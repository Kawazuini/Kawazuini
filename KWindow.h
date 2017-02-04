/**
 * @file   KWindow.h
 * @brief  KWindow
 * @author Maeda Takumi
 */
#ifndef KWINDOW_H
#define KWINDOW_H

#include "KNonCopy.h"
#include "KRect.h"
#include "KUtility.h"

class KListener;

/**
 * @brief  Windows Window
 * @author Maeda Takumi
 */
class KWindow : private KNonCopy {
    friend class KApplication;
    friend class KMouse;
public:

    /** @brief メイン関数の引数 */
    typedef struct {
        /** @brief インスタンスハンドル */ HINSTANCE mInst;
        /** @brief 常にNULL             */ HINSTANCE mPrevInst;
        /** @brief コマンドライン引数   */ LPSTR mCmndLine;
        /** @brief ウィンドウの表示方法 */ int mCmndShow;
    } MainArgs;

    /** @brief デフォルトのアスペクト比   */ static const float ASPECT;
    /** @brief デフォルトウィンドウサイズ */ static const KRect SIZE;
    /** @brief PCの画面サイズ             */ static const KRect DISPLAY_SIZE;
private:
    /** @brief メイン引数         */ const MainArgs * const mArgs;
    /** @brief 登録用文字列       */ const String mClassName;
    /** @brief ウィンドウクラス   */ const WNDCLASSEX mWindowClass;
    /** @brief ウィンドウハンドル */ const HWND mWindow;
    /** @brief 表示タイトル       */ String mTitle;

    /** @brief ウィンドウ生成状態 */ bool mExist;
    /** @brief 外枠表示           */ bool mFrameVisible;
    /** @brief フルスクリーン状態 */ bool mFullScreen;

    HDC mScreen; ///< 画面表示HDC

    int mFrameWidth;
    int mFrameHeight;

    /** @brief スクリーンサイズ */ KRect mScreenSize;

    /** @brief 描画構造体            */ PAINTSTRUCT mPaint;
    /** @brief ピクセルフォーマット  */ PIXELFORMATDESCRIPTOR mPixelFormat;

    /** @brief イベント処理クラス */ KListener* mListener;

    /* ウィンドウプロシージャ */
    static LRESULT CALLBACK WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam);

    /* in WM_PAINT */
    void startPaint(); // 描画処理の開始
    void clearCanvas(); // デパスバッファのクリア
    void display(); // 描画の表示

    HGLRC mGLRC;
public:

    /**
     * @param aArgs      メイン引数
     * @param aSize      表示サイズ
     * @param aTitle     表示タイトル
     * @param aResizable サイズ変更を許可するか
     */
    KWindow(
            const MainArgs* aArgs,
            const KRect& aSize,
            const String& aTitle = "",
            const bool& aResizable = false
            );
    virtual ~KWindow();

    /** @brief ウィンドウ表示 */ void show() const;
    /** @brief ウィンドウ隠蔽 */ void hide() const;

    /** @brief フレームの有無を切り替える */ void borderLoss();
    /** @brief フルスクリーンを切り替える */ void toFullScreen();

    /** @param aTitle    新しいタイトル             */ void setTitle(const String& aTitle);
    /** @param aSize     新しいサイズ               */ void setSize(const KRect& aSize);
    /** @param aListener ウィンドウイベントリスナー */ void setListener(KListener* aListener);

    /**
     * \~english
     * @brief  get window area in screen.
     * @return window area in screen
     * \~japanese
     * @brief  ウィンドウのスクリーン上の領域を返す。
     * @return ウィンドウのスクリーン上の領域
     */
    KRect windowArea() const;
    /**
     * \~english
     * @brief  get whether full screen.
     * @return whether full screen
     * \~japanese
     * @brief  フルスクリーン状態を取得します。
     * @return フルスクリーン状態
     */
    const bool& isFullScreen() const;
    /**
     * \~english
     * @brief  get whether active.
     * @return whether active
     * \~japanese
     * @brief  アクティブ状態を取得します。
     * @return アクティブ状態
     */
    bool isActive() const;
};

#endif /* KWINDOW_H */

