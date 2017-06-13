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
 * @brief  \~english  Windows Window
 * @brief  \~japanese ウィンドウ
 * @author \~ Maeda Takumi
 */
class KWindow : private KNonCopy {
    friend class KApplication;
    friend class KMouse;
public:

    /** @brief メイン関数の引数 */
    struct MainArgs {
        /** @brief インスタンスハンドル */ HINSTANCE mInst;
        /** @brief 常にNULL             */ HINSTANCE mPrevInst;
        /** @brief コマンドライン引数   */ LPSTR mCmndLine;
        /** @brief ウィンドウの表示方法 */ int mCmndShow;
    };

    /** @brief 既定のアスペクト比   */ static const float DEFAULT_ASPECT;
    /** @brief 既定ウィンドウサイズ */ static const KRect DEFAULT_SIZE;
    /** @brief PCの画面サイズ       */ static const KRect DISPLAY_SIZE;

    /** @brief メイン引数         */ const MainArgs& mArgs;
    /** @brief 登録用文字列       */ const String mClassName;
    /** @brief ウィンドウクラス   */ const WNDCLASSEX mWindowClass;
    /** @brief ウィンドウハンドル */ const HWND mWindow;

    /* イベント処理クラス */ KListener* mListener;
private:
    /* 表示タイトル       */ String mTitle;

    /* サイズ変更可能か   */ bool mResizable;

    /* ウィンドウ生成状態 */ bool mExist;

    /* 外枠表示           */ bool mFrameVisible;
    /* フルスクリーン状態 */ bool mFullScreen;
    /* フレーム幅         */ KRect mFrameWeight;

    /* 初期ウィンドウサイズ   */ KRect mInitialSize;
    /* 初期アスペクト比       */ float mInitialAspect;
    /* スクリーン領域         */ KRect mScreenArea;
    /* スクリーン領域の拡大率 */ float mScale;

    /* 画面表示HDC */ HDC mScreen;
    /* 描画構造体  */ PAINTSTRUCT mPaint;


    /* ウィンドウプロシージャ */
    static LRESULT CALLBACK WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam);

    // in WM_PAINT
    /* 描画処理の開始   */ void startPaint();
    /* バッファのクリア */ void clearCanvas();
    /* 描画の表示       */ void display();
public:
    /**
     * @param aArgs      メイン引数
     * @param aSize      表示サイズ
     * @param aTitle     表示タイトル
     * @param aResizable サイズ変更を許可するか
     */
    KWindow(
            const MainArgs& aArgs,
            const KRect& aSize,
            const String& aTitle = "",
            const bool& aResizable = false
            );
    virtual ~KWindow();

    /** @brief show window. */ void show() const;
    /** @brief hide window. */ void hide() const;

    /** @brief フレームの有無を切り替える */ void changeFrame();
    /** @brief フルスクリーンを切り替える */ void changeFullScreen();

    void setTitle(const String& aTitle);
    void setSize(const KRect& aSize);

    /**
     * @brief  get mouse position on screen.
     * @return mouse position on screen
     */
    KVector mousePositionOnScreen() const;

    /**
     * @brief  get initial window size.
     * @return initial window size
     */
    const KRect& initialSize() const;
    /**
     * @brief  get initial ratio of aspect.
     * @return initial ratio of aspect
     */
    const float& initialAspect() const;
    /**
     * @brief  get screen area.
     * @return screen area
     */
    const KRect& screenArea() const;
    /**
     * @brief  get scale of screen.
     * @return scale of screen
     */
    const float& scale() const;
    /**
     * @brief  get window area in screen.
     * @return window area in screen
     */
    KRect windowArea() const;
    /**
     * @brief  get client area in window.
     * @return client area in window
     */
    KRect clientArea() const;
    /**
     * @brief  get whether full screen.
     * @return whether full screen
     */
    const bool& isFullScreen() const;
    /**
     * @brief  get whether active.
     * @return whether active
     */
    bool isActive() const;
};

#endif /* KWINDOW_H */

