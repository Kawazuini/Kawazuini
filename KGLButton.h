/**
 * @file   KGLButton.h
 * @brief  KGLButton
 * @author Maeda Takumi
 */
#ifndef KGLBUTTON_H
#define KGLBUTTON_H

#include "KEvent.h"
#include "KGLContent.h"
#include "KSwitch.h"

class KGLButton : public KGLContent, public KEvent {
public:
    static const String ACTION_CURSOR;
    static const String ACTION_PRESS;
    static const String ACTION_RELEASE;
private:
    KSwitch mSwitch;
    bool mCondition;
    bool mHold;
public:
    KGLButton(const KRect& aArea);
    virtual ~KGLButton() = default;

    void draw(KTexture& aUI) const override;
    void update(KGLUI& aUI) override;

    bool condition() const override;
};

#endif /* KGLBUTTON_H */

