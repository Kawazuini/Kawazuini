/**
 * @file   KSphere.h
 * @brief  KSphere
 * @author Maeda Takumi
 */
#include "KSphere.h"

#include "KSegment.h"

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

bool KSphere::operator*(const KSegment& aSegment) const {
    KVector vec(mPosition - aSegment.mVec1);
    float t(vec.dot(aSegment.direction()) / aSegment.length()); // 線分の中心座標からの垂線との交点による内分比
    float dist(((aSegment.mVec2 - aSegment.mVec1) * t - vec).length()); // 中心座標と線分の最短距離
    if (t < 0) dist = vec.length();
    if (t > 1) dist = (mPosition - aSegment.mVec2).length();

    return dist < mRadius;
}

