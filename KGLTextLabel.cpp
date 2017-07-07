/**
 * @file   KGLTextLabel.cpp
 * @brief  KGLTextLabel
 * @author Maeda Takumi
 */
#include "KGLTextLabel.h"

#include "KTexture.h"

KGLTextLabel::KGLTextLabel(
        const KVector& aPosition,
        const KCharset& aCharset,
        const String& aText
        ) :
KGLContent(KRect(aPosition, aPosition + KVector(aCharset.getWidth(aText), aCharset.mSize * 2))),
mPosition(aPosition),
mCharset(aCharset),
mText(aText) {
}

void KGLTextLabel::draw(KTexture& aUI) const {
    if (mBackColor & 0xff000000) aUI.drawRect(mArea, mBackColor);
    if (mFrontColor & 0xff000000)aUI.drawText(mCharset, mText, mArea.begin(), mFrontColor);
}

int KGLTextLabel::setText(const String& aText) {
    mUpdated = true;
    mText = aText;
}

