/**
 * @file   KMidi.cpp
 * @brief  KMidi
 * @author Maeda Takumi
 */
#include "KMidi.h"

const int KMidi::CHANNEL_COUNT(16);
const int KMidi::STATE_PLAY(0x9);
const int KMidi::STATE_CHANGE(0xC);

KMidi::KMidi() :
mThread(TimeManager, this),
mNotes(CHANNEL_COUNT) {
    midiOutOpen(&mMidi, MIDIMAPPER, 0, 0, 0);
    mNoteLock.unlock();
}

KMidi::~KMidi() {
    mThread.stop();
    midiOutReset(mMidi);
    midiOutClose(mMidi);
}

void* KMidi::TimeManager(void* aMidi) {
    KMidi & midi(*(KMidi*) aMidi);
    Time time(0), pass(0);

    while (true) {
        pass = now() - time;
        midi.mNoteLock.lock();
        for (int i = 0; i < CHANNEL_COUNT; ++i) {
            int count(0);
            for (auto j = midi.mNotes[i].begin(); j != midi.mNotes[i].end(); ++j, ++count) {
                int phon(j->mPhonetic -= pass);
                if (phon < 0) { // 音価を使い切る
                    bool stop(true);
                    for (Note k : midi.mNotes[i]) {
                        if (k.mTone == j->mTone && k.mPhonetic != phon) { // 重なった音は止めない
                            stop = false;
                            break;
                        }
                    }
                    if (stop) midi.stop(i, *j);
                    midi.mNotes[i].erase(j);
                    if (count == midi.mNotes[i].size()) break;
                    j = midi.mNotes[i].begin() + count;
                }
            }
        }
        midi.mNoteLock.unlock();
        time = now();
        Sleep(1);

        pthread_testcancel();
    }
}

void KMidi::set(const int& aChannel, const Instrument& aInstrument) const {
    midiOutShortMsg(mMidi, noteToMsg(STATE_CHANGE, aChannel, aInstrument, 0));
}

void KMidi::play(const int& aChannel, const Note& aNote) {
    mNoteLock.lock();
    mNotes[aChannel].push_back(aNote);
    mNoteLock.unlock();
    midiOutShortMsg(mMidi, noteToMsg(STATE_PLAY, aChannel, aNote.mTone, aNote.mVelocity));
}

void KMidi::stop(const int& aChannel, const Note& aNote) const {
    midiOutShortMsg(mMidi, noteToMsg(STATE_PLAY, aChannel, aNote.mTone, 0));
}

void KMidi::stop() {
    mNoteLock.lock();
    for (Vector<Note> i : mNotes) i.clear();
    mNoteLock.unlock();
    midiOutReset(mMidi);
}

