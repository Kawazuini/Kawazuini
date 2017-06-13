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

KVector KCamera::sPosition;
KVector KCamera::sDirection;
float KCamera::sAngle;
KCamera::ViewCorner KCamera::sViewCorner;

KCamera::KCamera(const KWindow& aWindow) :
mWindow(aWindow),
mOption({DEFAULT_VIEWANGLE, 1.0f / aWindow.initialAspect(), 0.1f, 250.0f}),
mInformation({KVector(), KVector(0, 0, -1), KVector(0, 1, 0)}) {
    set();
}

void KCamera::set() {
    mHeight = mInformation.mHeadSlope * tan(Math::toRadian(mOption.mAngle / 2));
    mWidth = mHeight.rotate(KQuaternion(mInformation.mDirection, -Math::HALF_PI)) * mOption.mAspect;

    sPosition = mInformation.mPosition;
    sDirection = mInformation.mDirection;
    sAngle = mOption.mAngle;
    sViewCorner[0] = mInformation.mDirection - mWidth - mHeight;
    sViewCorner[1] = mInformation.mDirection + mWidth - mHeight;
    sViewCorner[2] = mInformation.mDirection - mWidth + mHeight;
    sViewCorner[3] = mInformation.mDirection + mWidth + mHeight;

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

void KCamera::zoom(const float& aScale) {
    mOption.mAngle = DEFAULT_VIEWANGLE * aScale;
}

bool KCamera::isInCamera(const KVector& aNormal) {
    return aNormal.dot(sViewCorner[0]) <= 0
            || aNormal.dot(sViewCorner[1]) <= 0
            || aNormal.dot(sViewCorner[2]) <= 0
            || aNormal.dot(sViewCorner[3]) <= 0;
}

bool KCamera::isInCamera(const Vector<KVector>& aVertex) {
    static float HALF_PI(Math::PI / 2);
    for (KVector i : aVertex) {
        // 頂点が画面内に存在する
        if (Math::abs((i - sPosition).angle(sDirection)) < HALF_PI) return true;
    }
    return false;
}

const KCamera::ViewCorner& KCamera::viewCorner() {
    return sViewCorner;
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

const KVector& KCamera::width() const {
    return mWidth;
}

const KVector& KCamera::height() const {
    return mHeight;
}

const KVector& KCamera::Position() {
    return sPosition;
}

const KVector& KCamera::Direction() {
    return sDirection;
}

