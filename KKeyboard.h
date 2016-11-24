/**
 * @file KKeyboard.h
 * @brief キー入力を管理するクラス
 */
#ifndef KKEYBOARD_H
#define KKEYBOARD_H

#include "Kawazuinclude.h"
#include "KNonCopy.h"

class KSwitch;

/** @brief キーボード */
class KKeyboard : private KNonCopy {
    friend class KWindow;
private:
    static int _; // 定数の初期化に使用

    bool mUpOff, mDownOff, mLeftOff, mRightOff; // 同時入力防止

    /** @brief 指定キーを押す */ void press(const WPARAM& aKey);
    /** @brief 指定キーを話す */ void release(const WPARAM& aKey);
public:
    /* キーID */
    /** @brief ↑     */ static const int K_UP;
    /** @brief ↓     */ static const int K_DOWN;
    /** @brief ←     */ static const int K_LEFT;
    /** @brief →     */ static const int K_RIGHT;
    /** @brief shift  */ static const int K_SHIFT;
    /** @brief space  */ static const int K_SPACE;
    /** @brief escape */ static const int K_ESCAPE;
    /** @brief A      */ static const int K_0;
    /** @brief B      */ static const int K_1;
    /** @brief C      */ static const int K_2;
    /** @brief D      */ static const int K_3;
    /** @brief E      */ static const int K_4;
    /** @brief F      */ static const int K_5;
    /** @brief G      */ static const int K_6;
    /** @brief H      */ static const int K_7;
    /** @brief I      */ static const int K_8;
    /** @brief J      */ static const int K_9;
    /** @brief A      */ static const int K_A;
    /** @brief B      */ static const int K_B;
    /** @brief C      */ static const int K_C;
    /** @brief D      */ static const int K_D;
    /** @brief E      */ static const int K_E;
    /** @brief F      */ static const int K_F;
    /** @brief G      */ static const int K_G;
    /** @brief H      */ static const int K_H;
    /** @brief I      */ static const int K_I;
    /** @brief J      */ static const int K_J;
    /** @brief K      */ static const int K_K;
    /** @brief L      */ static const int K_L;
    /** @brief M      */ static const int K_M;
    /** @brief N      */ static const int K_N;
    /** @brief O      */ static const int K_O;
    /** @brief P      */ static const int K_P;
    /** @brief Q      */ static const int K_Q;
    /** @brief R      */ static const int K_R;
    /** @brief S      */ static const int K_S;
    /** @brief T      */ static const int K_T;
    /** @brief U      */ static const int K_U;
    /** @brief V      */ static const int K_V;
    /** @brief W      */ static const int K_W;
    /** @brief X      */ static const int K_X;
    /** @brief Y      */ static const int K_Y;
    /** @brief Z      */ static const int K_Z;

    /** @brief キー配列 */ KSwitch * const mKeyboard;

    KKeyboard();
    virtual ~KKeyboard();

    /** @brief ボタンの更新 */ void pass();
};

#endif /* KKEYBOARD_H */
