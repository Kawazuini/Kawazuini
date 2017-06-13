/**
 * @file   KGLPanel.cpp
 * @brief  KGLPanel
 * @author Maeda Takumi
 */
#include "KGLPanel.h"

#include "KTexture.h"

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
}

void KGLPanel::addContent(KGLContent& aContent) {
    mContents.push_back(&aContent);
}
