/**
 * @file KDrawSphere.h
 * @brief KDrawSphere
 * @author Maeda Takumi
 */
#ifndef KDRAWSPHERE_H
#define KDRAWSPHERE_H

#include "KNonCopy.h"
#include "KVector.h"

class KTexture;

/**
 * @brief  \~english  Sphere for drawing
 * @brief  \~japanese 描画用球体
 * @author \~ Maeda Takumi
 */
class KDrawSphere : private KNonCopy {
private:
    /**
     * @brief \~english  center coordinate
     * @brief \~japanese 中心座標
     */
    KVector mPosition;
    /**
     * @brief \~english  radius
     * @brief \~japanese 半径
     */
    float mRadius;
    /**
     * @brief \~english  vertex array
     * @brief \~japanese 頂点配列
     */
    KVector* mVertex;
    /**
     * @brief \~english  Number of horizonal divisions like latitude
     * @brief \~japanese 緯度のような水平分割数
     */
    int mStack;
    /**
     * @brief \~english  Number of vertical divisions like longitude
     * @brief \~japanese 経度のような垂直分割数
     */
    int mSlice;
public:
    /**
     * @brief \~english  texture
     * @breif \~japanese テクスチャ
     */
    KTexture* mTexture;

    KDrawSphere(
            const KVector& aPosition,
            const float& aRadius,
            const int& aStack,
            const int& aSlice
            );
    virtual ~KDrawSphere();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const;
};

#endif /* KDRAWSPHERE_H */

