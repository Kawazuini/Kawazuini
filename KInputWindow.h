/**
 * @file   KInputWindow.h
 * @brief  KInputWindow
 * @author Maeda Takumi
 */
#ifndef KINPUTWINDOW_H
#define KINPUTWINDOW_H

#include "KCharset.h"
#include "KFont.h"
#include "KWindow.h"

class KCharset;

/**
 * @brief  \~english  Window that has EDIT function
 * @brief  \~japanese EDIT機能を持ったウィンドウ
 * @author Maeda Takumi
 */
class KInputWindow : private KNonCopy {
private:
    /* エディットID */ static const int ID_EDIT;
    /* ボタンID     */ static const int ID_BUTTON;

    /* メイン引数         */ const KWindow::MainArgs& mArgs;
    /* 登録用文字列       */ const String mClassName;
    /* ウィンドウクラス   */ const WNDCLASSEX mWindowClass;
    /* ウィンドウハンドル */ const HWND mWindow;

    /* ウィンドウ生存状況 */ bool mExist;
    /* ボタン押下状態     */ bool mDecide;
    /* 初期テキスト       */ const String mDefaultText;
    /* ウィンドウサイズ   */ const KRect mSize;

    /* フォント           */ KFont mFont;

    /* ウィンドウプロシージャ       */ static LRESULT CALLBACK WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam);
    /* デフォルトのEDITプロシージャ */ WNDPROC mDefaultProc;
    /* EDITプロシージャ             */ static LRESULT CALLBACK WIN_PROC_EDIT(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam);

    /* 文字列チェック用文字セット   */ const KCharset* mCharset;

    /* エディットのテキストを取得 */
    inline String getEditText() const {
        char text[1024];
        GetWindowText(GetDlgItem(mWindow, ID_EDIT), text, 1024);
        return P(text);
    }
public:
    /**
     * \~english
     * @param aArgs  main args
     * @param aSize  window size
     * @param aTitle window title
     * @param aText  default text
     * \~japanese
     * @param aArgs  メイン引数
     * @param aSize  ウィンドウサイズ
     * @param aTitle ウィンドウタイトル
     * @param aText  デフォルトテキスト
     */
    KInputWindow(
            const KWindow::MainArgs& aArgs,
            const KRect& aSize,
            const String& aTitle,
            const String& aText,
            const KCharset* aCharset = nullptr
            );
    virtual ~KInputWindow();

    /**
     * \~english
     * @brief  get edit contents.
     * @return edit contents
     * \~japanese
     * @brief  エディット内容を取得します。
     * @return エディット内容
     */
    String getText() const;
};

#endif /* KINPUTWINDOW_H */

