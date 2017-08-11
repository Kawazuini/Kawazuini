/**
 * @file   KQuaternion.h
 * @brief  KQuaternion
 * @author Maeda Takumi
 */
#ifndef KQUATERNION_H
#define KQUATERNION_H

#include "KMath.h"

class KVector;

/**
 * @brief  \~english  Quaternion
 * @brief  \~japanese クォータニオン
 * @author \~ Maeda Takumi
 */
class KQuaternion {
public:
    float t; ///< 
    float x; ///< 
    float y; ///< 
    float z; ///< 

    KQuaternion(
            const float& at = 0,
            const float& ax = 0,
            const float& ay = 0,
            const float& az = 0
            );
    KQuaternion(const KVector& aVec, const float& aTheta = Math::PI);
    virtual ~KQuaternion() = default;

    /**
     * @brief 共益を計算する
     * @return 共益クォータニオン
     */
    KQuaternion operator-() const;
    KQuaternion& operator*=(const KQuaternion& aQuaternion);
    KQuaternion operator*(const KQuaternion& aQuaternion) const;
    // 嘘つきメソッド
    KQuaternion& operator/=(const float& aAmount);
    KQuaternion operator/(const float& aAmount) const;

    operator KVector() const;

    KVector axis() const;
    float angle() const;
};

#endif /* KQUATERNION_H */

