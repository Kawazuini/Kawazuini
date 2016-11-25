/**
 * @file KGLUI.h
 * @author Maeda Takumi
 */
#ifndef KGLUI_H
#define KGLUI_H

#include "KUtility.h"

#include "KNonCopy.h"

class KCamera;
class KImage;
class KRect;
class KVector;

class KTexture;

class KGLUI : private KNonCopy {
public:
    static const int WIDTH; ///< 横幅
    static const int HEIGHT; ///< 縦幅
private:
    const KCamera * const mCamera;
public:
    KTexture * const mScreen; ///< 画面の画素情報

    KGLUI(const KCamera& aCamera);
    virtual ~KGLUI();

    /** @brief 描画処理 */
    void draw() const;
};

#endif /* KGLUI_H */

