/**
 * @file   KWindow.cpp
 * @brief  KWindow
 * @author Maeda Takumi
 */
#include "KWindow.h"

#include "KListener.h"
#include "KMath.h"

const float KWindow::ASPECT = 9.0f / 16.0f;
const KRect KWindow::SIZE = KRect(KVector(960, 540));
const KRect KWindow::DISPLAY_SIZE = KRect(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

KWindow::KWindow(
        const MainArgs* aArgs,
        const KRect& aSize,
        const String& aTitle,
        const bool& aResizable
        ) :
mArgs(aArgs),
mClassName(aTitle),
mWindowClass(WNDCLASSEX{// ウィンドウクラスの設定
    /* 構造体サイズ                 */ sizeof (WNDCLASSEX),
    /* ウィンドウスタイル           */ CS_HREDRAW | CS_VREDRAW,
    /* コールバック関数ポインタ     */ WIN_PROC,
    /* 構造体後の補足バイト数       */ 0,
    /* インスタンス後の補足バイト数 */ 0,
    /* インスタンス                 */ aArgs->mInst,
    /* アイコン                     */ NULL,
    /* マウスカーソルのリソース     */ LoadCursor(NULL, IDC_ARROW),
    /* ウィンドウ背景色             */ (HBRUSH) COLOR_BACKGROUND,
    /* デフォルトメニュー名         */ NULL,
    /* ウィンドウクラスにつける名前 */ mClassName.data(),
    /* 16 x 16サイズのアイコン      */ NULL
}),
mWindow((
        RegisterClassEx(&mWindowClass) ?
        CreateWindow(// ウィンドウの作成
        /* クラスネーム              */ mClassName.data(),
        /* ウィンドウタイトル        */ W(aTitle).data(),
        /* ウィンドウスタイル        */ aResizable ? WS_OVERLAPPEDWINDOW : WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME) | WS_DLGFRAME,
        /* x座標(デフォルト値)       */ CW_USEDEFAULT,
        /* y座標(デフォルト値)       */ CW_USEDEFAULT,
        /* ウィンドウ横幅            */ aSize.width,
        /* ウィンドウ縦幅            */ aSize.height,
        /* 親ウィンドウハンドル      */ NULL,
        /* メニューハンドル          */ NULL,
        /* モジュールインスタンス    */ aArgs->mInst,
        /* WM_CREATEのLPARAMに渡す値 */ this
        ) : NULL)) {
    mTitle = aTitle;

    mFrameVisible = true;
    mFullScreen = false;
    mListener = NULL;
    mClearColor = 0xffffffff; // クリアカラーを白に設定


    if (!mWindow) throw Error("ウィンドウの作成に失敗しました.");

    // ウィンドウサイズ設定
    RECT window, client; // フレーム幅計算
    GetWindowRect(mWindow, &window);
    GetClientRect(mWindow, &client);
    mWindowSize = window;
    mClientSize = client;
    setSize(aSize);

    mCanvasSize = SIZE;

    //
    mBmpInfo.bmiHeader = BITMAPINFOHEADER{sizeof (BITMAPINFOHEADER), DISPLAY_SIZE.width, -DISPLAY_SIZE.height, 1, 32, BI_RGB}; // BMP情報ヘッダの設定

    static PIXELFORMATDESCRIPTOR pformat = {
        sizeof (PIXELFORMATDESCRIPTOR),
        1,
        0 | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32, // color
        0, 0, // R
        0, 0, // G
        0, 0, // B
        0, 0, // A
        0, 0, 0, 0, 0, // AC R G B A
        24, // depth
        8, // stencil
        0, // aux
        0, // layertype
        0, // reserved
        0, // layermask
        0, // visiblemask
        0 // damagemask
    };

    mScreen = GetDC(mWindow);

    // ピクセルフォーマットの選択
    int pfmt = ChoosePixelFormat(mScreen, &pformat);
    SetPixelFormat(mScreen, pfmt, &pformat);

    // OpenGL コンテキストの作成
    mGLRC = wglCreateContext(mScreen);
    wglMakeCurrent(mScreen, mGLRC);

    DeleteDC(mScreen);
}

KWindow::~KWindow() {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(mGLRC);

    UnregisterClass(mClassName.data(), mArgs->mInst);
}

void KWindow::show() const {
    ShowWindow(mWindow, SW_SHOWNORMAL);
}

void KWindow::hide() const {
    ShowWindow(mWindow, SW_HIDE);
}

