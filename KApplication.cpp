/**
 * @file   KApplication.cpp
 * @brief  KApplication
 * @author Maeda Takumi
 */
#include "KApplication.h"

#include "KMath.h"
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
mFrameUpdate(false),
mExecution(false),
mPause(false),
mPauseSwitch(nullptr),
mCamera(aWindow),
mFrontUI(mCamera),
mBackUI(mCamera) {
    std::set_new_handler(KApplication::newFailed);

    KDrawer::remove();
    KUpdater::remove();

    mWindow.setListener(*this);
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
    Time end(now() + aTime);
    do {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (aTime) Sleep(1); // CPUの占有率を下げる
    } while (now() < end); // 指定ミリ秒だけ回る
}

void KApplication::start(const int& aFps) {
    Time start(0), second(0), pass(0);
    int frame(0);

    const double waitMilliSecond(1000.0 / aFps);

    if (!mExecution) { // 二重実行を防ぐ
        mExecution = true;
        //メインループ
        while (mWindow.mExist) {
            start = now();

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

            pass = now() - start;
            wait(Math::max(int(waitMilliSecond - pass), 0));

            ++frame;
            if (mFrameUpdate = ((second += (now() - start)) >= 1000)) {// 1秒ごとにfpsの更新
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
        mPauseSwitch = nullptr;
    }
}

KVector KApplication::mousePositionOn3D() const {
    KVector mouse(mWindow.getMousePositionOnScreen());
    const KRect initial(mWindow.getInitialSize());

    // correction -1 ~ 1
    const KVector center(initial.center());
    mouse -= center;
    mouse.x /= center.x;
    mouse.y /= center.y;

    // correction 3D coordinate
    return mCamera.getHalfWidth() * mouse.x + mCamera.getHalfHeight() * mouse.y + mCamera.getPosition() + mCamera.getDirection();
}

KVector KApplication::mousePositionFromScreenCenter() {
    KVector center(mWindow.getWindowArea().center());
    KVector move(mMouse.position() - center);
    return move;
}

void KApplication::setMousePositionToCenter() {
    KVector center(mWindow.getWindowArea().center());
    mMouse.setPos(center);
}

