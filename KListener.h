/**
 * @file KListener.h
 * @author Maeda Takumi
 */
#ifndef KLISTENER_H
#define KLISTENER_H

#include "KKeyboard.h"
#include "KMouse.h"

/** @see KWindow.h */
class KListener : private KNonCopy {
    friend class KWindow;
protected:
    KKeyboard mKeyboard; ///< キーボード
    KMouse mMouse; ///< マウス

    KListener() = default;
    virtual ~KListener() = default;

public:

    /** @brief 更新処理 */
    virtual void update() {
        mKeyboard.pass();
        mMouse.pass();
    };

    /** @brief 描画処理 */
    virtual void draw() {
    };
};

#endif /* KLISTENER_H */

