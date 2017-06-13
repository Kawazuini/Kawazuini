/**
 * @file   KInputWindow.cpp
 * @brief  KInputWindow
 * @author Maeda Takumi
 */
#include "KInputWindow.h"
#include "KWindows.h"

const int KInputWindow::ID_EDIT(1);
const int KInputWindow::ID_BUTTON(2);

KInputWindow::KInputWindow(
        const KWindow::MainArgs& aArgs,
        const KRect& aSize,
        const String& aTitle,
        const String& aText
        ) :
mArgs(aArgs),
mClassName(W(aTitle)),
mWindowClass({// ウィンドウクラスの設定
    /* 構造体サイズ                 */ sizeof (WNDCLASSEX),
    /* ウィンドウスタイル           */ CS_HREDRAW | CS_VREDRAW,
    /* コールバック関数ポインタ     */ WIN_PROC,
    /* 構造体後の補足バイト数       */ 0,
    /* インスタンス後の補足バイト数 */ 0,
    /* インスタンス                 */ aArgs.mInst,
    /* アイコン                     */ LoadIcon(aArgs.mInst, TEXT("IDI_ICON")),
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
        /* ウィンドウスタイル        */ WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME) | WS_DLGFRAME,
        /* x座標(デフォルト値)       */ CW_USEDEFAULT,
        /* y座標(デフォルト値)       */ CW_USEDEFAULT,
        /* ウィンドウ横幅            */ aSize.width,
        /* ウィンドウ縦幅            */ aSize.height,
        /* 親ウィンドウハンドル      */ NULL,
        /* メニューハンドル          */ NULL,
        /* モジュールインスタンス    */ aArgs.mInst,
        /* WM_CREATEのLPARAMに渡す値 */ this
        ) : NULL)),
mDefaultText(aText),
mSize(aSize),
mDecide(false) {
    if (!mWindow) throw Error(_T("ウィンドウの作成に失敗しました."));
    HWND edit(CreateWindow(// EDIT画面の作成
            /* クラスネーム              */ WC_EDIT,
            /* ウィンドウタイトル        */ W(mDefaultText).data(),
            /* ウィンドウスタイル        */ WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
            /* x座標(デフォルト値)       */ CW_USEDEFAULT,
            /* y座標(デフォルト値)       */ CW_USEDEFAULT,
            /* ウィンドウ横幅            */ CW_USEDEFAULT,
            /* ウィンドウ縦幅            */ CW_USEDEFAULT,
            /* 親ウィンドウハンドル      */ mWindow,
            /* メニューハンドル          */ (HMENU) ID_EDIT,
            /* モジュールインスタンス    */ aArgs.mInst,
            /* WM_CREATEのLPARAMに渡す値 */ this
            ));
    mDefaultProc = (WNDPROC) SetWindowLongPtr(edit, GWLP_WNDPROC, (LONG_PTR) WIN_PROC_EDIT);
    SetWindowLong(edit, GWL_USERDATA, uintptr_t(this));
    SetFocus(edit);
    CreateWindow(// ボタンの作成
            /* クラスネーム              */ WC_BUTTON,
            /* ウィンドウタイトル        */ W("決定").data(),
            /* ウィンドウスタイル        */ WS_CHILD | WS_VISIBLE | BS_TEXT,
            /* x座標(デフォルト値)       */ CW_USEDEFAULT,
            /* y座標(デフォルト値)       */ CW_USEDEFAULT,
            /* ウィンドウ横幅            */ CW_USEDEFAULT,
            /* ウィンドウ縦幅            */ CW_USEDEFAULT,
            /* 親ウィンドウハンドル      */ mWindow,
            /* メニューハンドル          */ (HMENU) ID_BUTTON,
            /* モジュールインスタンス    */ aArgs.mInst,
            /* WM_CREATEのLPARAMに渡す値 */ NULL
            );

    ShowWindow(mWindow, SW_SHOWNORMAL);

    RECT client;
    GetClientRect(mWindow, &client);
    KRect cRect(client);
    SetWindowPos(GetDlgItem(mWindow, ID_EDIT), NULL, cRect.x, cRect.y, cRect.width, cRect.height / 2, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(mWindow, ID_BUTTON), NULL, cRect.x, cRect.centerY(), cRect.width, cRect.height / 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

KInputWindow::~KInputWindow() {
    UnregisterClass(mClassName.data(), mArgs.mInst);
}

LRESULT KInputWindow::WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam) {
    KInputWindow * _this(NULL);

    if (aMsg == WM_NCCREATE) {
        _this = (KInputWindow*) ((LPCREATESTRUCT) aLParam)->lpCreateParams;
        SetWindowLong(aHwnd, GWL_USERDATA, uintptr_t(_this));
        _this->mExist = true;
    }

    _this = reinterpret_cast<KInputWindow*> (GetWindowLong(aHwnd, GWL_USERDATA));
    if (!_this) return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);

    _this->mDecide = false;

    switch (aMsg) {
        // ボタンの押下もしくはEnterキーで決定
        case WM_KEYDOWN:
            if (aWParam == VK_RETURN) _this->mDecide = true;
            break;
        case WM_COMMAND:
            switch (LOWORD(aWParam)) {
                case ID_BUTTON: _this->mDecide = true;
                    break;
            }
            break;
            
        case WM_DESTROY: _this->mExist = false;
    }

    return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);
}

LRESULT KInputWindow::WIN_PROC_EDIT(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam) {
    KInputWindow * _this(NULL);

    _this = reinterpret_cast<KInputWindow*> (GetWindowLong(aHwnd, GWL_USERDATA));
    if (!_this) return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);

    if (aMsg == WM_KEYDOWN && aWParam == VK_RETURN) {
        SendMessage(GetDlgItem(_this->mWindow, ID_BUTTON), BM_CLICK, aWParam, aLParam);
    }

    return _this->mDefaultProc(aHwnd, aMsg, aWParam, aLParam);
}

const bool& KInputWindow::exist() const {
    return mExist;
}

const bool& KInputWindow::decide() const {
    return mDecide;
}

void KInputWindow::close() {
    DestroyWindow(mWindow);
}

String KInputWindow::getText() const {
    char text[1024];
    GetWindowText(GetDlgItem(mWindow, ID_EDIT), text, 1024);
    return P(text);
}

