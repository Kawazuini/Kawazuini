/**
 * @file   KCamera.cpp
 * @brief  KCamera
 * @author Maeda Takumi
 */
#include "KCamera.h"

#include "KMath.h"
#include "KQuaternion.h"
#include "KWindow.h"

KVector KCamera::sPosition;
KVector KCamera::sDirection;
KVector KCamera::sDirection_UL;
KVector KCamera::sDirection_UR;
KVector KCamera::sDirection_DL;
KVector KCamera::sDirection_DR;

KCamera::KCamera() {
    mAngle = 30;
    mAspect = 1.0f / KWindow::ASPECT;
    mNearLimit = 0.1;
    mFarLimit = 250;

    mPosition = KVector(0, 0, 0);
    mDirection = KVector(0, 0, -1);
    mHeadSlope = KVector(0, 1, 0);
    set();
}

void KCamera::set() {
    sPosition = mPosition;
    sDirection = mDirection;

    KVector center = mPosition + mDirection;
    KVector height = mHeadSlope * tan(mAngle / 360 * Math::PI);
    KVector width = height.rotate(KQuaternion(mDirection, -Math::PI / 2)) * mAspect;

    sDirection_UL = center - width - height;
    sDirection_UR = center + width - height;
    sDirection_DL = center - width + height;
    sDirection_DR = center + width + height;

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

