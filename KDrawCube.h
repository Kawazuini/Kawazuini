/**
 * @file   KDrawCube.h
 * @brief  KDrawCube
 * @author Maeda Takumi
 */
#ifndef KDRAWCUBE_H
#define KDRAWCUBE_H

#include "KDrawer.h"
#include "KVector.h"

/**
 * @brief  \~english  Cube for drawing
 * @brief  \~japanese 描画用立方体
 * @author \~ Maeda Takumi
 */
class KDrawCube : public KDrawer {
protected:
    /// @brief \~english  centroid vertex number
    /// @brief \~japanese 重心頂点番号
    static const int CENTROID;
    /// @brief \~english  drawing vertex number
    /// @brief \~japanese 描画頂点番号
    static const int DRAW_VERTEX_INDEX[6][4];

    /// @brief \~english  vertex coordinate
    /// @brief \~japanese 頂点座標
    KVector mVertex[9];
    /// @brief \~english  normal vector
    /// @brief \~japanese 法線ベクトル
    KVector mNormal[6];
    /// @brief \~english  distance of each vertex from the centroid coordinate
    /// @brief \~japanese 重心から頂点への距離
    float mRadius;
public:
    /**
     * \~english
     * @param aScale    length of one side of cube
     * @param aPosition centroid of cube
     * \~japanese
     * @param aScale    立方体の一辺の長さ
     * @param aPosition 立方体の重心座標
     */
    KDrawCube(const float& aScale, const KVector& aPosition = KVector());
    virtual ~KDrawCube() = default;

    void draw() const override;

    /**
     * \~english
     * @brief move the cube.
     * @param aVec destination coordinates
     * \~japanese
     * @brief 立方体を移動させます。
     * @param aVec 移動先座標
     */
    void translate(const KVector& aVec);
    /**
     * \~english
     * @brief rotate cube.
     * @param aOrigin rotation origin
     * @param aQuater rotation information
     * \~japanese
     * @brief 立方体を回転させます。
     * @param aOrigin 回転原点
     * @param aQuater 回転情報
     */
    void rotate(KVector aOrigin, const KQuaternion& aQuater);

    const KVector& position() const;
    const float& radius() const;
};

#endif /* KDRAWCUBE_H */

