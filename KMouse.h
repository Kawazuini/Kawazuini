/**
 * @file KMouse.h
 * @brief マウスクラス
 */
#ifndef KMOUSE_H
#define KMOUSE_H

#include "KawazuInclude.h"

#include "KNonCopy.h"
#include "KSwitch.h"

class KVector;
class KWindow;

/** @brief マウス */
class KMouse : private KNonCopy {
    friend class KWindow;
private:
    /** @brief ホイール回転数       */ int mWheel;
    /** @brief 座標検出用ウィンドウ */ const KWindow* mWindow;

    /** @brief 指定ボタンを押す */ void press(const UINT& aMsg);
    /** @brief 指定ボタンを離す */ void release(const UINT& aMsg);
    /** @brief ホイールを回す   */ void wheelSpin(const WPARAM aWheel);
public:
    KSwitch mLeft; ///< 左クリック
    KSwitch mMiddle; ///< 中央クリック
    KSwitch mRight; ///< 右クリック

    KMouse();
    virtual ~KMouse() = default;

    /** @brief ウィンドウの登録(座標検出に使用) */
    void setWindow(const KWindow& aWindow);
    /** @brief ボタン時間の更新 */
    void pass();

    /***/
    KVector pos() const;
    /***/
    void setPos(const KVector& aPos);

    /***/
    void show();
    /***/
    void hide();

    /***/
    int wheel() const;
};

#endif /* KMOUSE_H */
