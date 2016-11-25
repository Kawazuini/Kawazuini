/**
 * @file KMouse.h
 * @author Maeda Takumi
 */
#ifndef KMOUSE_H
#define KMOUSE_H

#include "KawazuInclude.h"

#include "KNonCopy.h"
#include "KSwitch.h"

class KVector;

/** @see KWindow.h */
class KMouse : private KNonCopy {
    friend class KWindow;
private:
    int mWheel; ///< ホイール回転数

    void press(const UINT& aMsg);
    void release(const UINT& aMsg);
    void wheelSpin(const WPARAM& aWheel);
public:
    KSwitch mLeft; ///< 左クリック
    KSwitch mMiddle; ///< 中央クリック
    KSwitch mRight; ///< 右クリック

    KMouse();
    virtual ~KMouse() = default;

    /** @brief ボタン時間を更新する。 */
    void pass();

    /** @brief マウスカーソルの表示。 */
    void show();
    /** @brief マウスカーソルの隠蔽。 */
    void hide();

    /** @brief マウスポインタの座標を取得。 */
    KVector pos() const;
    /**
     * @brief マウスポインタの座標設定。
     * @param aPos 画面上の座標
     */
    void setPos(const KVector& aPos);

    /**
     * @brief ホイール回転数の取得。
     * @return ホイール回転数
     */
    int wheel() const;
};

#endif /* KMOUSE_H */

