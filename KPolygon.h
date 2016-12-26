/**
 * @file   KPolygon.h
 * @brief  KPolygon
 * @author Maeda Takumi
 */
#ifndef KPOLYGON_H
#define KPOLYGON_H

#include "KUtility.h"
#include "KVector.h"

class KSegment;

/**
 * @brief  \~english  Polygon for collision determination
 * @brief  \~japanese 衝突判定用ポリゴン
 * @author \~ Maeda Takumi
 */
class KPolygon {
public:
    /**
     * @brief \~english  vertex list
     * @brief \~japanese 頂点リスト
     */
    Vector<KVector> mVertex;
    /**
     * @brief \~english  normal vector
     * @brief \~japanese 法線ベクトル
     */
    KVector mNormal;

    KPolygon() = default;
    KPolygon(const Vector<KVector>& aVertex);
    KPolygon(const KPolygon& orig) = default;
    virtual ~KPolygon() = default;

    /**
     * \~english
     * @brief  evaluate collision with Point.
     * @param  aPoint target Point
     * @return collision determination
     * \~japanese
     * @brief  点との衝突判定を評価します。
     * @param  aPoint 対象点(位置ベクトル)
     * @return 衝突判定
     */
    bool operator*(const KVector& aPoint) const;
    /**
     * \~english
     * @brief  evaluate collision with Segment.
     * @param  aSegment target Segment
     * @return collision determination
     * \~japanese
     * @brief  線分との衝突判定を評価します。
     * @param  aSegment 対象線分
     * @return 衝突判定
     * 
     */
    bool operator*(const KSegment& aSegment) const;

    /**
     * \~english
     * @brief  compute intersection with Segment.
     * @param  aSegment target Segment
     * @return intersection
     * @note   returne value is intersection with Plane.
     * @note   When not intersecting, return zero vector.
     * \~japanese
     * @brief  線分との交点を計算します。
     * @param  aSegment 対象線分
     * @return 交点
     * @note   返される交点は面との交点です。(ポリゴン上にあるとは限りません。)
     * @note   交差していないときはゼロベクトルを返します。
     */
    KVector hitPoint(const KSegment& aSegment) const;
};

#endif /* KPOLYGON_H */

