/**
 * @file KQuaternion.cpp
 * @author Maeda Takumi
 */
#include "KQuaternion.h"

#include "KVector.h"

KQuaternion::KQuaternion(
        const float& at,
        const float& ax,
        const float& ay,
        const float& az
        ) {
    t = at;
    x = ax;
    y = ay;
    z = az;
}

KQuaternion::KQuaternion(const KVector& aVec, const float& aTheta) {
    t = cos(aTheta / 2);
    KVector tmp = aVec.normalization() * sin(aTheta / 2);
    x = tmp.x;
    y = tmp.y;
    z = tmp.z;
}

KQuaternion KQuaternion::operator-() const {
    return KQuaternion(t, -x, -y, -z);
}

KQuaternion KQuaternion::operator*(const KQuaternion& aQuaternion) const {
    KVector v1 = KVector(*this), v2 = KVector(aQuaternion);
    float tmp = t * aQuaternion.t - v1.dot(v2);
    KVector tmp2 = v1 * aQuaternion.t + v2 * t + v1.cross(v2);
    return KQuaternion(tmp, tmp2.x, tmp2.y, tmp2.z);
}

KQuaternion::operator KVector() const {
    return KVector(x, y, z);
}
