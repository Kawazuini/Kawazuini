/**
 * @file   KGLTextButton.h
 * @brief  KGLTextButton
 * @author Maeda Takumi
 */
#ifndef KGLTEXTBUTTON_H
#define KGLTEXTBUTTON_H

#include "KGLButton.h"
#include "KGLTextLabel.h"

class KGLTextButton : public KGLButton, public KGLTextLabel {
public:
    KGLTextButton(
            const KRect& aArea,
            const KCharset& aCharset,
            const String& aText
            );
    virtual ~KGLTextButton() = default;

    void draw(KTexture& aUI) const override;
    void update(KGLUI& aUI) override;
};

#endif /* KGLTEXTBUTTON_H */

