/**
 * @file   KCylinder.h
 * @brief  KCylinder
 * @author Maeda Takumi
 */
#ifndef KCYLINDER_H
#define KCYLINDER_H

#include "KVector.h"

class KSphere;

/**
 * @brief  \~english  Cylinder for collision determination
 * @brief  \~japanese 衝突判定用円筒
 * @author \~ Maeda Takumi
 */
class KCylinder final {
public:
    /// @brief \~english  radius of Sphere
    /// @brief \~japanese 半径
    float mWidth;
    /// @brief \~english  line start
    /// @brief \~japanese 始端
    KVector mVec1;
    /// @brief \~english  line termination
    /// @brief \~japanese 終端
    KVector mVec2;
    /// @brief \~english  End shape (Spherical if true)
    /// @brief \~japanese 端形状(trueなら球形)
    bool mRounding;

    /**
     * \~english
     * @param aRadius radius
     * @param aVec1   line start
     * @param aVec2   line termination
     * \~japanese
     * @param aRadius 半径
     * @param aVec1   線分始端
     * @param aVec2   線分終端
     */
    KCylinder(
            const float& aRadius,
            const KVector& aVec1,
            const KVector& aVec2,
            const bool& aRounding = true
            );
    ~KCylinder() = default;

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
};

#endif /* KCYLINDER_H */

