/**
 * @file   KFPSCamera.cpp
 * @brief  KFPSCamera
 * @author Maeda Takumi
 */
#include "KFPSCamera.h"

#include "KQuaternion.h"
#include "KUtility.h"

const KVector KFPSCamera::BASE_DIRECTION(0, 0, -1);

KFPSCamera::KFPSCamera(
        KCamera& aCamera,
        KVector& aPosition,
        KVector& aDirection
        ) :
mCamera(aCamera),
mFPSPosition(aPosition),
mFPSDirection(aDirection),
mVerticalAngle(0) {
    mFPSDirection = mCamera.mInformation.mDirection = BASE_DIRECTION;
    mCamera.set();
}

void KFPSCamera::update() {
    mCamera.mInformation.mPosition = mFPSPosition;
    mCamera.mInformation.mDirection = mFPSDirection;
    mCamera.set();
}

void KFPSCamera::move(const KVector& aMovement) {
    mFPSPosition += convertDirection(aMovement);
}

void KFPSCamera::rotate(const float& aVAngle, const float& aHAngle) {
    static const float LIMIT(Math::HALF_PI - Math::EPSILON);

    float pVAngle(mVerticalAngle);
    mVerticalAngle = Math::max(-LIMIT, Math::min(mVerticalAngle + aVAngle, LIMIT));

    KQuaternion v(KVector(mFPSDirection.z, 0, -mFPSDirection.x), mVerticalAngle - pVAngle);
    KQuaternion h(KVector(0, 1, 0), aHAngle);
    mFPSDirection = mFPSDirection.rotate(v * h);
    mCamera.mInformation.mHeadSlope = mCamera.mInformation.mHeadSlope.rotate(v * h);
}

KVector KFPSCamera::convertDirection(const KVector& aVec) {
    KVector para(mFPSDirection.x, 0, mFPSDirection.z);
    KQuaternion rot(BASE_DIRECTION.roundAngle(para));
    if (!KVector(rot).length()) {
        float d(BASE_DIRECTION.dot(para));
        if (0 < d) return aVec;
        else return -aVec;
    }
    return aVec.rotate(rot);
}

