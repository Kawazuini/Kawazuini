/**
 * @file   KSphere.h
 * @brief  KSphere
 * @author Maeda Takumi
 */
#include "KSphere.h"

KSphere::KSphere(const float& aRadius) :
mPosition(mDummy) {
}

KSphere::KSphere(KVector& aPosition, const float& aRadius) :
mPosition(aPosition),
mRadius(aRadius) {
}

bool KSphere::operator*(const KSphere& aSphere) const {
    float length = (mPosition - aSphere.mPosition).length();
    return length <= mRadius + aSphere.mRadius;
}
