/**
 * @file   KMouse.h
 * @brief  KMouse
 * @author Maeda Takumi
 */
#ifndef KMOUSE_H
#define KMOUSE_H

#include "KawazuInclude.h"

#include "KNonCopy.h"
#include "KSwitch.h"

class KVector;

/**
 * @brief  \~english  management system of mouse
 * @brief  \~japanese マウス管理システム
 * @author \~ Maeda Takumi
 */
class KMouse final : private KNonCopy {
    friend class KWindow;
private:
    /* ホイール回転数 */ int mWheel;

    /* ボタンを押します。         */ void press(const UINT& aMsg);
    /* ボタンを離します。         */ void release(const UINT& aMsg);
    /* ホイールを回転させます。   */ void wheelSpin(const WPARAM& aWheel);
    /* 表示カウントを計算します。 */ int count() const;
public:
    /// @brief \~english  left click
    /// @brief \~japanese 左クリック
    KSwitch mLeft;
    /// @brief \~english  middle click
    /// @brief \~japanese 中央クリック
    KSwitch mMiddle;
    /// @brief \~english  right click
    /// @brief \~japanese 右クリック
    KSwitch mRight;

    KMouse();
    ~KMouse() = default;

    /**
     * @brief \~english  update button time.
     * @brief \~japanese ボタン時間を更新します。
     */
    void pass();

    /**
     * @brief \~english  display mouse cursor.
     * @brief \~japanese マウスカーソルを表示します。
     */
    void show();
    /**
     * @brief \~english  hide mouse cursor.
     * @brief \~japanese マウスカーソルを隠します。
     */
    void hide();

    /**
     * \~english
     * @brief  calculate mouse pointer coordinate.
     * @return mouse pointer coordinate
     * \~japanese
     * @brief  マウスポインタの座標を計算します。
     * @return マウスポインタ座標
     */
    KVector position() const;
    /**
     * \~english
     * @brief set mouse pointer coordinate.
     * @param aPos new position
     * \~japanese
     * @brief マウスポインタの座標を設定します。
     * @param aPos 新しい座標
     */
    void setPos(const KVector& aPos);

    /**
     * \~english
     * @brief  calculate wheel speed.
     * @return wheel speed
     * \~japanese
     * @brief  ホイール回転数を計算します。
     * @return ホイール回転数
     */
    int wheel() const;
};

#endif /* KMOUSE_H */