LRESULT CALLBACK KWindow::WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam) {
    KWindow* _this = NULL;

    if (aMsg == WM_NCCREATE) {
        _this = (KWindow*) ((LPCREATESTRUCT) aLParam)->lpCreateParams;
        SetWindowLong(aHwnd, GWL_USERDATA, uintptr_t(_this));
        _this->mExist = true;
    }

    _this = reinterpret_cast<KWindow*> (GetWindowLong(aHwnd, GWL_USERDATA));
    if (!_this || !_this->mListener) return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);

    switch (aMsg) {
            /* キーイベント */
        case WM_KEYDOWN: _this->mListener->mKeyboard.press(aWParam);
            break;
        case WM_KEYUP: _this->mListener->mKeyboard.release(aWParam);
            break;

            /* マウスイベント */
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
            _this->mListener->mMouse.press(aMsg);
            break;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
            _this->mListener->mMouse.release(aMsg);
            break;
        case WM_MOUSEWHEEL:
            _this->mListener->mMouse.wheelSpin(aWParam);
            break;

        case WM_SIZE:
            // println("unti");
            break;

        case WM_PAINT:
            _this->startPaint();
            _this->mListener->draw();
            _this->display();
            break;
        case WM_DESTROY: _this->mExist = false;
    }
    return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);
}

void KWindow::startPaint() {
    InvalidateRect(mWindow, NULL, false);
    mScreen = BeginPaint(mWindow, &mPaint);
    clearCanvas();
}

void KWindow::clearCanvas() {
    // float a = (float) ((mClearColor & 0xff000000) >> 8 * 3) / 0xff;
    // float r = (float) ((mClearColor & 0x00ff0000) >> 8 * 2) / 0xff;
    // float g = (float) ((mClearColor & 0x0000ff00) >> 8 * 1) / 0xff;
    // float b = (float) ((mClearColor & 0x000000ff) >> 8 * 0) / 0xff;
    // glClearColor(r, g, b, a);
    // glClearDepth(1.0f);
    // glClearStencil(0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void KWindow::display() {
    glFinish();
    SwapBuffers(mScreen);
    EndPaint(mWindow, &mPaint);
}

void KWindow::borderLoss() {
    mFrameVisible = !mFrameVisible; // 交互にスイッチ
    long style = GetWindowLong(mWindow, GWL_STYLE);
    mFrameVisible ? style |= WS_CAPTION : style &= ~WS_CAPTION;
    SetWindowLong(mWindow, GWL_STYLE, style);
    setSize(mScreenSize);
}

void KWindow::toFullScreen() {
    static const float scale = Math::min((float) DISPLAY_SIZE.width / SIZE.width, (float) DISPLAY_SIZE.height / SIZE.height);
    static KRect pos;
    if (mFullScreen != mFrameVisible) borderLoss();
    if (mFullScreen = !mFullScreen) {
        RECT window;
        GetWindowRect(mWindow, &window);
        pos = KRect(window.left, window.top, mScreenSize.width, mScreenSize.height);

        setSize(DISPLAY_SIZE);

        int width = SIZE.width * scale, height = SIZE.height * scale;
        mScreenSize = KRect((DISPLAY_SIZE.width - width) / 2, (DISPLAY_SIZE.height - height) / 2, width, height); // 縦横比が一致しない場合の黒塗り
    } else setSize(pos); // 全画面以前のウィンドウ位置に戻す
}

void KWindow::setTitle(const String & aTitle) {
    mTitle = aTitle;
    SetWindowText(mWindow, W(mTitle).data());
}

void KWindow::setSize(const KRect& aSize) {
    // フレーム幅
    static const int FrameWidth = mWindowSize.width - mClientSize.width;
    static const int FrameHeight = mWindowSize.height - mClientSize.height;

    KRect pos;
    if (aSize.start().isZero()) { // 始点指定なし
        RECT window;
        GetWindowRect(mWindow, &window);
        pos = window;
    }

    mScreenSize = KRect(aSize.width, aSize.height);

    SetWindowPos(mWindow, NULL,
            mFullScreen ? 0 : aSize.x ? aSize.x : pos.x,
            mFullScreen ? 0 : aSize.y ? aSize.y : pos.y,
            (mFrameVisible ? FrameWidth : 0) + aSize.width,
            (mFrameVisible ? FrameHeight : 0) + aSize.height,
            SWP_NOZORDER);

    RECT window, client;
    GetWindowRect(mWindow, &window);
    GetClientRect(mWindow, &client);
    mWindowSize = window;
    mClientSize = client;
}

void KWindow::setListener(KListener * aListener) {
    mListener = aListener;
}

void KWindow::setClearColor(const color& aColor) {
    mClearColor = aColor;
}

KRect KWindow::windowArea() const {
    RECT window;
    GetWindowRect(mWindow, &window);
    return KRect(window);
}

bool KWindow::fullScreen() const {
    return mFullScreen;
}
