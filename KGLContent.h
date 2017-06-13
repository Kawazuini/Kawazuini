/**
 * @file   KGLContent.h
 * @brief  KGLContetn
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
protected:
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
public:
    const bool& isActive() const;
    const bool& isUpdated() const;

    void setFrontColor(const color& aColor);
    void setBackColor(const color& aColor);

    const color& frontColor() const;
    const color& backColor() const;
};

#endif /* KGLCONTENT_H */

