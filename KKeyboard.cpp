/**
 * @file   KKeyboard.cpp
 * @brief  KKeyboard
 * @author Maeda Takumi
 */
#include "KKeyboard.h"

#include "KSwitch.h"

KKeyboard::KKeyboard() :
mKeyboard(new KSwitch[KEY_ID_Z + 1]),
mUpOff(false),
mDownOff(false),
mLeftOff(false),
mRightOff(false) {
}

KKeyboard::~KKeyboard() {
    delete[] mKeyboard;
}

void KKeyboard::press(const WPARAM& aKey) {
    switch (aKey) {
        case VK_UP:
            if ((mKeyboard + KEY_ID_DOWN)->onFrame()) {
                mDownOff = true;
                (mKeyboard + KEY_ID_DOWN)->OFF();
            }
            return (mKeyboard + KEY_ID_UP)->ON();
        case VK_DOWN:
            if ((mKeyboard + KEY_ID_UP)->onFrame()) {
                mUpOff = true;
                (mKeyboard + KEY_ID_UP)->OFF();
            }
            return (mKeyboard + KEY_ID_DOWN)->ON();
        case VK_LEFT:
            if ((mKeyboard + KEY_ID_RIGHT)->onFrame()) {
                mRightOff = true;
                (mKeyboard + KEY_ID_RIGHT)->OFF();
            }
            return (mKeyboard + KEY_ID_LEFT)->ON();
        case VK_RIGHT:
            if ((mKeyboard + KEY_ID_LEFT)->onFrame()) {
                mLeftOff = true;
                (mKeyboard + KEY_ID_LEFT)->OFF();
            }
            return (mKeyboard + KEY_ID_RIGHT)->ON();
        case VK_SHIFT: return (mKeyboard + KEY_ID_SHIFT)->ON();
        case VK_SPACE: return (mKeyboard + KEY_ID_SPACE)->ON();
        case VK_ESCAPE: return (mKeyboard + KEY_ID_ESCAPE)->ON();
        case VK_TAB: return (mKeyboard + KEY_ID_TAB)->ON();
        case '0': return (mKeyboard + KEY_ID_0)->ON();
        case '1': return (mKeyboard + KEY_ID_1)->ON();
        case '2': return (mKeyboard + KEY_ID_2)->ON();
        case '3': return (mKeyboard + KEY_ID_3)->ON();
        case '4': return (mKeyboard + KEY_ID_4)->ON();
        case '5': return (mKeyboard + KEY_ID_5)->ON();
        case '6': return (mKeyboard + KEY_ID_6)->ON();
        case '7': return (mKeyboard + KEY_ID_7)->ON();
        case '8': return (mKeyboard + KEY_ID_8)->ON();
        case '9': return (mKeyboard + KEY_ID_9)->ON();
        case 'A': return (mKeyboard + KEY_ID_A)->ON();
        case 'B': return (mKeyboard + KEY_ID_B)->ON();
        case 'C': return (mKeyboard + KEY_ID_C)->ON();
        case 'D': return (mKeyboard + KEY_ID_D)->ON();
        case 'E': return (mKeyboard + KEY_ID_E)->ON();
        case 'F': return (mKeyboard + KEY_ID_F)->ON();
        case 'G': return (mKeyboard + KEY_ID_G)->ON();
        case 'H': return (mKeyboard + KEY_ID_H)->ON();
        case 'I': return (mKeyboard + KEY_ID_I)->ON();
        case 'J': return (mKeyboard + KEY_ID_J)->ON();
        case 'K': return (mKeyboard + KEY_ID_K)->ON();
        case 'L': return (mKeyboard + KEY_ID_L)->ON();
        case 'M': return (mKeyboard + KEY_ID_M)->ON();
        case 'N': return (mKeyboard + KEY_ID_N)->ON();
        case 'O': return (mKeyboard + KEY_ID_O)->ON();
        case 'P': return (mKeyboard + KEY_ID_P)->ON();
        case 'Q': return (mKeyboard + KEY_ID_Q)->ON();
        case 'R': return (mKeyboard + KEY_ID_R)->ON();
        case 'S': return (mKeyboard + KEY_ID_S)->ON();
        case 'T': return (mKeyboard + KEY_ID_T)->ON();
        case 'U': return (mKeyboard + KEY_ID_U)->ON();
        case 'V': return (mKeyboard + KEY_ID_V)->ON();
        case 'W': return (mKeyboard + KEY_ID_W)->ON();
        case 'X': return (mKeyboard + KEY_ID_X)->ON();
        case 'Y': return (mKeyboard + KEY_ID_Y)->ON();
        case 'Z': return (mKeyboard + KEY_ID_Z)->ON();
    }
}

