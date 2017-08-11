/**
 * @file   KGLUI.h
 * @brief  KGLUI
 * @author Maeda Takumi
 */
#ifndef KGLUI_H
#define KGLUI_H

#include "KDrawer.h"
#include "KTexture.h"
#include "KRect.h"
#include "KUpdater.h"
#include "KWindow.h"
#include "KVertexBufferObject.h"

class KCamera;
class KGLContent;
class KTexture;
class KWindow;

/**
 * @brief  \~english  UI by OpenGL
 * @brief  \~japanese OpenGLで表現されるUI
 * @author \~ Maeda Takumi
 */
class KGLUI final : private KDrawer, private KUpdater {
private:
    /* UI size            */ static const int SIZE;
    /* camera for drawing */ const KCamera& mCamera;
    /* window for drawing */ const KWindow& mWindow;
    /* UI components      */ List<KGLContent*> mComponents;

    /* pixel information of screen   */ KTexture mScreen;
    /* whether updated of screen     */ bool mUpdated;
    /* scale between UI and Window   */ float mScale;
    /* drawabel area of screen       */ KRect mArea;
    /* aspect ratio of drawable area */ float mAspect;

    KVertexBufferObject<KVector> mVertex;
    KVertexBufferObject<float[2]> mCoordinate;
public:
    KGLUI(const KCamera& aCamera);
    ~KGLUI() = default;

    void draw() const override;
    void update() override;
    void refrect();
    void addContent(KGLContent& aContent);

    bool isContentsActive() const;

    KVector mousePosition() const;

    const KCamera& camera() const;
    const KWindow& window() const;
    KTexture& screen();
    const KRect& area() const;
};

#endif /* KGLUI_H */

