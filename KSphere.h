/**
 * @file   KSphere.h
 * @brief  KSphere
 * @author Maeda Takumi
 */
#ifndef KSPHERE_H
#define KSPHERE_H

#include "KVector.h"
#include "KCylinder.h"

class KCylinder;
class KSegment;

/**
 * @brief  \~english  Sphere for collision determination
 * @brief  \~japanese 球状の衝突判定
 * @author \~ Maeda Takumi
 */
class KSphere final {
public:
    /// @brief \~english  center coordinate
    /// @brief \~japanese 中心座標
    KVector mPosition;
    /// @brief \~english  radius of Sphere
    /// @brief \~japanese 半径
    float mRadius;

    /**
     * \~english
     * @param aPosition center coordinate
     * @param aRadius   radius
     * \~japanese
     * @param aPosition 中心座標
     * @param aRadius   半径
     */
    KSphere(
            const KVector& aPosition,
            const float& aRadius
            );
    ~KSphere() = default;

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
    /**
     * \~english
     * @brief  evaluate collision with Segment.
     * @param  aSegment target Segment
     * @return collision determination
     * \~japanese
     * @brief  線分との衝突判定を評価します。
     * @param  aSegment 対象線分
     * @return 衝突判定
     */
    bool operator*(const KSegment& aSegment) const;
    /**
     * \~english
     * @brief  evaluate collision with Cylinder.
     * @param  aCylinder target Cylinder
     * @return collision determination
     * \~japanese
     * @brief  円筒との衝突判定を評価します。
     * @param  aCylinder 対象円筒
     * @return 衝突判定
     */
    bool operator*(const KCylinder& aCylinder) const;
};

#endif /* KSPHERE_H */

