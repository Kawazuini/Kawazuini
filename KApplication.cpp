/**
 * @file   KApplication.cpp
 * @brief  KApplication
 * @author Maeda Takumi
 */
#include "KApplication.h"

#include "KMath.h"
#include "KTimer.h"
#include "KWindow.h"
#include "KSwitch.h"

KApplication::KApplication(KWindow& aWindow) :
mWindow(aWindow),
mFrame(0),
mExecution(false),
mPause(false),
mPauseSwitch(NULL) {
    timeBeginPeriod(1); // 最小分解能の設定(Timerは信頼できるが,Sleepは信頼できない)
}

KApplication::~KApplication() {
    timeEndPeriod(1);
}

void KApplication::wait(const int& aTime) {
    MSG msg;
    KTimer::Time end = KTimer::now() + aTime;
    do {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (aTime) Sleep(1); // CPUの占有率を下げる
    } while (KTimer::now() < end); // 指定ミリ秒だけ回る
}

void KApplication::start(const int& aFps) {
    KTimer::Time start, second = 0;
    int frame = 0;

    if (!mExecution) { // 二重実行を防ぐ
        mExecution = true;
        //メインループ
        while (mWindow.mExist) {
            start = KTimer::now();

            if (!mPause) {
                update();

                mWindow.startPaint();
                draw();
                mWindow.display();
            } else if (mPauseSwitch && mPauseSwitch->isTouch()) {
                resume();
            }

            wait(Math::max(int(1000 / aFps - (KTimer::now() - start)), 0));

            ++frame;
            if ((second += (KTimer::now() - start)) >= 1000) {// 1秒ごとにfpsの更新
                mFrame = frame;
                second = 0;
                frame = 0;
            }
        }
    }
}

void KApplication::resume() {
    mPause = false;
    mPauseSwitch->OFF();
    mPauseSwitch = NULL;
}

void KApplication::stop(KSwitch * const aPauseSwitch) {
    mPause = true;
    mPauseSwitch = aPauseSwitch;
    mPauseSwitch->OFF();
}
