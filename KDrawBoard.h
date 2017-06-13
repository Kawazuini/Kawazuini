/**
 * @file   KDrawBoard.h
 * @brief  KDrawBoard
 * @author Maeda Takumi
 */
#ifndef KDRAWBOARD_H
#define KDRAWBOARD_H

#include "KDrawer.h"
#include "KTexture.h"
#include "KVector.h"

/**
 * @brief  \~english  Rect Polygon for drawing
 * @brief  \~japanese 描画用四角形ポリゴン
 * @author \~ Maeda Takumi
 */
class KDrawBoard : public KDrawer {
private:
    /* 描画頂点   */ Vector<KVector> mVertex;
    /* 中心座標   */ KVector mCenter;
    /* 法線       */ KVector mNormal;
    /* テクスチャ */ const KTexture * const mTexture;
public:
    KDrawBoard(
            const Vector<KVector>& aVertex,
            const KTexture* aTexture = NULL
            );
    virtual ~KDrawBoard() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    /**
     * \~english
     * @brief translate the Polygon.
     * @param aVec destination coordinates
     * \~japanese
     * @brief ポリゴンを移動させます。
     * @param aVec 移動先座標
     */
    void translate(const KVector& aVec);
    /**
     * \~english
     * @brief rotate Polygon.
     * @param aOrigin rotation origin
     * @param aQuater rotation information
     * \~japanese
     * @brief ポリゴンを回転させます。
     * @param aOrigin 回転原点
     * @param aQuater 回転情報
     */
    void rotate(const KQuaternion& aQuater);

    /**
     * \~english
     * @brief  get position vector.
     * @return position vector
     * \~japanese
     * @brief  位置ベクトルを取得します。
     * @return 位置ベクトル
     */
    const KVector& position() const;
    /**
     * \~english
     * @brief  get normal vector.
     * @return normal vector
     * \~japanese
     * @brief  法線ベクトルを取得します。
     * @return 法線ベクトル
     */
    const KVector& normal() const;
};

#endif /* KDRAWBOARD_H */

