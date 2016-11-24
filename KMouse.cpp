/**
 * @file KMouse.cpp
 * @brief KMouseクラスの実装
 */
#include "KMouse.h"

#include "KSwitch.h"
#include "KWindow.h"

KMouse::KMouse() {
    mWheel = 0;
    mWindow = NULL;
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

void KMouse::wheelSpin(const WPARAM aWheel) {
    mWheel = GET_WHEEL_DELTA_WPARAM(aWheel);
}

void KMouse::setWindow(const KWindow& aWindow) {
    mWindow = &aWindow;
}

void KMouse::pass() {
    mLeft.pass();
    mMiddle.pass();
    mRight.pass();
    mWheel = 0;
}

KVector KMouse::pos() const {
    POINT pos;
    GetCursorPos(&pos);
    ScreenToClient(mWindow->mWindow, &pos);
    return KVector(pos);
}

void KMouse::setPos(const KVector& aPos) {
    POINT pos = aPos;
    ClientToScreen(mWindow->mWindow, &pos);
    SetCursorPos(pos.x, pos.y);
}

void KMouse::show() {
}

void KMouse::hide() {
}

int KMouse::wheel() const {
    return mWheel / WHEEL_DELTA;
}

