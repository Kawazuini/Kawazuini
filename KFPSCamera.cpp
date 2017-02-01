/**
 * @file   KFPSCamera.cpp
 * @brief  KFPSCamera
 * @author Maeda Takumi
 */
#include "KFPSCamera.h"

#include "KUtility.h"
#include "KQuaternion.h"

const KVector KFPSCamera::BASE_DIRECTION(0, 0, -1);

KFPSCamera::KFPSCamera(KVector& aPosition, KVector& aDirection) :
mFPSPosition(aPosition),
mFPSDirection(aDirection),
mVerticalAngle(0) {
    mFPSDirection = mDirection = BASE_DIRECTION;
    set();
}

void KFPSCamera::update() {
    mPosition = mFPSPosition;
    mDirection = mFPSDirection;
    set();
}

void KFPSCamera::move(const KVector& aMovement) {
    mFPSPosition += convertDirection(aMovement);
}

void KFPSCamera::rotate(const float& aVAngle, const float& aHAngle) {
    static const float LIMIT = Math::PI / 2 - Math::EPSILON;

    float pVAngle(mVerticalAngle);
    mVerticalAngle = Math::max(-LIMIT, Math::min(mVerticalAngle + aVAngle, LIMIT));

    KQuaternion v(KVector(mFPSDirection.z, 0, -mFPSDirection.x), mVerticalAngle - pVAngle);
    KQuaternion h(KVector(0, 1, 0), aHAngle);
    mFPSDirection = mFPSDirection.rotate(v * h);
    mHeadSlope = mHeadSlope.rotate(v * h);
}

KVector KFPSCamera::convertDirection(const KVector& aVec) {
    KQuaternion rot(BASE_DIRECTION.roundAngle(KVector(mFPSDirection.x, 0, mFPSDirection.z)));
    if (!KVector(rot).length() && rot.t) return -aVec;
    return aVec.rotate(rot);
}

