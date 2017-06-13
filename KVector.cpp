/**
 * @file   KVector.cpp
 * @brief  KVector
 * @author Maeda Takumi
 */
#include "KVector.h"

#include "KMath.h"
#include "KQuaternion.h"

KVector::KVector(const float& ax, const float& ay, const float& az) :
x(ax),
y(ay),
z(az) {
}

KVector::KVector(const POINT& aPoint)
: KVector(aPoint.x, aPoint.y) {
}

bool KVector::operator==(const KVector& aVec) const {
    return Math::approximately(x, aVec.x) && Math::approximately(y, aVec.y) && Math::approximately(z, aVec.z);
}

bool KVector::operator!=(const KVector& aVec) const {
    return !this->operator==(aVec);
}

KVector KVector::operator-() const {
    return KVector(-x, -y, -z);
}

KVector& KVector::operator+=(const KVector& aVec) {
    x += aVec.x;
    y += aVec.y;
    z += aVec.z;

    return *this;
}

KVector& KVector::operator-=(const KVector& aVec) {
    return *this += (-aVec);
}

KVector& KVector::operator*=(const float& aTimes) {
    x *= aTimes;
    y *= aTimes;
    z *= aTimes;

    return *this;
}

KVector& KVector::operator/=(const float& aTimes) {
    x /= aTimes;
    y /= aTimes;
    z /= aTimes;

    return *this;
}

KVector KVector::operator+(const KVector& aVec) const {
    return KVector(*this) += aVec;
}

KVector KVector::operator-(const KVector& aVec) const {
    return *this +(-aVec);
}

KVector KVector::operator*(const float& aTimes) const {
    return KVector(*this) *= aTimes;
}

KVector KVector::operator/(const float& aTimes) const {
    return KVector(*this) /= aTimes;
}

KVector::operator POINT() const {
    return POINT{(int) x, (int) y};
}

KVector KVector::normalization() const {
    float len(length());
    if (len) return *this / len;
    return *this;
}

float KVector::dot(const KVector& aVec) const {
    return x * aVec.x + y * aVec.y + z * aVec.z;
}

KVector KVector::cross(const KVector& aVec) const {
    return KVector(
            y * aVec.z - z * aVec.y,
            z * aVec.x - x * aVec.z,
            x * aVec.y - y * aVec.x
            );
}

KVector KVector::extractParallel(const KVector& aVec) const {
    return aVec * this->dot(aVec) / aVec.dot(aVec);
}

KVector KVector::extractVertical(const KVector& aVec) const {
    return *this -extractParallel(aVec);
}

KVector KVector::rotate(const KQuaternion& aQuaternion) const {
    if (KVector(aQuaternion).isZero()) { // 回転軸が零ベクトル
        return *this; // 回転がない
    }
    float len(length());
    if (len) return KVector((-aQuaternion) * KQuaternion(*this) * aQuaternion).normalization() * len;
    return *this;
}

float KVector::length() const {
    return sqrt(x * x + y * y + z * z);
}

float KVector::lengthSquared() const {
    return x * x + y * y + z * z;
}

float KVector::angle(const KVector& aVec) const {
    float len1(length()), len2(aVec.length());
    if (len1 && len2) return acos(Math::max(-1.0f, Math::min(dot(aVec) / (len1 * len2), 1.0f)));
    return 0;
}

KQuaternion KVector::roundAngle(const KVector& aVec) const {
    return KQuaternion(cross(aVec), -angle(aVec));
}

void KVector::fit(const KVector& aVec) {
    if (abs(aVec.x) < abs(x)) x = aVec.x;
    if (abs(aVec.y) < abs(y)) y = aVec.y;
    if (abs(aVec.z) < abs(z)) z = aVec.z;
}

bool KVector::isZero() const {
    static const KVector ZERO;
    return *this == ZERO;
}

