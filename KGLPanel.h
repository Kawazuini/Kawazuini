/**
 * @file   KGLPanel.cpp
 * @brief  KGLPanel
 * @author Maeda Takumi
 */
#ifndef KGLPANEL_H
#define KGLPANEL_H

#include "KGLContent.h"

class KGLPanel : public KGLContent {
private:
    List<KGLContent*> mContents;
public:
    KGLPanel(const KRect& aArea);
    virtual ~KGLPanel() = default;

    void draw(KTexture& aUI) const override;
    void update(KGLUI& aUI) override;

    void addContent(KGLContent& aContent);
};

#endif /* KGLPANEL_H */

