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
protected:
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
     * @brief \~english  Number of horizonal divisions
     * @brief \~japanese 水平分割数
     */
    int mStack;
    /**
     * @brief \~english  Number of vertical divisions
     * @brief \~japanese 垂直分割数
     */
    int mSlice;
    /**
     * @brief \~english  vertex array
     * @brief \~japanese 頂点配列
     */
    Vector<Vector<KVector>> mVertex;
    /**
     * @brief \~english  normal array
     * @brief \~japanese 法線配列
     */
    Vector<Vector<KVector>> mNormal;
    /**
     * @brief \~english  valid vertex number
     * @brief \~japanese 有効頂点数
     */
    int mVertexSize;

    /**
     * \~english
     * @brief  return valid vertex.
     * @param  aStack latitude
     * @param  aSlice longitude
     * @return valid vertex
     * \~japanese
     * @brief  有効な頂点を返します。
     * @param  aStack 緯度
     * @param  aSlice 経度
     * @return 有効な頂点
     */
    const KVector& getVertex(const int& aStack, const int& aSlice) const;
    /**
     * \~english
     * @brief  return valid normal.
     * @param  aStack latitude
     * @param  aSlice longitude
     * @return valid normal
     * \~japanese
     * @brief  有効な法線を返します。
     * @param  aStack 緯度
     * @param  aSlice 経度
     * @return 有効な法線
     */
    const KVector& getNormal(const int& aStack, const int& aSlice) const;
    /**
     * \~english
     * @brief  determine whether valid vertex.
     * @param  aStack latitude
     * @param  aSlice longitude
     * @return whether valid vertex
     * \~japanese
     * @brief  有効な頂点かを判定します。
     * @param  aStack 緯度
     * @param  aSlice 経度
     * @return 有効な頂点か
     */
    bool validIndex(const int& aStack, const int& aSlice);
public:
    /**
     * @brief \~english  texture
     * @breif \~japanese テクスチャ
     */
    const KTexture* mTexture;

    KDrawSphere(
            const KVector& aPosition,
            const float& aRadius,
            const int& aStack,
            const int& aSlice
            );
    virtual ~KDrawSphere() = default;

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
     * @brief 中心座標を指定座標に遷移させます。
     * @param 設定する中心座標
     */
    virtual void translate(const KVector& aVec);
    /**
     * \~english
     * @brief rotate each vertex at the center coordinate.
     * @param aQuater rotating information
     * \~japanese
     * @brief 中心座標で各頂点を回転させます。
     * @param aQuater 回転情報
     */
    void rotate(const KQuaternion& aQuater);
};

#endif /* KDRAWSPHERE_H */

