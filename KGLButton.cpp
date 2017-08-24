/**
 * @file   KGLButton.cpp
 * @brief  KGLButton
 * @author Maeda Takumi
 */
#include "KGLButton.h"

#include "KGLUI.h"
#include "KListener.h"
#include "KTexture.h"
#include "KVector.h"
#include "KWindow.h"
#include "KEventListener.h"

const String KGLButton::ACTION_CURSOR("Cursor on Button");
const String KGLButton::ACTION_PRESS("Pressed");
const String KGLButton::ACTION_RELEASE("Released");

KGLButton::KGLButton(const KRect& aArea) :
KGLContent(aArea),
mCondition(false),
mHold(false) {
    KEvent::remove();
}

void KGLButton::draw(KTexture& aUI) const {
    if (mBackColor & 0xff000000) aUI.drawClearRect(mArea, mBackColor);
    if (mFrontColor & 0xff000000) aUI.drawRect(mArea.expand(-1), mFrontColor);
}

void KGLButton::update(KGLUI& aUI) {
    const KWindow & window(aUI.window());
    const KSwitch & click(window.getListener().mosue().mLeft);

    if (!click.onFrame()) mHold = false;
    if (mArea.isColision(aUI.mousePosition())) {
        mActive = true;
        mCondition = true;
        if (click.onFrame()) {
            mHold = true;
            mActionCommand = ACTION_PRESS;
        } else if (!click.offFrame()) {
            mActionCommand = ACTION_RELEASE;
        } else {
            mActionCommand = ACTION_CURSOR;
        }
        for(KEventListener* i:mListeners){
            i->processEvent(this);
        }
    } else {
        if (!mHold) mActive = false;
        mCondition = false;
    }
}

bool KGLButton::condition() const {
    return mCondition;
}

