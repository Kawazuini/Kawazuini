/**
 * @file   KGLContent.h
 * @brief  KGLContent
 * @author Maeda Takumi
 */
#ifndef KGLCONTENT_H
#define KGLCONTENT_H

#include "KNonCopy.h"
#include "KRect.h"
#include "KUtility.h"

class KGLUI;
class KTexture;

class KGLContent : private KNonCopy {
    friend class KGLUI;
    friend class KGLPanel;
    friend class KGLScrollPanel;
protected:
    const KGLContent* mParent;

    KRect mArea;
    bool mActive;
    bool mUpdated;

    color mFrontColor;
    color mBackColor;

    KGLContent(const KRect& aArea);
    virtual ~KGLContent() = default;
private:
    virtual void draw(KTexture& aUI) const = 0;
    virtual void update(KGLUI& aUI) = 0;

    void setParent(const KGLContent* aContent);
public:
    const bool& isActive() const;
    const bool& isUpdated() const;

    void setFrontColor(const color& aColor);
    void setBackColor(const color& aColor);

    const color& frontColor() const;
    const color& backColor() const;

    virtual void slide(const KVector& aSlide);

    const KRect& area() const;
};

#endif /* KGLCONTENT_H */

