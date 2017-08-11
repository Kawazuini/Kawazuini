/**
 * @file   KSegment.h
 * @brief  KSegment
 * @author Maeda Takumi
 */
#ifndef KSEGMENT_H
#define KSEGMENT_H

#include "KVector.h"
#include "KPolygon.h"

class KPolygon;
class KSphere;

/**
 * @brief  \~english  Directed Segment for collision determination
 * @brief  \~japanese 衝突判定用有向線分
 * @author \~ Maeda Takumi
 */
class KSegment final {
public:
    /// @brief \~english  line start
    /// @brief \~japanese 線分始端
    KVector mVec1;
    /// @brief \~english  line termination
    /// @brief \~japanese 線分終端
    KVector mVec2;

    KSegment() = default;
    /**
     * \~english
     * @param aVec1 line start
     * @param aVec2 line termination
     * \~japanese
     * @param aVec1 線分始端
     * @param aVec2 線分終端
     */
    KSegment(const KVector& aVec1, const KVector& aVec2);
    ~KSegment() = default;

    /**
     * \~english
     * @brief  evaluate collision with Polygon.
     * @param  aPolygon target Polygon
     * @return collision determination
     * \~japanese
     * @brief  ポリゴンとの衝突判定を評価します。
     * @param  aPolygon 対象ポリゴン
     * @return 衝突判定
     */
    bool operator*(const KPolygon& aPolygon) const;
    /**
     * \~english
     * @brief  evaluate collision with Sphere.
     * @param  aSphere target Sphere
     * @return collision determination
     * \~japanese
     * @brief  球体との衝突判定を評価します。
     * @param  aSphere 対象球体
     * @return 衝突判定
     */
    bool operator*(const KSphere& aSphere) const;

    float length() const;
    KVector direction() const;
};

#endif /* KSEGMENT_H */

