/**
 * @file   KKeyboard.h
 * @brief  KKeyboard
 * @author Maeda Takumi
 */
#ifndef KKEYBOARD_H
#define KKEYBOARD_H

#include "Kawazuinclude.h"
#include "KNonCopy.h"

class KSwitch;

/**
 * @brief  \~english  management system for keyboard
 * @brief  \~japanese キーボード入力管理システム
 * @author \~ Maeda Takumi
 */
class KKeyboard final : private KNonCopy {
    friend class KWindow;
private:
    bool mUpOff, mDownOff, mLeftOff, mRightOff; // 同時入力防止

    /* 指定キーを押す */ void press(const WPARAM& aKey);
    /* 指定キーを話す */ void release(const WPARAM& aKey);
public:

    /**
     * @brief \~english  kye ID
     * @brief \~japanese キーID
     */
    enum {
        KEY_ID_UP, KEY_ID_DOWN, KEY_ID_LEFT, KEY_ID_RIGHT,
        KEY_ID_CTRL, KEY_ID_SHIFT,
        KEY_ID_SPACE, KEY_ID_TAB,
        KEY_ID_ESCAPE, KEY_ID_BACK_SPACE,
        KEY_ID_0, KEY_ID_1, KEY_ID_2, KEY_ID_3, KEY_ID_4, KEY_ID_5, KEY_ID_6, KEY_ID_7, KEY_ID_8, KEY_ID_9,
        KEY_ID_A, KEY_ID_B, KEY_ID_C, KEY_ID_D, KEY_ID_E, KEY_ID_F, KEY_ID_G, KEY_ID_H, KEY_ID_I, KEY_ID_J,
        KEY_ID_K, KEY_ID_L, KEY_ID_M, KEY_ID_N, KEY_ID_O, KEY_ID_P, KEY_ID_Q, KEY_ID_R, KEY_ID_S, KEY_ID_T,
        KEY_ID_U, KEY_ID_V, KEY_ID_W, KEY_ID_X, KEY_ID_Y, KEY_ID_Z,
    };

    /**
     * @brief \~english  key array
     * @brief \~japanese キー配列
     */
    KSwitch * const mKeyboard;

    KKeyboard();
    ~KKeyboard();

    /**
     * @brief \~english  update switch.
     * @brief \~japanese ボタンを更新します。
     */
    void pass();
};

#endif /* KKEYBOARD_H */
