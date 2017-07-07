/**
 * @file   KApplication.cpp
 * @brief  KApplication
 * @author Maeda Takumi
 */
#include "KApplication.h"

#include "KMath.h"
#include "KTimer.h"
#include "KWindow.h"
#include "KWindows.h"

void KApplication::newFailed() {
    message(_T("メモリの確保に失敗しました。"), _T("実行時エラー"));
    exit(1);
}

KApplication::KApplication(KWindow& aWindow) :
mOpenGL(aWindow),
mWindow(aWindow),
mFrame(0),
mExecution(false),
mPause(false),
mPauseSwitch(NULL),
mCamera(aWindow),
mFrontUI(mCamera),
mBackUI(mCamera) {
    std::set_new_handler(KApplication::newFailed);

    KDrawer::remove();
    KUpdater::remove();

    mWindow.mListener = this;
    timeBeginPeriod(1); // 最小分解能の設定(Timerは信頼できるが,Sleepは信頼できない)
}

KApplication::~KApplication() {
    timeEndPeriod(1);
}

void KApplication::responsiveDraw() const {
    KShading::ColorShading->ON();
    mBackUI.draw();
    draw();
    KShading::ColorShading->ON();
    mFrontUI.draw();
}

void KApplication::wait(const int& aTime) {
    MSG msg;
    KTimer::Time end(KTimer::now() + aTime);
    do {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (aTime) Sleep(1); // CPUの占有率を下げる
    } while (KTimer::now() < end); // 指定ミリ秒だけ回る
}

void KApplication::start(const int& aFps) {
    KTimer::Time start(0), second(0), pass(0);
    int frame(0);

    const double waitMilliSecond(1000.0 / aFps);

    if (!mExecution) { // 二重実行を防ぐ
        mExecution = true;
        //メインループ
        while (mWindow.mExist) {
            start = KTimer::now();

            if (!mPause) {
                update();
                mMouse.pass();
                mKeyboard.pass();
                mFrontUI.refrect();
                mBackUI.refrect();

                mWindow.startPaint();
                KShading::ColorShading->ON();
                mBackUI.draw();
                draw();
                KShading::ColorShading->ON();
                mFrontUI.draw();
                mWindow.display();
            } else if (mPauseSwitch && mPauseSwitch->isTouch()) {
                resume();
            }

            pass = KTimer::now() - start;
            wait(Math::max(int(waitMilliSecond - pass), 0));

            ++frame;
            if ((second += (KTimer::now() - start)) >= 1000) {// 1秒ごとにfpsの更新
                mFrame = frame;
                second = 0;
                frame = 0;
            }
        }
    }
}

void KApplication::stop() {
    mPause = true;
}

void KApplication::stop(KSwitch& aPauseSwitch) {
    mPause = true;
    mPauseSwitch = &aPauseSwitch;
    mPauseSwitch->OFF();
}

void KApplication::resume() {
    mPause = false;
    if (mPauseSwitch) {
        mPauseSwitch->OFF();
        mPauseSwitch = NULL;
    }
}

KVector KApplication::mousePositionOn3D() const {
    KVector mouse(mWindow.mousePositionOnScreen());
    const KRect initial(mWindow.initialSize());

    // correction -1 ~ 1
    const KVector center(initial.center());
    mouse -= center;
    mouse.x /= center.x;
    mouse.y /= center.y;

    // correction 3D coordinate
    return mCamera.halfWidth() * mouse.x + mCamera.halfHeight() * mouse.y + mCamera.position() + mCamera.direction();
}
