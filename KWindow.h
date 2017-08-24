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

    /**
     * @brief \~english  arguments of main function
     * @brief \~japanese メイン関数の引数
     */
    struct MainArgs {
        /// @brief \~english  handle of instance
        /// @brief \~japanese インスタンスハンドル
        HINSTANCE mInst;
        /// @brief \~english  null at allways
        /// @brief \~japanese 常にNULL
        HINSTANCE mPrevInst;
        /// @brief \~english  arguments of command line
        /// @brief \~japanese コマンドライン引数
        LPSTR mCmndLine;
        /// @brief \~english  how to display windows
        /// @brief \~japanese ウィンドウの表示方法
        int mCmndShow;
    };

    /// @brief \~english  display size of PC
    /// @brief \~japanese PCの画面サイズ
    static const KRect DISPLAY_SIZE;

    /// @brief \~english  arguments of main function
    /// @brief \~japanese メイン引数
    const MainArgs& mArgs;
    /// @brief \~english  name for registration
    /// @brief \~japanese 登録用文字列
    const String mClassName;
    /// @brief \~english  window class
    /// @brief \~japanese ウィンドウクラス
    const WNDCLASSEX mWindowClass;
    /// @brief \~english  window handle
    /// @brief \~japanese ウィンドウハンドル
    const HWND mWindow;
private:
    /* イベント処理クラス     */ KListener* mListener;
    /* ウィンドウ生成状態     */ bool mExist;

    /* 表示タイトル           */ String mTitle;

    /* サイズ変更可能か       */ bool mResizable;
    /* 外枠表示               */ bool mFrameVisible;
    /* フルスクリーン状態     */ bool mFullScreen;
    /* フレーム幅             */ KRect mFrameWeight;
    /* 初期ウィンドウサイズ   */ KRect mInitialSize;
    /* 初期アスペクト比       */ float mInitialAspect;
    /* スクリーン領域         */ KRect mScreenArea;
    /* スクリーン領域の拡大率 */ float mScale;

    /* 画面表示HDC            */ HDC mScreen;
    /* 描画構造体             */ PAINTSTRUCT mPaint;


    /* ウィンドウプロシージャ */
    static LRESULT CALLBACK WIN_PROC(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam);

    // in WM_PAINT
    /* 描画処理の開始   */ void startPaint();
    /* バッファのクリア */ void clearCanvas();
    /* 描画内容の表示   */ void display();

    /* 画像保存用       */ bool getEncoder(const WCHAR& aFormat, CLSID& aClsid);
public:
    /**
     * \~english
     * @param aArgs      arguments of main function
     * @param aSize      client size
     * @param aTitle     window title
     * @param aResizable whether resizable
     * \~japanese
     * @param aArgs      メイン引数
     * @param aSize      フレームを除いた画面サイズ
     * @param aTitle     ウィンドウタイトル
     * @param aResizable サイズ変更を許可するか
     */
    KWindow(
            const MainArgs& aArgs,
            const KRect& aSize,
            const String& aTitle = "",
            const bool& aResizable = false
            );
    virtual ~KWindow();

    /// @brief \~englsih  show window.
    /// @brief \~japanese ウィンドウを表示します。
    void show() const;
    /// @brief \~englsih  hide window.
    /// @brief \~japanese ウィンドウを隠蔽します。
    void hide() const;

    /**
     * \~english
     * @brief save screen shot.
     * @param aFileName  file name
     * @param aExtension file extension
     * \~japanese
     * @brief スクリーンショットを保存します。
     * @param aFileName  ファイル名
     * @param aExtension ファイル拡張子
     */
    void screenShot(
            const String& aFileName,
            const Extension& aExtension
            );

    /// @brief \~english  change presence or absence of a frame.
    /// @brief \~japanese フレームの表示状態を変更します。
    void changeFrame();
    /// @brief \~english  change full screen state.
    /// @brief \~japanese フルスクリーン状態を変更します。
    void changeFullScreen();

    /// @breif \~english  set windows event listener.
    /// @breif \~japanese イベントリスナーを設定します。
    void setListener(KListener& aListener);
    /// @breif \~english  set title.
    /// @breif \~japanese タイトルを設定します。
    void setTitle(const String& aTitle);
    /// @breif \~english  set client size.
    /// @breif \~japanese クライアントサイズを設定します。
    void setSize(const KRect& aSize);

    /// @breif \~english  get mouse position on screen.
    /// @breif \~japanese スクリーン上のマウス座標を取得します。
    KVector getMousePositionOnScreen() const;
    /// @breif \~english  get windows event listener.
    /// @breif \~japanese イベントリスナーを取得します。
    const KListener& getListener() const;
    /// @breif \~english  get initial window size.
    /// @breif \~japanese 初期ウィンドウサイズを取得します。
    const KRect& getInitialSize() const;
    /// @breif \~english  get initial ratio of aspect.
    /// @breif \~japanese 初期アスペクト比を取得します。
    const float& getInitialAspect() const;
    /// @breif \~english  get screen area.
    /// @breif \~japanese スクリーン領域を取得します。
    const KRect& getScreenArea() const;
    /// @breif \~english  get scale of screen.
    /// @breif \~japanese スクリーン倍率を取得します。
    const float& getScale() const;
    /// @breif \~english  get window area in screen.
    /// @breif \~japanese スクリーン上のウィンドウ領域を取得します。
    KRect getWindowArea() const;
    /// @breif \~english  get client area in window.
    /// @breif \~japanese ウィンドウ上のクライアント領域を取得します。
    KRect getClientArea() const;
    /// @breif \~english  get whether full screen.
    /// @breif \~japanese フルスクリーン状態を取得します。
    const bool& isFullScreen() const;
    /// @breif \~english  get whether active.
    /// @breif \~japanese アクティブ状態を取得します。
    bool isActive() const;
};

#endif /* KWINDOW_H */

