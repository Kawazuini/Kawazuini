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

KGLUI::KGLUI() : mScreen(new KTexture(WIDTH)) {
    KDrawer::erase();
    draw();
}

KGLUI::~KGLUI() {
    delete mScreen;
}

void KGLUI::draw() const {
    mScreen->reflect();

    glDisable(GL_DEPTH_TEST);
    mScreen->bindON();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3f(DEPLOYMENT(KCamera::sDirection_DL));
    glTexCoord2f(0, KWindow::ASPECT);
    glVertex3f(DEPLOYMENT(KCamera::sDirection_UL));
    glTexCoord2f(1, KWindow::ASPECT);
    glVertex3f(DEPLOYMENT(KCamera::sDirection_UR));
    glTexCoord2f(1, 0);
    glVertex3f(DEPLOYMENT(KCamera::sDirection_DR));
    glEnd();
    mScreen->bindOFF();
    glEnable(GL_DEPTH_TEST);
}
