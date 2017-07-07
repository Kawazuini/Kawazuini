/**
 * @file   KGLSlider.cpp
 * @brief  KGLSlider
 * @author Maeda Takumi
 */
#include "KGLSlider.h"

#include "KGLUI.h"
#include "KListener.h"
#include "KMath.h"
#include "KVector.h"

KGLSlider::KGLSlider(
        const KRect& aArea,
        const SliderType& aType
        ) :
KGLContent(aArea),
mType(aType),
mHold(false),
mSlider(0) {
}

void KGLSlider::draw(KTexture& aUI) const {
    KRect slider(mArea.expand(-1));
    switch (mType) {
        case HORIZON:
            slider.width = Math::max(0, mSlider - 2);
            if (mBackColor && 0xff000000) aUI.drawRect(mArea, mBackColor);
            if (mFrontColor && 0xff000000) aUI.drawRect(slider, mFrontColor);
            break;
        case VERTICAL:
            slider.height = Math::max(0, mSlider - 2);
            if (mBackColor && 0xff000000) aUI.drawRect(mArea, mBackColor);
            if (mFrontColor && 0xff000000) aUI.drawRect(slider, mFrontColor);
            break;
    }
}

void KGLSlider::update(KGLUI& aUI) {
    const KWindow & window(aUI.window());
    const KVector mousePosition(aUI.mousePosition());
    const KSwitch & click(window.mListener->mosue().mLeft);

    if (mArea.isColision(mousePosition) && click.isTouch()) mHold = true;
    if (!click.onFrame()) mHold = false;

    if (mActive = mHold) {
        mUpdated = true;
        switch (mType) {
            case HORIZON:
                mSlider = Math::max(0, Math::min((int) mousePosition.x - mArea.x, mArea.width));
                break;
            case VERTICAL:
                mSlider = Math::max(0, Math::min((int) mousePosition.y - mArea.y, mArea.height));
                break;
        }
    }
}

void KGLSlider::setValue(const double& aValue) {
    mUpdated = true;
    switch (mType) {
        case HORIZON:
            mSlider = Math::max(0.0, Math::min(aValue, 1.0)) * mArea.width;
            break;
        case VERTICAL:
            mSlider = Math::max(0.0, Math::min(aValue, 1.0)) * mArea.height;
            break;
    }
}

double KGLSlider::getValue() const {
    switch (mType) {
        case HORIZON: return (double) mSlider / mArea.width;
        case VERTICAL: return (double) mSlider / mArea.height;
    }
}

