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
 * @brief  \~english  UI by OpenGL
 * @brief  \~japanese OpenGLで表現されるUI
 * @author \~ Maeda Takumi
 * @note   \~japanese 最前面に表示しているだけなので、描画は最後に呼び出されなければならない。
 */
class KGLUI : private KDrawer {
public:
    /**
     * @brief \~english  screen width
     * @brief \~japanese スクリーン横幅
     */
    static const int WIDTH;
    /**
     * @brief \~english  screen height
     * @brief \~japanese スクリーン縦幅
     */
    static const int HEIGHT;
    /**
     * @brief \~english  pixel information of screen
     * @brief \~japanese 画面の画素情報
     */
    KTexture mScreen;

    /**
     * @brief \~english  camera
     * @brief \~japanese カメラ
     */
    const KCamera& mCamera;

    /**
     * \~english
     * @brief generate UI.
     * @param aCamera camera for drawing
     * \~japanese
     * @brief UIを生成します。
     * @param aCamera 描画対象のカメラ
     */
    KGLUI(const KCamera& aCamera);
    virtual ~KGLUI() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
};

#endif /* KGLUI_H */

