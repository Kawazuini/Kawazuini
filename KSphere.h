/**
 * @file   KSphere.h
 * @brief  KSphere
 * @author Maeda Takumi
 */
#ifndef KSPHERE_H
#define KSPHERE_H

#include "KVector.h"

/**
 * @brief  \~english  Sphere for collision determination
 * @brief  \~japanese 衝突判定用球体
 * @author \~ Maeda Takumi
 */
class KSphere {
private:
    /**
     * @brief \~english  dummy coordinates
     * @brief \~japanese ダミー座標
     */
    KVector mDummy;
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

    KSphere(const float& aRadius = 0.0f);
    KSphere(KVector& aPosition, const float& aRadius = 0.0f);
    KSphere(const KSphere& orig) = default;
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
     * 
     */
    bool operator*(const KSphere& aSphere) const;
};

#endif /* KSPHERE_H */

