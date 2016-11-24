/**
 * @file KFPSCamera.cpp
 * @author Maeda Takumi
 */
#include "KFPSCamera.h"

#include "KUtility.h"
#include "KQuaternion.h"

const KVector KFPSCamera::BASE_DIRECTION(0, 0, -1);

KFPSCamera::KFPSCamera() {
    mVirticalAngle = 0;
    mDirection = BASE_DIRECTION;
}

void KFPSCamera::move(const KVector& aMovement) {
    mPosition += convertDirection(aMovement);
    set();
}

void KFPSCamera::rotate(const float& aVAngle, const float& aHAngle) {
    static const float LIMIT = Math::PI / 2 - Math::EPSILON;

    mVirticalAngle = Math::max(-LIMIT, Math::min(mVirticalAngle += aVAngle, LIMIT));

    KQuaternion v(KVector(mDirection.z, 0, -mDirection.x), aVAngle);
    KQuaternion h(KVector(0, 1, 0), aHAngle);
    mDirection = mDirection.rotate(v * h);
    mHeadSlope = mHeadSlope.rotate(v * h);

    set();
}

KVector KFPSCamera::convertDirection(const KVector& aVec) {
    KQuaternion rot = KVector(mDirection.x, 0, mDirection.z).roundAngle(BASE_DIRECTION);
    if (!KVector(rot).length()) return -aVec;
    return aVec.rotate(rot);
}

