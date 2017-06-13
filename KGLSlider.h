/**
 * @file   KGLSlider.h
 * @brief  KGLSlider
 * @author Maeda Takumi
 */
#ifndef KGLSLIDER_H
#define KGLSLIDER_H

#include "KGLContent.h"

class KGLSlider : public KGLContent {
public:

    enum SliderType {
        HORIZON,
        VERTICAL,
    };

private:
    SliderType mType;
    bool mHold;
    int mSlider;
public:
    KGLSlider(
            const KRect& aArea,
            const SliderType& aType
            );
    virtual ~KGLSlider() = default;
private:
    void draw(KTexture& aUI) const override;
    void update(KGLUI& aUI) override;
public:
    void setValue(const double& aValue);
    double getValue() const;
};

#endif /* KGLSLIDER_H */

