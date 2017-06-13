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

class KSwitch;
class KWindow;

/**
 * @brief  \~english  Base of Application
 * @brief  \~japanese アプリケーション基底
 * @author \~ Maeda Takumi
 */
class KApplication : public KListener {
private:
    KOpenGL mOpenGL;
    KShading mShading;
    void wait(const int& aTime); // ミリ秒間処理を休止
protected:
    /**
     * @brief \~english  window for processing
     * @brief \~japanese 処理を行うウィンドウ
     */
    KWindow& mWindow;
    /**
     * @brief \~english  count for frame per second
     * @brief \~japanese 秒間フレームカウント
     */
    int mFrame;
    /**
     * @brief \~english  whether processing execution
     * @brief \~japanese 処理を実行しているか
     */
    bool mExecution;
    /**
     * @brief \~english  whether processing pause
     * @brief \~japanese 処理を中断しているか
     */
    bool mPause;
    /**
     * @brief \~english  resume switch
     * @brief \~japanese ポーズ解除スイッチ
     */
    KSwitch* mPauseSwitch;

    KCamera mCamera;
    KGLUI mFrontUI;
    KGLUI mBackUI;

    /**
     * @param \~english  aWindow window for processing
     * @param \~japanese aWindow 処理を行うウィンドウ
     */
    KApplication(KWindow& aWindow);
    virtual ~KApplication();
public:
    virtual void update() = 0;

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
};

#endif /* KAPPLICATION_H */

