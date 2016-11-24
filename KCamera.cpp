/**
 * @file KCamera.cpp
 * @athor Maeda Takumi
 */
#include "KCamera.h"

#include "KWindow.h"

KCamera::KCamera() {
    mAngle = 30;
    mAspect = 1 / KWindow::ASPECT;
    mNearLimit = 0.1;
    mFarLimit = 1000;

    mPosition = KVector(0, 0, 0);
    mDirection = KVector(0, 0, -1);
    mHeadSlope = KVector(0, 1, 0);
    set();
}

void KCamera::set() {
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
}

