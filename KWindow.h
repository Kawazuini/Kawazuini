/**
 * @file KWindow.h
 * @brief ウィンドウクラス
 */
#ifndef KWINDOW_H
#define KWINDOW_H

#include "KUtility.h"

#include "KNonCopy.h"

#include "KRect.h"

class KListener;

/** @brief ウィンドウ */
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

    /** @brief 枠幅込みのウィンドウサイズ */ KRect mWindowSize;
    /** @brief 枠幅抜きのウィンドウサイズ */ KRect mClientSize;

    /** @brief スクリーンサイズ */ KRect mScreenSize;
    /** @brief キャンバスサイズ */ KRect mCanvasSize;

    /** @brief 描画構造体            */ PAINTSTRUCT mPaint;
    /** @brief mPixelの生成に必要    */ BITMAPINFO mBmpInfo;

    color mClearColor; ///< 背景の消去色
    /** @brief イベント処理クラス */ KListener* mListener;

    /* ウィンドウプロシージャ */
    static LRESULT CALLBACK WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam);

    /* in WM_PAINT */
    void startPaint(); // 描画処理の開始
    void clearCanvas(); // 背景色でCanvasを塗りつぶす
    void trans(const HDC& aDist, const KRect& aDistRec, const HDC& aSrc, const KRect& aSrcRec) const; // HDC間の転写
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
    /** @param aColor    新しいクリアカラー         */ void setClearColor(const color& aColor);


    /**
     * @brief ウィンドウの画面上の領域を返す。
     * @return ウィンドウの画面上の領域
     */
    KRect windowArea() const;


    /** @return フルスクリーン状態 */ bool fullScreen() const;
};

#endif /* KWINDOW_H */
