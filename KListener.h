/**
 * @file KListener.h
 * @brief イベントリスナークラス
 */
#ifndef KLISTENER_H
#define KLISTENER_H

#include "KKeyboard.h"
#include "KMouse.h"

/**
 * @brief イベントリスナー
 * @see KWindow.h
 */
class KListener : private KNonCopy {
    friend class KWindow;
protected:
    /** @brief キーボード   */ KKeyboard mKeyboard;
    /** @brief マウス       */ KMouse mMouse;

    KListener(KWindow* aWindow) {
        mMouse.setWindow(*aWindow);
    };

    virtual ~KListener() {
    };

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
