/**
 * @file   KCamera.cpp
 * @brief  KCamera
 * @author Maeda Takumi
 */
#include "KCamera.h"

#include "KMath.h"
#include "KQuaternion.h"
#include "KWindow.h"

const float KCamera::DEFAULT_ANGLE(30.0f);

KVector KCamera::sDirection_UL;
KVector KCamera::sDirection_UR;
KVector KCamera::sDirection_DL;
KVector KCamera::sDirection_DR;

KCamera::KCamera() :
mAngle(DEFAULT_ANGLE),
mAspect(1.0f / KWindow::ASPECT),
mNearLimit(0.1),
mFarLimit(250),
mDirection(0, 0, -1),
mHeadSlope(0, 1, 0) {
    set();
}

void KCamera::set() {
    KVector height(mHeadSlope * tan(mAngle / 360 * Math::PI));
    KVector width(height.rotate(KQuaternion(mDirection, -Math::PI / 2)) * mAspect);

    sDirection_UL = mDirection - width - height;
    sDirection_UR = mDirection + width - height;
    sDirection_DL = mDirection - width + height;
    sDirection_DR = mDirection + width + height;

    int mode;
    glGetIntegerv(GL_MATRIX_MODE, &mode);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(mAngle, mAspect, mNearLimit, mFarLimit);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            DEPLOYMENT(mPosition),
            DEPLOYMENT(mDirection + mPosition),
            DEPLOYMENT(mHeadSlope)
            );

    glMatrixMode(mode);
}

