/**
 * @file   KGLTextButton.cpp
 * @brief  KGLTextButton
 * @author Maeda Takumi
 */
#include "KGLTextButton.h"

KGLTextButton::KGLTextButton(
        const KRect& aArea,
        const KCharset& aCharset,
        const String& aText
        ) :
KGLContent(aArea),
KGLButton(aArea),
KGLTextLabel(aArea.begin(), aCharset, aText) {
    mArea = aArea;
}

void KGLTextButton::draw(KTexture& aUI) const {
    KGLTextLabel::draw(aUI);
}

void KGLTextButton::update(KGLUI& aUI) {
    KGLButton::update(aUI);
}

