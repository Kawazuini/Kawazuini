/**
 * @file KGLUI.h
 * @author Maeda Takumi
 */
#ifndef KGLUI_H
#define KGLUI_H

#include "KUtility.h"

#include "KDrawer.h"

class KCamera;
class KTexture;

class KGLUI : private KDrawer {
public:
    static const int WIDTH; ///< 横幅
    static const int HEIGHT; ///< 縦幅
    KTexture * const mScreen; ///< 画面の画素情報

    KGLUI();
    virtual ~KGLUI();

    /** @brief 描画処理 */
    void draw() const override;
};

#endif /* KGLUI_H */

