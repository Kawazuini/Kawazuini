/**
 * @file   KWindow.cpp
 * @brief  KWindow
 * @author Maeda Takumi
 */
#include "KWindow.h"

#include "KListener.h"
#include "KMath.h"

const float KWindow::ASPECT(9.0f / 16.0f);
const KRect KWindow::SIZE((KVector(960, 540)));
const KRect KWindow::DISPLAY_SIZE(KRect(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));

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
        ) : NULL)),
mTitle(aTitle),
mFrameVisible(true),
mFullScreen(false),
mScreenSize(aSize),
mPixelFormat({
    sizeof (PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
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
}) {
    if (!mWindow) throw Error(_T("ウィンドウの作成に失敗しました."));

    // ピクセルフォーマットの選択
    wglDeleteContext(mGLRC);
    mScreen = GetDC(mWindow);
    SetPixelFormat(mScreen, ChoosePixelFormat(mScreen, &(mPixelFormat)), &(mPixelFormat));
    mGLRC = wglCreateContext(mScreen); // OpenGL コンテキストの作成
    wglMakeCurrent(mScreen, mGLRC);
    ReleaseDC(mWindow, mScreen);

    // フレーム幅
    RECT window, client; // フレーム幅計算
    GetWindowRect(mWindow, &window);
    GetClientRect(mWindow, &client);
    KRect w(window), c(client);
    mFrameWidth = w.width - c.width;
    mFrameHeight = w.height - c.height;

    setSize(aSize);
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
    KWindow * _this(NULL);

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
        {
            int mode;
            glGetIntegerv(GL_MATRIX_MODE, &mode);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glViewport(_this->mScreenSize.x, _this->mScreenSize.y, _this->mScreenSize.width, _this->mScreenSize.height);
            glMatrixMode(mode);

            break;
        }
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
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void KWindow::display() {
    glFinish();
    SwapBuffers(mScreen);
    EndPaint(mWindow, &mPaint);
}

void KWindow::borderLoss() {
    mFrameVisible = !mFrameVisible; // 交互にスイッチ
    long style(GetWindowLong(mWindow, GWL_STYLE));
    mFrameVisible ? style |= WS_CAPTION : style &= ~WS_CAPTION;
    SetWindowLong(mWindow, GWL_STYLE, style);
    setSize(mScreenSize);
}

void KWindow::toFullScreen() {
    static const float scale(Math::min((float) DISPLAY_SIZE.width / SIZE.width, (float) DISPLAY_SIZE.height / SIZE.height));
    static KRect pPosition;
    if (mFullScreen != mFrameVisible) borderLoss();
    if (mFullScreen = !mFullScreen) {
        // 事前領域の記憶
        RECT window;
        GetWindowRect(mWindow, &window);
        pPosition = KRect(window.left, window.top, mScreenSize.width, mScreenSize.height);

        int width(SIZE.width * scale);
        int height(SIZE.height * scale);
        // 縦横比が一致しない場合の黒塗り
        mScreenSize = KRect((DISPLAY_SIZE.width - width) / 2, (DISPLAY_SIZE.height - height) / 2, width, height);

        setSize(DISPLAY_SIZE);
    } else {
        mScreenSize = KRect(pPosition.width, pPosition.height);
        setSize(pPosition); // 全画面以前のウィンドウ位置に戻す
    }
}

void KWindow::setTitle(const String & aTitle) {
    mTitle = aTitle;
    SetWindowText(mWindow, W(mTitle).data());
}

void KWindow::setSize(const KRect& aSize) {
    KRect area(aSize);

    if (area.start().isZero() && !mFullScreen) { // 始点指定なし(左上座標そのまま)
        RECT window;
        GetWindowRect(mWindow, &window);

        area.x = window.left;
        area.y = window.top;
    }
    if (mFrameVisible) area.width += mFrameWidth;
    if (mFrameVisible) area.height += mFrameHeight;
    SetWindowPos(mWindow, NULL, area.x, area.y, area.width, area.height, SWP_NOZORDER);
}

void KWindow::setListener(KListener * aListener) {
    mListener = aListener;
}

KRect KWindow::windowArea() const {
    RECT window;
    GetWindowRect(mWindow, &window);
    return KRect(window);
}

const bool& KWindow::isFullScreen() const {
    return mFullScreen;
}

bool KWindow::isActive() const {
    return mWindow == GetActiveWindow() && mWindow == GetForegroundWindow();
}

