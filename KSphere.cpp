/**
 * @file   KSphere.h
 * @brief  KSphere
 * @author Maeda Takumi
 */
#include "KSphere.h"

#include "KCylinder.h"
#include "KMath.h"
#include "KSegment.h"

KSphere::KSphere(
        const KVector& aPosition,
        const float& aRadius
        ) :
mPosition(aPosition),
mRadius(aRadius) {
}

bool KSphere::operator*(const KSphere& aSphere) const {
    return (mPosition - aSphere.mPosition).length() <= mRadius + aSphere.mRadius;
}

bool KSphere::operator*(const KSegment& aSegment) const {
    KVector vec1(mPosition - aSegment.mVec1);
    KVector vec2(mPosition - aSegment.mVec2);
    KVector seg(aSegment.mVec2 - aSegment.mVec1);
    KVector para(vec1.extractParallel(seg));

    if (seg.length() == 0.0f) { // 線分の長さがないときは点として判定
        return vec1.length() < mRadius;
    }

    //  中心座標から線分に垂らした垂線との交点による内分比
    float t(para.length() / seg.length());

    float dist; // 中心座標と線分の最短距離
    if (0 < t && t < 1) dist = (para - vec1).length();
    else { // 交点が線分上にない(線分の端との距離を計測)
        if (t < 0) dist = vec1.length();
        if (1 < t) dist = vec2.length();
    }
    return dist < mRadius;
}

bool KSphere::operator*(const KCylinder& aCylinder) const {
    KSegment seg(aCylinder.mVec1, aCylinder.mVec2);
    if (!aCylinder.mRounding) {
        KVector dir(seg.direction());
        float len(seg.length() / 2);
        KVector center(seg.mVec1 + dir * len);
        float lenDiff(Math::max(0.0f, len - aCylinder.mWidth));
        seg = KSegment(center + dir * lenDiff, center - dir * lenDiff);
    }
    return KSphere(mPosition, mRadius + aCylinder.mWidth) * seg;
}

