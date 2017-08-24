/**
 * @file   KWindow.cpp
 * @brief  KWindow
 * @author Maeda Takumi
 */
#include "KWindow.h"

#include "KListener.h"
#include "KMath.h"
#include "KVector.h"

const KRect KWindow::DISPLAY_SIZE(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

KWindow::KWindow(
        const MainArgs& aArgs,
        const KRect& aSize,
        const String& aTitle,
        const bool& aResizable
        ) :
mArgs(aArgs),
mClassName(W(aTitle)),
mWindowClass(WNDCLASSEX{// ウィンドウクラスの設定
    /* 構造体サイズ                 */ sizeof (WNDCLASSEX),
    /* ウィンドウスタイル           */ CS_HREDRAW | CS_VREDRAW,
    /* コールバック関数ポインタ     */ WIN_PROC,
    /* 構造体後の補足バイト数       */ 0,
    /* インスタンス後の補足バイト数 */ 0,
    /* インスタンス                 */ aArgs.mInst,
    /* アイコン                     */ LoadIcon(aArgs.mInst, TEXT("IDI_ICON")),
    /* マウスカーソルのリソース     */ LoadCursor(nullptr, IDC_ARROW),
    /* ウィンドウ背景色             */ (HBRUSH) COLOR_BACKGROUND,
    /* デフォルトメニュー名         */ nullptr,
    /* ウィンドウクラスにつける名前 */ mClassName.data(),
    /* 16 x 16サイズのアイコン      */ nullptr
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
        /* 親ウィンドウハンドル      */ nullptr,
        /* メニューハンドル          */ nullptr,
        /* モジュールインスタンス    */ aArgs.mInst,
        /* WM_CREATEのLPARAMに渡す値 */ this
        ) : nullptr)),
mListener(nullptr),
mTitle(aTitle),
mResizable(aResizable),
mFrameVisible(true),
mFullScreen(false),
mInitialSize(aSize),
mInitialAspect((float) aSize.height / aSize.width),
mScreenArea(aSize),
mScale(1.0f) {
    if (!mWindow) throw Error(_T("ウィンドウの作成に失敗しました."));

    // フレーム幅の計算
    KRect w(getWindowArea()), c(getClientArea());
    mFrameWeight = KRect(w.width - c.width, w.height - c.height);

    setSize(aSize);
}

KWindow::~KWindow() {
    UnregisterClass(mClassName.data(), mArgs.mInst);
}

LRESULT CALLBACK KWindow::WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam) {
    KWindow * _this(nullptr);

    if (aMsg == WM_NCCREATE) {
        _this = (KWindow*) ((LPCREATESTRUCT) aLParam)->lpCreateParams;
        SetWindowLong(aHwnd, GWL_USERDATA, uintptr_t(_this));
        _this->mExist = true;
    }

    _this = reinterpret_cast<KWindow*> (GetWindowLong(aHwnd, GWL_USERDATA));
    if (!_this || !_this->mListener)
        return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);

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
            SetCapture(_this->mWindow);
            _this->mListener->mMouse.press(aMsg);
            break;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
            ReleaseCapture();
            _this->mListener->mMouse.release(aMsg);
            break;
        case WM_MOUSEWHEEL:
            _this->mListener->mMouse.wheelSpin(aWParam);
            break;

        case WM_SIZE:
        {
            KRect client(_this->getClientArea());
            _this->mScale =
                    Math::min(
                    (float) client.width / _this->mInitialSize.width,
                    (float) client.height / _this->mInitialSize.height
                    );
            int width(_this->mInitialSize.width * _this->mScale);
            int height(_this->mInitialSize.height * _this->mScale);
            _this->mScreenArea = KRect(
                    (client.width - width) / 2,
                    (client.height - height) / 2,
                    width, height);

            KRect area(_this->mScreenArea);
            glViewport(DEPLOY_RECT(area));
            break;
        }
        case WM_PAINT:
            _this->startPaint();
            _this->mListener->responsiveDraw();
            _this->display();
            break;
        case WM_DESTROY: _this->mExist = false;
    }
    return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);
}

void KWindow::startPaint() {
    InvalidateRect(mWindow, nullptr, false);
    mScreen = BeginPaint(mWindow, &mPaint);
    clearCanvas();
}

void KWindow::clearCanvas() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void KWindow::display() {
    glFinish();
    SwapBuffers(mScreen);
    EndPaint(mWindow, &mPaint);
}

void KWindow::show() const {
    ShowWindow(mWindow, SW_SHOWNORMAL);
}

void KWindow::hide() const {
    ShowWindow(mWindow, SW_HIDE);
}

bool KWindow::getEncoder(const WCHAR& aFormat, CLSID& aClsid) {
    unsigned int num(0), size(0);
    Gdiplus::GetImageEncodersSize(&num, &size);
    if (!size) return false;

    Gdiplus::ImageCodecInfo * imageCodecInfo(new Gdiplus::ImageCodecInfo[size]);
    Gdiplus::GetImageEncoders(num, size, imageCodecInfo);

    for (int i = 0; i < num; ++i) {
        if (!(wcscmp((imageCodecInfo + i)->MimeType, &aFormat))) {
            aClsid = (imageCodecInfo + i)->Clsid;
            delete[] imageCodecInfo;
            return true;
        }
    }
    delete[] imageCodecInfo;
    return false;
}

