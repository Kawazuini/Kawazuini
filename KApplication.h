/**
 * @file KApplication.h
 * @brief アプリケーションクラス
 */
#ifndef KAPPLICATION_H
#define KAPPLICATION_H

#include "KListener.h"
#include "KVector.h"

class KSwitch;
class KWindow;

/** @brief アプリケーション */
class KApplication : public KListener {
private:
    void wait(const int& aTime); // ミリ秒間処理を休止
protected:
    /** @brief 処理を行うウィンドウ */ KWindow* mWindow;
    /** @brief 秒間フレームカウント */ int mFrame;
    /** @brief 実行中               */ bool mExecution;
    /** @brief ポーズ中             */ bool mPause;
    /** @brief ポーズ解除スイッチ   */ KSwitch* mPauseSwitch;

    /** @param aWindow 処理を行うウィンドウ */
    KApplication(KWindow* aWindow);
    virtual ~KApplication();

public:
    /** @brief メインループの開始 */ void start(const int& aFps = 50);
    /** @brief メインループの再開 */ void resume();
    /**
     * @brief メインループの停止
     * @param 停止解除スイッチ
     */
    void stop(KSwitch * const aPauseSwitch = NULL);
};

#endif /* KAPPLICATION_H */
