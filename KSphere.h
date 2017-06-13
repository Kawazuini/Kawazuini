/**
 * @file   KSphere.h
 * @brief  KSphere
 * @author Maeda Takumi
 */
#ifndef KSPHERE_H
#define KSPHERE_H

#include "KVector.h"

class KSegment;

/**
 * @brief  \~english  Sphere for collision determination
 * @brief  \~japanese 衝突判定用球体
 * @author \~ Maeda Takumi
 */
class KSphere {
private:
    /* ダミー座標 */ KVector mDummy;
public:
    /**
     * @brief \~english  center coordinate
     * @brief \~japanese 中心座標
     */
    KVector& mPosition;
    /**
     * @brief \~english  radius of Sphere
     * @brief \~japanese 半径
     */
    float mRadius;

    /**
     * \~english
     * @param aRadius radius
     * \~japanese
     * @param aRadius 半径
     */
    KSphere(const float& aRadius = 0.0f);
    /**
     * \~english
     * @param aPosition coordinates to be synchronized
     * @param aRadius   radius
     * \~japanese
     * @param aPosition 同期する座標
     * @param aRadius   半径
     */
    KSphere(KVector& aPosition, const float& aRadius = 0.0f);
    virtual ~KSphere() = default;

    /**
     * \~english
     * @brief  evaluate collision with Sphere.
     * @param  aSphere target Sphere
     * @return collision determination
     * \~japanese
     * @brief  球体との衝突判定を評価します。
     * @param  aSegment 対象球体
     * @return 衝突判定
     */
    bool operator*(const KSphere& aSphere) const;
    /**
     * \~english
     * @brief  evaluate collision with Segment.
     * @param  aSphere target Segment
     * @return collision determination
     * \~japanese
     * @brief  線分との衝突判定を評価します。
     * @param  aSegment 対象線分
     * @return 衝突判定
     */
    bool operator*(const KSegment& aSegment) const;
};

#endif /* KSPHERE_H */

