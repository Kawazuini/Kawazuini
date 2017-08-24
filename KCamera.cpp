/**
 * @file   KCamera.cpp
 * @brief  KCamera
 * @author Maeda Takumi
 */
#include "KCamera.h"

#include "KMath.h"
#include "KQuaternion.h"
#include "KWindow.h"

const float KCamera::DEFAULT_VIEWANGLE(30.0f);
const float KCamera::DEFAULT_NEARLIMIT(0.1f);
const float KCamera::DEFAULT_FARLIMIT(250.0f);

KCamera::KCamera(const KWindow& aWindow) :
mWindow(aWindow),
mOption({DEFAULT_VIEWANGLE, 1.0f / aWindow.getInitialAspect(), DEFAULT_NEARLIMIT, DEFAULT_FARLIMIT}),
mInformation({KVector(), KVector(0, 0, -1), KVector(0, 1, 0)}) {
    set();
}

void KCamera::set() {
    mHalfHeight = mInformation.mHeadSlope * tan(Math::toRadian(mOption.mAngle / 2));
    mHalfWidth = mHalfHeight.rotate(KQuaternion(mInformation.mDirection, -Math::HALF_PI)) * mOption.mAspect;

    mViewCorner[0] = mInformation.mDirection - mHalfWidth + mHalfHeight;
    mViewCorner[1] = mInformation.mDirection - mHalfWidth - mHalfHeight;
    mViewCorner[2] = mInformation.mDirection + mHalfWidth - mHalfHeight;
    mViewCorner[3] = mInformation.mDirection + mHalfWidth + mHalfHeight;

    int mode;
    glGetIntegerv(GL_MATRIX_MODE, &mode);

    // 視点位置(処理簡略)
    KVector eyePos(mInformation.mDirection + mInformation.mPosition);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            mOption.mAngle,
            mOption.mAspect,
            mOption.mNearLimit,
            mOption.mFarLimit
            );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            DEPLOY_VEC(mInformation.mPosition),
            DEPLOY_VEC(eyePos),
            DEPLOY_VEC(mInformation.mHeadSlope)
            );

    glMatrixMode(mode);
}

void KCamera::translate(const KVector& aPosition) {
    mInformation.mPosition = aPosition;
}

void KCamera::rotate(const KQuaternion& aQuaternion) {
    mInformation.mDirection = mInformation.mDirection.rotate(aQuaternion);
    mInformation.mHeadSlope = mInformation.mHeadSlope.rotate(aQuaternion);
}

void KCamera::zoom(const float& aScale) {
    mOption.mAngle = DEFAULT_VIEWANGLE * aScale;
}

bool KCamera::isInCamera(const KVector& aNormal) const {
    return aNormal.dot(mViewCorner[0]) <= 0
            || aNormal.dot(mViewCorner[1]) <= 0
            || aNormal.dot(mViewCorner[2]) <= 0
            || aNormal.dot(mViewCorner[3]) <= 0;
}

bool KCamera::isInCamera(const Vector<KVector>& aVertex) const {
    static float HALF_PI(Math::PI / 2);
    for (KVector i : aVertex) {
        // 頂点が画面内に存在する
        if (Math::abs((i - mInformation.mPosition).angle(mInformation.mDirection)) < HALF_PI) return true;
    }
    return false;
}

const KCamera::ViewCorner& KCamera::viewCorner() const {
    return mViewCorner;
}

const KWindow& KCamera::window() const {
    return mWindow;
}

const KVector& KCamera::position() const {
    return mInformation.mPosition;
}

const KVector& KCamera::direction() const {
    return mInformation.mDirection;
}

const KVector& KCamera::headslope() const {
    return mInformation.mHeadSlope;
}

const KVector& KCamera::halfWidth() const {
    return mHalfWidth;
}

const KVector& KCamera::halfHeight() const {
    return mHalfHeight;
}

