/**
 * @file   KDrawSphere.h
 * @brief  KDrawSphere
 * @author Maeda Takumi
 */
#ifndef KDRAWSPHERE_H
#define KDRAWSPHERE_H

#include "KDrawObject.h"
#include "KVector.h"

class KTexture;

/**
 * @brief  \~english  Sphere for drawing
 * @brief  \~japanese 描画用球体
 * @author \~ Maeda Takumi
 */
class KDrawSphere : public KDrawObject {
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
     * @brief \~english  Number of horizonal divisions like latitude
     * @brief \~japanese 緯度のような水平分割数
     */
    int mStack;
    /**
     * @brief \~english  Number of vertical divisions like longitude
     * @brief \~japanese 経度のような垂直分割数
     */
    int mSlice;
    /**
     * @brief \~english  vertex array
     * @brief \~japanese 頂点配列
     */
    KVector* mVertex;
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
    void draw() const override;

    /**
     * \~english
     * @brief translate center coordinate into argument.
     * @param aVec new center coordinate
     * \~japanese
     * @brief 中心座標を指定座標に遷移させる。
     * @param 設定する中心座標
     */
    void tlanslate(const KVector& aVec);
    /**
     * \~english
     * @brief rotate each vertex at the center coordinate.
     * @param aQuater rotating information
     * \~japanese
     * @brief 中心座標で各頂点を回転させる。
     * @param aQuater 回転情報
     */
    void rotate(const KQuaternion& aQuater);
};

#endif /* KDRAWSPHERE_H */

