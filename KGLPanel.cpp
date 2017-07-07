/**
 * @file   KGLPanel.cpp
 * @brief  KGLPanel
 * @author Maeda Takumi
 */
#include "KGLPanel.h"

#include "KTexture.h"
#include "KGLUI.h"
#include "KVector.h"

KGLPanel::KGLPanel(const KRect& aArea) :
KGLContent(aArea) {
}

void KGLPanel::draw(KTexture& aUI) const {
    if (mBackColor & 0xff000000) aUI.drawRect(mArea, mBackColor);
    for (KGLContent* i : mContents) {
        i->draw(aUI);
        i->mUpdated = false;
    }
}

void KGLPanel::update(KGLUI& aUI) {
    mActive = false;
    for (KGLContent* i : mContents) {
        i->update(aUI);
        if (i->mUpdated) mUpdated = true;
        if (i->mActive) mActive = true;
    }
    if (!mActive) mActive = mArea.isColision(aUI.mousePosition());
}

void KGLPanel::addContent(KGLContent& aContent) {
    aContent.setParent(this);
    mContents.push_back(&aContent);
}

void KGLPanel::removeContent(KGLContent& aContent) {
    mUpdated = true;
    for (auto i = mContents.begin(), i_e(mContents.end()); i != i_e; ++i) {
        if (*i == &aContent) {
            mContents.erase(i);
            return;
        }
    }
}

void KGLPanel::slide(const KVector& aSlide) {
    KGLContent::slide(aSlide);

    for (KGLContent* i : mContents) {
        i->slide(aSlide);
    }
}
