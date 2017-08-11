/**
 * @file   KQuaternion.cpp
 * @brief  KQuaternion
 * @author Maeda Takumi
 */
#include "KQuaternion.h"

#include "KVector.h"

KQuaternion::KQuaternion(
        const float& at,
        const float& ax,
        const float& ay,
        const float& az
        ) :
t(at),
x(ax),
y(ay),
z(az) {
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

KQuaternion& KQuaternion::operator*=(const KQuaternion& aQuaternion) {
    KVector v1(*this), v2(aQuaternion);
    KVector tmp(v1 * aQuaternion.t + v2 * t + v1.cross(v2));
    t = t * aQuaternion.t - v1.dot(v2);
    x = tmp.x;
    y = tmp.y;
    z = tmp.z;
    return *this;
}

KQuaternion KQuaternion::operator*(const KQuaternion& aQuaternion) const {
    return KQuaternion(*this) *= aQuaternion;
}

KQuaternion& KQuaternion::operator/=(const float& aAmount) {
    float tmp = acos(t) * 2;
    *this = KQuaternion(KVector(x, y, z), tmp / aAmount);
    return *this;
}

KQuaternion KQuaternion::operator/(const float& aAmount) const {
    return KQuaternion(*this) /= aAmount;
}

KQuaternion::operator KVector() const {
    return KVector(x, y, z);
}

KVector KQuaternion::axis() const {
    return operator KVector().normalization();
}

float KQuaternion::angle() const {
    return acos(t) * 2;
}

