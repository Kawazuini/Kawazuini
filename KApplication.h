/**
 * @file   KApplication.h
 * @brief  KApplication
 * @author Maeda Takumi
 */
#ifndef KAPPLICATION_H
#define KAPPLICATION_H

#include "KCamera.h"
#include "KGLUI.h"
#include "KListener.h"
#include "KOpenGL.h"
#include "KShading.h"

class KWindow;

/**
 * @brief  \~english  Base of Application
 * @brief  \~japanese アプリケーション基底
 * @author \~ Maeda Takumi
 */
class KApplication :
protected KListener,
protected KDrawer,
protected KUpdater {
private:
    /* メモリの確保に失敗したときに呼ばれます。 */ static void newFailed();

    /* OpenGLの初期化   */ KOpenGL mOpenGL;
    /* シェーダの初期化 */ KShading mShading;

    /* Windowが再描画を要求したときに呼ばれます。 */ void responsiveDraw() const override final;
    /* 指定ミリ秒の間、処理を休止します。         */ void wait(const int& aTime);
protected:
    /// @brief \~english  window for processing
    /// @brief \~japanese 処理を行っているウィンドウ
    KWindow& mWindow;
    /// @brief \~english  count of frame per second
    /// @brief \~japanese 1秒間のフレームカウント
    int mFrame;
    bool mFrameUpdate;
    /// @brief \~english  whether processing is execution
    /// @brief \~japanese 処理を実行しているか
    bool mExecution;
    /// @brief \~english  whether processing is paused
    /// @brief \~japanese 処理を中断しているか
    bool mPause;
    /// @brief \~english  switch for resume
    /// @brief \~japanese ポーズ解除スイッチ
    KSwitch* mPauseSwitch;
    /// @brief \~english  camera for application
    /// @brief \~japanese アプリケーションカメラ
    KCamera mCamera;
    /// @brief \~english  frontmost UI
    /// @brief \~japanese 最前面UI
    KGLUI mFrontUI;
    /// @brief \~english  innermost UI
    /// @brief \~japanese 最奥面UI
    KGLUI mBackUI;

    /**
     * @param \~english  aWindow window for processing
     * @param \~japanese aWindow 処理を行うウィンドウ
     */
    KApplication(KWindow& aWindow);
    virtual ~KApplication();
public:
    /**
     * \~english
     * @brief start main loop.
     * @param aFps frame per second for main loop
     * \~japanese
     * @brief メインループを開始します。
     * @param aFps メインループの秒間フレーム数
     */
    void start(const int& aFps = 50);
    /**
     * @brief \~english stop main loop
     * \~japanese
     * @brief メインループを中断します。
     * @note  FPSのカウントとウィンドウメッセージの処理は中断されずに行われます。
     */
    void stop();
    /**
     * \~english
     * @brief stop the main loop and specify the switch for resume.
     * @param aPauseSwitch switch for resume main loop
     * \~japanese
     * @brief 再開スイッチを指定してメインループを中断します。
     * @param aPauseSwitch メインループを再開させるためのスイッチ
     */
    void stop(KSwitch& aPauseSwitch);
    /**
     * @brief \~english  resume main loop.
     * @brief \~japanese メインループを再開します。
     */
    void resume();
    /**
     * \~english
     * @brief  calculate mouse coordinates(1m ahead) on 3 dimensions.
     * @return mouse coordinates(1m ahead) on 3 dimensions
     * \~japanese
     * @brief  3次元上の(1m先の)マウス座標を計算します。
     * @return 3次元上の(1m先の)マウス座標
     */
    KVector mousePositionOn3D() const;
    
    KVector mousePositionFromScreenCenter();
    void setMousePositionToCenter();
};

#endif /* KAPPLICATION_H */

