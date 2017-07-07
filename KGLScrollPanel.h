/**
 * @file   KGLScrollPanel.h
 * @brief  KGLScrollPanel
 * @author Maeda Takumi
 */
#ifndef KGLSCROLLPANEL_H
#define KGLSCROLLPANEL_H

#include "KGLPanel.h"

#include "KVector.h"

class KGLScrollPanel : public KGLPanel {
private:
    Vector<KGLContent*> mViewList;
    KRect mPanelArea;
    int mScrollAmount;
    KVector mScroll;
public:
    KGLScrollPanel(const KRect& aArea);
    virtual ~KGLScrollPanel() = default;

    void update(KGLUI& aUI) override;
    void draw(KTexture& aUI) const override;

    void addContent(KGLContent& aContent) override;
    void removeContent(KGLContent& aContent) override;

    void expand(const KVector& aExpand);
    void scroll(const KVector& aOffset);
};

#endif /* KGLSCROLLPANEL_H */

