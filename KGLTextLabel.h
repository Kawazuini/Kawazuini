/**
 * @file   KGLTextLabel.h
 * @brief  KGLTextLabel
 * @author Maeda Takumi
 */
#ifndef KGLTEXTLABEL_H
#define KGLTEXTLABEL_H

#include "KCharset.h"
#include "KGLContent.h"

class KGLTextLabel : public KGLContent {
private:
    KVector mPosition;
    const KCharset& mCharset;
    String mText;
public:
    KGLTextLabel(
            const KVector& aPosition,
            const KCharset& aCharset,
            const String& aText
            );
    virtual ~KGLTextLabel() = default;
private:
    void draw(KTexture& aUI) const override;

    void update(KGLUI& aUI) override {
    };
public:
    setText(const String& aText);
};

#endif /* KGLTEXTLABEL_H */

