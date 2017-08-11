/**
 * @file   KCylinder.cpp
 * @brief  KCylinder
 * @author Maeda Takumi
 */
#include "KCylinder.h"

#include "KSphere.h"

KCylinder::KCylinder(
        const float& aRadius,
        const KVector& aVec1,
        const KVector& aVec2,
        const bool& aRounding
        ) :
mWidth(aRadius),
mVec1(aVec1),
mVec2(aVec2),
mRounding(aRounding) {
}

bool KCylinder::operator*(const KSphere& aSphere) const {
    return aSphere.operator*(*this);
}

