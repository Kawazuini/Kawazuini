/**
 * @file   KRect.h
 * @brief  KRect
 * @author Maeda Takumi
 */
#ifndef KRECT_H
#define KRECT_H

#include "KawazuInclude.h"

class KVector;

#define DEPLOY_RECT(aRec) (aRec).x, (aRec).y, (aRec).width, (aRec).height

/**
 * @brief  \~english  Rect
 * @brief  \~japanese 矩形
 * @author \~ Maeda Takumi
 */
class KRect {
public:
    /** @brief 始点x座標 */ int x;
    /** @brief 始点y座標 */ int y;
    /** @brief 横幅      */ int width;
    /** @brief 縦幅      */ int height;

    KRect(
            const int& ax,
            const int& ay,
            const int& aw,
            const int& ah
            );
    /** @brief 原点から矩形を生成    */ KRect(const int& aw = 0, const int& ah = 0);
    /** @param aVec 右下の二次元座標 */ KRect(const KVector& aVec);
    /**
     * @param fromVec 矩形の左上の二次元座標
     * @param toVec 矩形の右下の二次元座標
     */
    KRect(const KVector& fromVec, const KVector& toVec);
    KRect(const RECT& aRec);

    KRect(const KRect& orig) = default;
    virtual ~KRect() = default;

    /** @return 2つの矩形が等しいかを返す  */ bool operator==(const KRect& aRect) const;
    /** @return 矩形を比較し大きいか返す   */ bool operator>(const KRect& aRect) const;
    /** @return 矩形を比較し小さいか返す   */ bool operator<(const KRect& aRect) const;
    /** @brief 矩形情報に変換              */ operator RECT() const;

    KRect expand(const int& aAmount) const;
    KRect slide(const KVector& aAmount) const;

    /** @return 矩形領域に,他の矩形領域が含まれるか */ bool isColision(const KRect& aRec) const;
    /** @return 矩形領域に,二次元座標が含まれるか   */ bool isColision(const KVector& aVec) const;
    /** @return 矩形同士の重なった領域              */ KRect intersect(const KRect& aRec) const;

    /** @return 矩形が大きさをもっているか */ bool isZero() const;
    /** @return 矩形上端のy座標            */ int top() const;
    /** @return 矩形下端のy座標            */ int bottom() const;
    /** @return 矩形左端のx座標            */ int left() const;
    /** @return 矩形右端のx座標            */ int right() const;
    /** @return 矩形の水平方向の中心座標   */ int centerX() const;
    /** @return 矩形の垂直方向の中心座標   */ int centerY() const;
    /** @return 始点座標                   */ KVector begin() const;
    /** @return 終点座標                   */ KVector end() const;
    /** @return 中心座標                   */ KVector center() const;
};

#endif /* KRECT_H */

