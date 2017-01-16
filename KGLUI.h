/**
 * @file   KGLUI.h
 * @brief  KGLUI
 * @author Maeda Takumi
 */
#ifndef KGLUI_H
#define KGLUI_H

#include "KDrawer.h"
#include "KTexture.h"

class KCamera;
class KTexture;

/**
 * @brief  \~english  UI of OpenGL
 * @brief  \~japanese OpenGLで表現されるUI
 * @author \~ Maeda Takumi
 * @note   \~japanese 最前面に表示しているだけなので、描画は最後に呼び出されなければならない。
 */
class KGLUI : private KDrawer {
private:
    /**
     * @brief \~english  pixel information of screen
     * @brief \~japanese 画面の画素情報
     */
    KTexture mScreen;
public:
    static const int WIDTH;
    static const int HEIGHT;


    KGLUI();
    virtual ~KGLUI() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    KTexture& screen();
};

#endif /* KGLUI_H */

