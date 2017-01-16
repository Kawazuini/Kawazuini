/**
 * @file   KListener.h
 * @brief  KListener
 * @author Maeda Takumi
 */
#ifndef KLISTENER_H
#define KLISTENER_H

#include "KKeyboard.h"
#include "KMouse.h"

/**
 * @brief  Application's Listener System
 * @author Maeda Takumi
 */
class KListener : private KNonCopy {
    friend class KWindow;
protected:
    KKeyboard mKeyboard; ///< キーボード
    KMouse mMouse; ///< マウス

    KListener() = default;
    virtual ~KListener() = default;
public:

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    virtual void draw() {
    };

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    virtual void update() {
        mKeyboard.pass();
        mMouse.pass();
    };
};

#endif /* KLISTENER_H */

