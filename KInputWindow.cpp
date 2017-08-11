/**
 * @file   KInputWindow.cpp
 * @brief  KInputWindow
 * @author Maeda Takumi
 */
#include "KInputWindow.h"

#include "KCharset.h"
#include "KWindows.h"

const int KInputWindow::ID_EDIT(1);
const int KInputWindow::ID_BUTTON(2);

KInputWindow::KInputWindow(
        const KWindow::MainArgs& aArgs,
        const KRect& aSize,
        const String& aTitle,
        const String& aText,
        const KCharset* aCharset
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
        /* ウィンドウスタイル        */ WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME) | WS_DLGFRAME,
        /* x座標(デフォルト値)       */ CW_USEDEFAULT,
        /* y座標(デフォルト値)       */ CW_USEDEFAULT,
        /* ウィンドウ横幅            */ aSize.width,
        /* ウィンドウ縦幅            */ aSize.height,
        /* 親ウィンドウハンドル      */ nullptr,
        /* メニューハンドル          */ nullptr,
        /* モジュールインスタンス    */ aArgs.mInst,
        /* WM_CREATEのLPARAMに渡す値 */ this
        ) : nullptr)),
mDefaultText(aText),
mSize(aSize),
mDecide(false),
mFont("メイリオ", 20),
mCharset(aCharset) {
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
    HWND button(CreateWindow(// ボタンの作成
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
            /* WM_CREATEのLPARAMに渡す値 */ nullptr
            ));

    SendMessage(edit, WM_SETFONT, (WPARAM) mFont.font(), 0);
    SendMessage(button, WM_SETFONT, (WPARAM) mFont.font(), 0);

    RECT client;
    GetClientRect(mWindow, &client);
    KRect cRect(client);
    SetWindowPos(GetDlgItem(mWindow, ID_EDIT), nullptr, cRect.x, cRect.y, cRect.width, cRect.height / 2, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(mWindow, ID_BUTTON), nullptr, cRect.x, cRect.centerY(), cRect.width, cRect.height / 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

KInputWindow::~KInputWindow() {
    DestroyWindow(mWindow);
    UnregisterClass(mClassName.data(), mArgs.mInst);
}

LRESULT KInputWindow::WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam) {
    KInputWindow * _this(nullptr);

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
    KInputWindow * _this(nullptr);

    _this = reinterpret_cast<KInputWindow*> (GetWindowLong(aHwnd, GWL_USERDATA));
    if (!_this) return DefWindowProc(aHwnd, aMsg, aWParam, aLParam);

    if (aMsg == WM_KEYDOWN && aWParam == VK_RETURN) {
        SendMessage(GetDlgItem(_this->mWindow, ID_BUTTON), BM_CLICK, aWParam, aLParam);
    }

    return _this->mDefaultProc(aHwnd, aMsg, aWParam, aLParam);
}

String KInputWindow::getText() const {
    String text;

    ShowWindow(mWindow, SW_SHOWNORMAL);

    while (mExist) {
        if (mDecide) {
            text = getEditText();
            if (mCharset && !mCharset->getDrawable(text)) message("使える文字は半角英数字・ひらがな・カタカナです。", "使えない文字が含まれています。");
            else if (text.empty()) message("使える文字は半角英数字・ひらがな・カタカナです。", "文字を入力してください。");
            else break;
        }

        MSG msg;
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    ShowWindow(mWindow, SW_HIDE);
    return text;
}