void KKeyboard::release(const WPARAM& aKey) {
    switch (aKey) {
        case VK_UP:
            mUpOff = false;
            if (mDownOff) {
                mDownOff = false;
                (mKeyboard + KEY_ID_DOWN)->ON();
            }
            return (mKeyboard + KEY_ID_UP)->OFF();
        case VK_DOWN:
            mDownOff = false;
            if (mUpOff) {
                mUpOff = false;
                (mKeyboard + KEY_ID_UP)->ON();
            }
            return (mKeyboard + KEY_ID_DOWN)->OFF();
        case VK_LEFT:
            mLeftOff = false;
            if (mRightOff) {
                mRightOff = false;
                (mKeyboard + KEY_ID_RIGHT)->ON();
            }
            return (mKeyboard + KEY_ID_LEFT)->OFF();
        case VK_RIGHT:
            mRightOff = false;
            if (mLeftOff) {
                mLeftOff = false;
                (mKeyboard + KEY_ID_LEFT)->ON();
            }
            return (mKeyboard + KEY_ID_RIGHT)->OFF();
        case VK_SHIFT: return (mKeyboard + KEY_ID_SHIFT)->OFF();
        case VK_SPACE: return (mKeyboard + KEY_ID_SPACE)->OFF();
        case VK_ESCAPE: return (mKeyboard + KEY_ID_ESCAPE)->OFF();
        case VK_TAB: return (mKeyboard + KEY_ID_TAB)->OFF();
        case '0': return (mKeyboard + KEY_ID_0)->OFF();
        case '1': return (mKeyboard + KEY_ID_1)->OFF();
        case '2': return (mKeyboard + KEY_ID_2)->OFF();
        case '3': return (mKeyboard + KEY_ID_3)->OFF();
        case '4': return (mKeyboard + KEY_ID_4)->OFF();
        case '5': return (mKeyboard + KEY_ID_5)->OFF();
        case '6': return (mKeyboard + KEY_ID_6)->OFF();
        case '7': return (mKeyboard + KEY_ID_7)->OFF();
        case '8': return (mKeyboard + KEY_ID_8)->OFF();
        case '9': return (mKeyboard + KEY_ID_9)->OFF();
        case 'A': return (mKeyboard + KEY_ID_A)->OFF();
        case 'B': return (mKeyboard + KEY_ID_B)->OFF();
        case 'C': return (mKeyboard + KEY_ID_C)->OFF();
        case 'D': return (mKeyboard + KEY_ID_D)->OFF();
        case 'E': return (mKeyboard + KEY_ID_E)->OFF();
        case 'F': return (mKeyboard + KEY_ID_F)->OFF();
        case 'G': return (mKeyboard + KEY_ID_G)->OFF();
        case 'H': return (mKeyboard + KEY_ID_H)->OFF();
        case 'I': return (mKeyboard + KEY_ID_I)->OFF();
        case 'J': return (mKeyboard + KEY_ID_J)->OFF();
        case 'K': return (mKeyboard + KEY_ID_K)->OFF();
        case 'L': return (mKeyboard + KEY_ID_L)->OFF();
        case 'M': return (mKeyboard + KEY_ID_M)->OFF();
        case 'N': return (mKeyboard + KEY_ID_N)->OFF();
        case 'O': return (mKeyboard + KEY_ID_O)->OFF();
        case 'P': return (mKeyboard + KEY_ID_P)->OFF();
        case 'Q': return (mKeyboard + KEY_ID_Q)->OFF();
        case 'R': return (mKeyboard + KEY_ID_R)->OFF();
        case 'S': return (mKeyboard + KEY_ID_S)->OFF();
        case 'T': return (mKeyboard + KEY_ID_T)->OFF();
        case 'U': return (mKeyboard + KEY_ID_U)->OFF();
        case 'V': return (mKeyboard + KEY_ID_V)->OFF();
        case 'W': return (mKeyboard + KEY_ID_W)->OFF();
        case 'X': return (mKeyboard + KEY_ID_X)->OFF();
        case 'Y': return (mKeyboard + KEY_ID_Y)->OFF();
        case 'Z': return (mKeyboard + KEY_ID_Z)->OFF();
    }
}

void KKeyboard::pass() {
    KSwitch* key = mKeyboard;
    for (int i = 0, i_e = KEY_ID_Z + 1; i < i_e; ++i, ++key) key->pass();
}

