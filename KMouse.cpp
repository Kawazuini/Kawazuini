/**
 * @file KMouse.cpp
 * @author Maeda Takumi
 */
#include "KMouse.h"

#include "KVector.h"

KMouse::KMouse() {
    mWheel = 0;
}

void KMouse::press(const UINT& aMsg) {
    switch (aMsg) {
        case WM_LBUTTONDOWN: return mLeft.ON();
        case WM_MBUTTONDOWN: return mMiddle.ON();
        case WM_RBUTTONDOWN: return mRight.ON();
    }
}

void KMouse::release(const UINT& aMsg) {
    switch (aMsg) {
        case WM_LBUTTONUP: return mLeft.OFF();
        case WM_MBUTTONUP: return mMiddle.OFF();
        case WM_RBUTTONUP: return mRight.OFF();
    }
}

void KMouse::wheelSpin(const WPARAM& aWheel) {
    mWheel = GET_WHEEL_DELTA_WPARAM(aWheel);
}

void KMouse::pass() {
    mLeft.pass();
    mMiddle.pass();
    mRight.pass();
    mWheel = 0;
}

void KMouse::show() {
    ShowCursor(true);
}

void KMouse::hide() {
    ShowCursor(false);
}

KVector KMouse::pos() const {
    POINT pos;
    GetCursorPos(&pos);
    return KVector(pos);
}

void KMouse::setPos(const KVector& aPos) {
    SetCursorPos(aPos.x, aPos.y);
}

int KMouse::wheel() const {
    return mWheel / WHEEL_DELTA;
}

