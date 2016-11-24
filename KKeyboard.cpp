/**
 * @file KKeyboard.cpp
 * @brief KKeyboardクラスの実装
 */
#include "KKeyboard.h"

#include "KSwitch.h"

int KKeyboard::_ = 0;

const int KKeyboard::K_UP = _++;
const int KKeyboard::K_DOWN = _++;
const int KKeyboard::K_LEFT = _++;
const int KKeyboard::K_RIGHT = _++;
const int KKeyboard::K_SHIFT = _++;
const int KKeyboard::K_SPACE = _++;
const int KKeyboard::K_ESCAPE = _++;
const int KKeyboard::K_0 = _++;
const int KKeyboard::K_1 = _++;
const int KKeyboard::K_2 = _++;
const int KKeyboard::K_3 = _++;
const int KKeyboard::K_4 = _++;
const int KKeyboard::K_5 = _++;
const int KKeyboard::K_6 = _++;
const int KKeyboard::K_7 = _++;
const int KKeyboard::K_8 = _++;
const int KKeyboard::K_9 = _++;
const int KKeyboard::K_A = _++;
const int KKeyboard::K_B = _++;
const int KKeyboard::K_C = _++;
const int KKeyboard::K_D = _++;
const int KKeyboard::K_E = _++;
const int KKeyboard::K_F = _++;
const int KKeyboard::K_G = _++;
const int KKeyboard::K_H = _++;
const int KKeyboard::K_I = _++;
const int KKeyboard::K_J = _++;
const int KKeyboard::K_K = _++;
const int KKeyboard::K_L = _++;
const int KKeyboard::K_M = _++;
const int KKeyboard::K_N = _++;
const int KKeyboard::K_O = _++;
const int KKeyboard::K_P = _++;
const int KKeyboard::K_Q = _++;
const int KKeyboard::K_R = _++;
const int KKeyboard::K_S = _++;
const int KKeyboard::K_T = _++;
const int KKeyboard::K_U = _++;
const int KKeyboard::K_V = _++;
const int KKeyboard::K_W = _++;
const int KKeyboard::K_X = _++;
const int KKeyboard::K_Y = _++;
const int KKeyboard::K_Z = _++;

KKeyboard::KKeyboard() : mKeyboard(new KSwitch[_]) {
    mUpOff = mDownOff = mLeftOff = mRightOff = false;
}

KKeyboard::~KKeyboard() {
    delete[] mKeyboard;
}

void KKeyboard::press(const WPARAM& aKey) {
    switch (aKey) {
        case VK_UP:
            if ((mKeyboard + K_DOWN)->onFrame()) {
                mDownOff = true;
                (mKeyboard + K_DOWN)->OFF();
            }
            return (mKeyboard + K_UP)->ON();
        case VK_DOWN:
            if ((mKeyboard + K_UP)->onFrame()) {
                mUpOff = true;
                (mKeyboard + K_UP)->OFF();
            }
            return (mKeyboard + K_DOWN)->ON();
        case VK_LEFT:
            if ((mKeyboard + K_RIGHT)->onFrame()) {
                mRightOff = true;
                (mKeyboard + K_RIGHT)->OFF();
            }
            return (mKeyboard + K_LEFT)->ON();
        case VK_RIGHT:
            if ((mKeyboard + K_LEFT)->onFrame()) {
                mLeftOff = true;
                (mKeyboard + K_LEFT)->OFF();
            }
            return (mKeyboard + K_RIGHT)->ON();
        case VK_SHIFT: return (mKeyboard + K_SHIFT)->ON();
        case VK_SPACE: return (mKeyboard + K_SPACE)->ON();
        case VK_ESCAPE: return (mKeyboard + K_ESCAPE)->ON();
        case '0': return (mKeyboard + K_0)->ON();
        case '1': return (mKeyboard + K_1)->ON();
        case '2': return (mKeyboard + K_2)->ON();
        case '3': return (mKeyboard + K_3)->ON();
        case '4': return (mKeyboard + K_4)->ON();
        case '5': return (mKeyboard + K_5)->ON();
        case '6': return (mKeyboard + K_6)->ON();
        case '7': return (mKeyboard + K_7)->ON();
        case '8': return (mKeyboard + K_8)->ON();
        case '9': return (mKeyboard + K_9)->ON();
        case 'A': return (mKeyboard + K_A)->ON();
        case 'B': return (mKeyboard + K_B)->ON();
        case 'C': return (mKeyboard + K_C)->ON();
        case 'D': return (mKeyboard + K_D)->ON();
        case 'E': return (mKeyboard + K_E)->ON();
        case 'F': return (mKeyboard + K_F)->ON();
        case 'G': return (mKeyboard + K_G)->ON();
        case 'H': return (mKeyboard + K_H)->ON();
        case 'I': return (mKeyboard + K_I)->ON();
        case 'J': return (mKeyboard + K_J)->ON();
        case 'K': return (mKeyboard + K_K)->ON();
        case 'L': return (mKeyboard + K_L)->ON();
        case 'M': return (mKeyboard + K_M)->ON();
        case 'N': return (mKeyboard + K_N)->ON();
        case 'O': return (mKeyboard + K_O)->ON();
        case 'P': return (mKeyboard + K_P)->ON();
        case 'Q': return (mKeyboard + K_Q)->ON();
        case 'R': return (mKeyboard + K_R)->ON();
        case 'S': return (mKeyboard + K_S)->ON();
        case 'T': return (mKeyboard + K_T)->ON();
        case 'U': return (mKeyboard + K_U)->ON();
        case 'V': return (mKeyboard + K_V)->ON();
        case 'W': return (mKeyboard + K_W)->ON();
        case 'X': return (mKeyboard + K_X)->ON();
        case 'Y': return (mKeyboard + K_Y)->ON();
        case 'Z': return (mKeyboard + K_Z)->ON();
    }
}

