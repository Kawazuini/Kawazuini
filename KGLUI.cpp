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
mScale((float) SIZE / Math::max(mWindow.getInitialSize().width, mWindow.getInitialSize().height)),
mScreen(SIZE),
mUpdated(false),
mArea(KVector(), mWindow.getInitialSize().end() * mScale),
mAspect((float) mArea.height / mArea.width),
mVertex(4, GL_ARRAY_BUFFER, GL_STREAM_DRAW),
mCoordinate(4, GL_ARRAY_BUFFER, GL_STATIC_DRAW) {
    KDrawer::remove();

    auto coord(mCoordinate.data(GL_WRITE_ONLY));
    (*(coord + 0))[0] = 0.0f;
    (*(coord + 0))[1] = 0.0f;
    (*(coord + 1))[0] = 0.0f;
    (*(coord + 1))[1] = mAspect;
    (*(coord + 2))[0] = 1.0f;
    (*(coord + 2))[1] = mAspect;
    (*(coord + 3))[0] = 1.0f;
    (*(coord + 3))[1] = 0.0f;
}

void KGLUI::draw() const {
    const KCamera::ViewCorner & vc(mCamera.viewCorner());
    const KVector & cPos(mCamera.position());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    KVector * vertex(mVertex.data(GL_WRITE_ONLY));
    for (int i = 0, i_e(mVertex.size()); i < i_e; ++i, ++vertex) {
        *vertex = vc[i] + cPos;
    }

    glDisable(GL_DEPTH_TEST); // 絶対描画
    mScreen.bindON();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    mVertex.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    mCoordinate.bind();
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, mVertex.size());
    mScreen.bindOFF();
    glEnable(GL_DEPTH_TEST);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
    return mWindow.getMousePositionOnScreen() * mScale;
}

const KCamera& KGLUI::camera() const {
    return mCamera;
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

