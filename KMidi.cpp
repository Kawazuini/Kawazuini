/**
 * @file KMidi.cpp
 * @brief KMidiクラスの実装
 */
#include "KMidi.h"

const int KMidi::STATE_PLAY = 0x9;
const int KMidi::STATE_CHANGE = 0xC;

KMidi::KMidi() {
    midiOutOpen(&mMidiOut, MIDIMAPPER, 0, 0, 0);
}

KMidi::~KMidi() {
    midiOutReset(mMidiOut);
    midiOutClose(mMidiOut);
}

void KMidi::set(const int& aChannel, const Instrument& aInstrument) const {
    midiOutShortMsg(mMidiOut, noteToMsg(STATE_CHANGE, aChannel, aInstrument, 0));
}

void KMidi::play(const int& aChannel, const Note& aNote) const {
    midiOutShortMsg(mMidiOut, noteToMsg(STATE_PLAY, aChannel, 0x3c, 64));
}

void KMidi::stop(const int& aChannel) const {
    midiOutShortMsg(mMidiOut, noteToMsg(STATE_PLAY, aChannel, 0x3c, 0));
}
