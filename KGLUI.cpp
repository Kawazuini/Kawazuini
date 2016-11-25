/**
 * @file KGLUI.cpp
 * @author Maeda Takumi
 */
#include "KGLUI.h"

#include "KCamera.h"
#include "KMath.h"
#include "KQuaternion.h"
#include "KTexture.h"
#include "KWindow.h"

const int KGLUI::WIDTH = 1024;
const int KGLUI::HEIGHT = WIDTH * KWindow::ASPECT;

KGLUI::KGLUI(const KCamera& aCamera) :
mCamera(&aCamera),
mScreen(new KTexture(WIDTH)) {
}

KGLUI::~KGLUI() {
    delete[] mScreen;
}

void KGLUI::draw() const {
    KVector center = mCamera->mPosition + mCamera->mDirection;
    KVector height = mCamera->mHeadSlope * tan(mCamera->mAngle / 360 * Math::PI);
    KVector width = height.rotate(KQuaternion(mCamera->mDirection, -Math::PI / 2)) / KWindow::ASPECT;

    mScreen->update();

    mScreen->bindON();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(DEPLOYMENT(center - width + height));
    glTexCoord2f(0, KWindow::ASPECT);
    glVertex3f(DEPLOYMENT(center - width - height));
    glTexCoord2f(1, KWindow::ASPECT);
    glVertex3f(DEPLOYMENT(center + width - height));
    glTexCoord2f(1, 0);
    glVertex3f(DEPLOYMENT(center + width + height));
    glEnd();
    mScreen->bindOFF();
}
