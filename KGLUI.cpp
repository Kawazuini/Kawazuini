/**
 * @file   KGLUI.cpp
 * @brief  KGLUI
 * @author Maeda Takumi
 */
#include "KGLUI.h"

#include "KCamera.h"
#include "KGLContent.h"
#include "KMath.h"
#include "KQuaternion.h"
#include "KWindow.h"

const int KGLUI::SIZE(1024);

KGLUI::KGLUI(const KCamera& aCamera) :
mCamera(aCamera),
mWindow(mCamera.window()),
mScale((float) SIZE / Math::max(mWindow.initialSize().width, mWindow.initialSize().height)),
mScreen(SIZE),
mUpdated(false),
mArea(KVector(), mWindow.initialSize().end() * mScale),
mAspect((float) mArea.height / mArea.width) {
    KDrawer::remove();
}

void KGLUI::draw() const {    
    const KCamera::ViewCorner & vc(mCamera.viewCorner());
    const KVector & cPos(mCamera.position());
    const KVector & cDirect(mCamera.direction());
    KVector corner[4]{// UI描画角座標
        vc[2] + cPos,
        vc[0] + cPos,
        vc[1] + cPos,
        vc[3] + cPos,
    };

    glDisable(GL_DEPTH_TEST); // 絶対描画
    glNormal3f(DEPLOY_VEC(-cDirect));
    mScreen.bindON();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3f(DEPLOY_VEC(corner[0]));
    glTexCoord2f(0, mAspect);
    glVertex3f(DEPLOY_VEC(corner[1]));
    glTexCoord2f(1, mAspect);
    glVertex3f(DEPLOY_VEC(corner[2]));
    glTexCoord2f(1, 0);
    glVertex3f(DEPLOY_VEC(corner[3]));
    glEnd();
    mScreen.bindOFF();
    glEnable(GL_DEPTH_TEST);
}

void KGLUI::update() {
    for (KGLContent* i : mComponents) i->update(*this);
}

void KGLUI::refrect() {
    bool update(false);
    for (KGLContent* i : mComponents) {
        if (i->mUpdated) {
            update = true;
            mScreen.clearRect(i->mArea);
            i->draw(mScreen);
            i->mUpdated = false;
        }
    }
    if (mUpdated || update) {
        mUpdated = false;
        mScreen.reflect();
    }
}

void KGLUI::addContent(KGLContent& aContent) {
    mComponents.push_back(&aContent);
}

bool KGLUI::isContentsActive() const {
    for (KGLContent* i : mComponents) {
        if (i->isActive()) return true;
    }
    return false;
}

KVector KGLUI::mousePosition() const {
    return mWindow.mousePositionOnScreen() * mScale;
}

const KWindow& KGLUI::window() const {
    return mWindow;
}

KTexture& KGLUI::screen() {
    mUpdated = true;
    return mScreen;
}

const KRect& KGLUI::area() const {
    return mArea;
}