void KKeyboard::release(const WPARAM& aKey) {
    switch (aKey) {
        case VK_UP:
            mUpOff = false;
            if (mDownOff) {
                mDownOff = false;
                (mKeyboard + K_DOWN)->ON();
            }
            return (mKeyboard + K_UP)->OFF();
        case VK_DOWN:
            mDownOff = false;
            if (mUpOff) {
                mUpOff = false;
                (mKeyboard + K_UP)->ON();
            }
            return (mKeyboard + K_DOWN)->OFF();
        case VK_LEFT:
            mLeftOff = false;
            if (mRightOff) {
                mRightOff = false;
                (mKeyboard + K_RIGHT)->ON();
            }
            return (mKeyboard + K_LEFT)->OFF();
        case VK_RIGHT:
            mRightOff = false;
            if (mLeftOff) {
                mLeftOff = false;
                (mKeyboard + K_LEFT)->ON();
            }
            return (mKeyboard + K_RIGHT)->OFF();
        case VK_SHIFT: return (mKeyboard + K_SHIFT)->OFF();
        case VK_SPACE: return (mKeyboard + K_SPACE)->OFF();
        case VK_ESCAPE: return (mKeyboard + K_ESCAPE)->OFF();
        case '0': return (mKeyboard + K_0)->OFF();
        case '1': return (mKeyboard + K_1)->OFF();
        case '2': return (mKeyboard + K_2)->OFF();
        case '3': return (mKeyboard + K_3)->OFF();
        case '4': return (mKeyboard + K_4)->OFF();
        case '5': return (mKeyboard + K_5)->OFF();
        case '6': return (mKeyboard + K_6)->OFF();
        case '7': return (mKeyboard + K_7)->OFF();
        case '8': return (mKeyboard + K_8)->OFF();
        case '9': return (mKeyboard + K_9)->OFF();
        case 'A': return (mKeyboard + K_A)->OFF();
        case 'B': return (mKeyboard + K_B)->OFF();
        case 'C': return (mKeyboard + K_C)->OFF();
        case 'D': return (mKeyboard + K_D)->OFF();
        case 'E': return (mKeyboard + K_E)->OFF();
        case 'F': return (mKeyboard + K_F)->OFF();
        case 'G': return (mKeyboard + K_G)->OFF();
        case 'H': return (mKeyboard + K_H)->OFF();
        case 'I': return (mKeyboard + K_I)->OFF();
        case 'J': return (mKeyboard + K_J)->OFF();
        case 'K': return (mKeyboard + K_K)->OFF();
        case 'L': return (mKeyboard + K_L)->OFF();
        case 'M': return (mKeyboard + K_M)->OFF();
        case 'N': return (mKeyboard + K_N)->OFF();
        case 'O': return (mKeyboard + K_O)->OFF();
        case 'P': return (mKeyboard + K_P)->OFF();
        case 'Q': return (mKeyboard + K_Q)->OFF();
        case 'R': return (mKeyboard + K_R)->OFF();
        case 'S': return (mKeyboard + K_S)->OFF();
        case 'T': return (mKeyboard + K_T)->OFF();
        case 'U': return (mKeyboard + K_U)->OFF();
        case 'V': return (mKeyboard + K_V)->OFF();
        case 'W': return (mKeyboard + K_W)->OFF();
        case 'X': return (mKeyboard + K_X)->OFF();
        case 'Y': return (mKeyboard + K_Y)->OFF();
        case 'Z': return (mKeyboard + K_Z)->OFF();
    }
}

void KKeyboard::pass() {
    KSwitch* key = mKeyboard;
    for (int i = 0; i < _; ++i, ++key) key->pass();
}
