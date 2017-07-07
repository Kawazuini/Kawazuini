/**
 * @file   KGLPanel.h
 * @brief  KGLPanel
 * @author Maeda Takumi
 */
#ifndef KGLPANEL_H
#define KGLPANEL_H

#include "KGLContent.h"

class KGLPanel : public KGLContent {
protected:
    List<KGLContent*> mContents;
public:
    KGLPanel(const KRect& aArea);
    virtual ~KGLPanel() = default;

    virtual void draw(KTexture& aUI) const override;
    virtual void update(KGLUI& aUI) override;

    virtual void addContent(KGLContent& aContent);
    virtual void removeContent(KGLContent& aContent);

    void slide(const KVector& aSlide) override;
};

#endif /* KGLPANEL_H */