void KWindow::screenShot(
        const String& aFileName,
        const Extension& aExtension
        ) {
    HDC scr(GetDC(mWindow));
    HBITMAP screen(CreateCompatibleBitmap(scr, mInitialSize.width, mInitialSize.height));
    HDC canvas(CreateCompatibleDC(scr));

    SelectObject(canvas, screen);

    // 描画結果の取得と転送
    unsigned char* pixel(new unsigned char[mInitialSize.width * mInitialSize.height * 3]);
    glReadPixels(DEPLOY_RECT(mInitialSize), GL_RGB, GL_UNSIGNED_BYTE, pixel);
    unsigned char* color(pixel);
    for (int i = mInitialSize.height - 1; i >= 0; --i) {
        for (int j = 0, j_e(mInitialSize.width); j < j_e; ++j) {
            SetPixel(canvas, j, i, (*color++) | (*color++ << 8) | (*color++ << 16));
        }
    }
    delete[] pixel;

    // ファイル名と保存形式の決定
    String name(split(aFileName, R"(\.)")[0]); // 拡張子剥がす
    WCHAR* format;
    switch (aExtension) {
        case BMP:
            name += ".bmp";
            format = (WCHAR*) L"image/bmp";
            break;
        case GIF:
            name += ".gif";
            format = (WCHAR*) L"image/gif";
            break;
        case JPG:
            name += ".jpg";
            format = (WCHAR*) L"image/jpeg";
            break;
        case PNG:
            name += ".png";
            format = (WCHAR*) L"image/png";
            break;
    }

    WCHAR wFileName[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, name.data(), -1, wFileName, MAX_PATH);

    CLSID clsid;
    Gdiplus::Bitmap bmp(screen, (HPALETTE) GetStockObject(DEFAULT_PALETTE));
    if (getEncoder(*format, clsid)) {
        bmp.Save(wFileName, &clsid, NULL);
    }

    ReleaseDC(mWindow, scr);
    DeleteObject(screen);
    DeleteDC(canvas);
}

void KWindow::changeFrame() {
    mFrameVisible = !mFrameVisible; // 交互にスイッチ

    long frameStyle(WS_CAPTION);

    if (mResizable) frameStyle = WS_CAPTION ^ WS_DLGFRAME | WS_THICKFRAME;

    long style(GetWindowLong(mWindow, GWL_STYLE));
    mFrameVisible ? style |= frameStyle : style ^= frameStyle;
    SetWindowLong(mWindow, GWL_STYLE, style);
    setSize(mScreenArea);
}

void KWindow::changeFullScreen() {
    static KRect pPosition;
    if (mFullScreen != mFrameVisible) changeFrame();
    if (mFullScreen = !mFullScreen) {
        // 事前領域の記憶
        KRect w(getWindowArea());
        pPosition = KRect(w.x, w.y, mScreenArea.width, mScreenArea.height);
        setSize(DISPLAY_SIZE);
    } else setSize(pPosition); // 全画面以前のウィンドウ位置に戻す    
}

void KWindow::setListener(KListener& aListener) {
    mListener = &aListener;
}

void KWindow::setTitle(const String & aTitle) {
    mTitle = aTitle;
    SetWindowText(mWindow, W(mTitle).data());
}

void KWindow::setSize(const KRect& aSize) {
    KRect area(aSize);

    if (area.begin().isZero() && !mFullScreen) { // 始点指定なし(左上座標そのまま)
        KRect w(getWindowArea());
        area.x = w.x;
        area.y = w.y;
    }
    if (mFrameVisible) {

        area.width += mFrameWeight.width;
        area.height += mFrameWeight.height;
    }
    SetWindowPos(mWindow, nullptr, DEPLOY_RECT(area), SWP_NOZORDER);
}

KVector KWindow::getMousePositionOnScreen() const {
    POINT mousePoint;
    GetCursorPos(&mousePoint);
    ScreenToClient(mWindow, &mousePoint);
    KVector mouse(mousePoint);

    const KRect & screen(mScreenArea);

    mouse -= screen.begin(); // スクリーンに合うように補正
    mouse /= mScale; // 拡大率に合うように補正

    return mouse;
}

const KRect& KWindow::getInitialSize() const {
    return mInitialSize;
}

const float& KWindow::getInitialAspect() const {
    return mInitialAspect;
}

const KRect& KWindow::getScreenArea() const {
    return mScreenArea;
}

const float& KWindow::getScale() const {
    return mScale;
}

KRect KWindow::getWindowArea() const {
    RECT window;
    GetWindowRect(mWindow, &window);

    return window;
}

KRect KWindow::getClientArea() const {
    RECT client;
    GetClientRect(mWindow, &client);

    return client;
}

const bool& KWindow::isFullScreen() const {
    return mFullScreen;
}

bool KWindow::isActive() const {
    return mWindow == GetActiveWindow() && mWindow == GetForegroundWindow();
}

