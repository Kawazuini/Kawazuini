/**
 * @file KQuaternion.h
 * @author Maeda Takumi
 */
#ifndef KQUATERNION_H
#define KQUATERNION_H

#include "KMath.h"


class KVector;

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
    KQuaternion(const KQuaternion& orig) = default;
    virtual ~KQuaternion() = default;

    /**
     * @brief 共益を計算する
     * @return 共益クォータニオン
     */
    KQuaternion operator-() const;
    KQuaternion operator*(const KQuaternion& aQuaternion) const;
    operator KVector() const;
};

#endif /* KQUATERNION_H */

