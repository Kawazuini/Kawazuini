/**
 * @file   KGLScrollPanel.cpp
 * @brief  KGLScrollPanel
 * @author Maeda Takumi
 */
#include "KGLScrollPanel.h"

#include "KGLContent.h"
#include "KGLUI.h"
#include "KListener.h"
#include "KTexture.h"

KGLScrollPanel::KGLScrollPanel(const KRect& aArea) :
KGLPanel(aArea),
mPanelArea(aArea),
mScrollAmount(5) {
}

void KGLScrollPanel::draw(KTexture& aUI) const {
    if (mBackColor & 0xff000000) aUI.drawRect(mArea, mBackColor);
    for (KGLContent* i : mViewList) {
        i->draw(aUI);
        i->mUpdated = false;
    }
}

void KGLScrollPanel::update(KGLUI& aUI) {
    KGLPanel::update(aUI);

    const KMouse & mouse(aUI.window().getListener().mosue());
    int wheel(mouse.wheel());
    if (wheel && mArea.isColision(aUI.mousePosition())) {
        mActive = true;
        mUpdated = true;
        scroll(KVector(0, mScrollAmount * wheel));
    } else if (mUpdated) scroll(KVector());
}

void KGLScrollPanel::addContent(KGLContent& aContent) {
    KGLPanel::addContent(aContent);
    aContent.slide(mScroll);

    // 領域からはみ出してコンテンツが登録される
    KRect & area(aContent.mArea);
    KRect inter(mPanelArea.intersect(area));
    if (!(inter == area)) {
        KVector exp(area.right() - mPanelArea.right(), area.bottom() - mPanelArea.bottom());
        expand(exp);
    }
}

void KGLScrollPanel::removeContent(KGLContent& aContent) {
    KGLPanel::removeContent(aContent);
    for (auto i = mViewList.begin(), i_e(mViewList.end()); i != i_e; ++i) {
        if (*i == &aContent) {
            mViewList.erase(i);
            return;
        }
    }
}

void KGLScrollPanel::expand(const KVector& aExpand) {
    KVector size(mPanelArea.end());
    size += aExpand;
    mPanelArea = KRect(mPanelArea.begin(), size);
}

void KGLScrollPanel::scroll(const KVector& aOffset) {
    mPanelArea = mPanelArea.slide(aOffset);
    mViewList.clear();
    mScroll += aOffset;
    for (KGLContent* i : mContents) {
        i->slide(aOffset);
        const KRect & content(i->area());
        if (mArea.intersect(content) == content) { // 完全に内包
            mViewList.push_back(i);
        }
    }
    if (!(mArea.intersect(mPanelArea) == mArea)) {
        KVector offset;
        if (0 < aOffset.y) offset.y = mArea.y - mPanelArea.y;
        if (aOffset.y < 0) offset.y = mArea.bottom() - mPanelArea.bottom();

        scroll(offset);
    }
}

