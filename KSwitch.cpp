/**
 * @file KSwitch.cpp
 * @brief KSwitchクラスの実装
 */
#include "KSwitch.h"

KSwitch::KSwitch() :
mSwitch(false),
mOnFrame(0),
mOffFrame(0) {
}

void KSwitch::ON() {
    if (!mSwitch) mOnFrame = 1;
    mSwitch = true;
}

void KSwitch::OFF() {
    if (mSwitch) mOffFrame = 0;
    mSwitch = false;
}

void KSwitch::pass() {
    if (mSwitch) {
        if (mOnFrame < 0xfffffff) ++mOnFrame;
    } else if (mOffFrame < 0xfffffff) ++mOffFrame;
}

int KSwitch::onFrame() const {
    if (mSwitch) return mOnFrame;
    return 0;
}

int KSwitch::offFrame() const {
    return mOffFrame;
}

bool KSwitch::isTouch() const {
    return mSwitch && mOnFrame == 1;
}