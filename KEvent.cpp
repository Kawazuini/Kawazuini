/**
 * @file   KEvent.cpp
 * @brief  KEvent
 * @author Maeda Takumi
 */
#include "KEvent.h"

#include "KEventListener.h"

KEvent::KEvent() :
mActionCommand() {
}

void KEvent::update() {
    if (condition()) {
        for (KEventListener* i : mListeners) i->processEvent(this);
    }
}

int KEvent::addEventListener(KEventListener* aListener) {
    mListeners.push_back(aListener);
}

const String& KEvent::actionCommand() const {
    return mActionCommand;
}

