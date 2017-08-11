/**
 * @file   KSegment.h
 * @brief  KSegment
 * @author Maeda Takumi
 */
#include "KSegment.h"
#include "KSphere.h"

KSegment::KSegment(const KVector& aVec1, const KVector& aVec2) {
    mVec1 = aVec1;
    mVec2 = aVec2;
}

float KSegment::length() const {
    return (mVec1 - mVec2).length();
}

KVector KSegment::direction() const {
    return (mVec2 - mVec1).normalization();
}

bool KSegment::operator*(const KPolygon& aPolygon) const {
    return aPolygon.operator*(*this);
}

bool KSegment::operator*(const KSphere& aSphere) const {
    return aSphere.operator*(*this);
}

