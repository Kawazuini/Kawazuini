/**
 * @file KGLUI.h
 * @author Maeda Takumi
 */
#ifndef KGLUI_H
#define KGLUI_H

#include "KUtility.h"

#include "KNonCopy.h"

class KCamera;
class KImage;
class KRect;
class KVector;

class KGLUI : private KNonCopy {
public:
    static const int WIDTH; ///< 横幅
    static const int HEIGHT; ///< 縦幅
private:
    const KCamera * const mCamera;

    color * const mPixel; ///< 画面の画素情報    
public:
    KGLUI(const KCamera& aCamera);
    virtual ~KGLUI();

    /** @brief 描画処理 */
    void draw() const;

    void clearRect(const KRect& aRect);

    /* ------------------------- Paint.cpp ------------------------- */

    /** @return 指定座標のピクセルポインタ(安全性確保) */
    inline color* getPixel(const int&x, const int& y) {
        if (x < 0 || WIDTH - 1 < x || y < 0 || HEIGHT - 1 < y) return NULL;
        return mPixel + y * WIDTH + x;
    };

    /** @brief 指定ピクセルポインタに色を置く */
    static inline void setPixel(color * const pixel, const color& aColor) {
        if (pixel) {
            int alpha = aColor >> 24, disAlpha = 255 ^ alpha;
            if (alpha) {
                *pixel =
                        ((((aColor & 0xff00ff) * alpha + (*pixel & 0xff00ff) * disAlpha) >> 8) & 0xff00ff) |
                        ((((aColor & 0x00ff00) * alpha + (*pixel & 0x00ff00) * disAlpha) >> 8) & 0x00ff00);
            }
        }
    }
    /**
     * @brief ウィンドウに直線を描画
     * @param fromX  始点をあらわすx座標
     * @param fromY  始点をあらわすy座標
     * @param distX  終点をあらわすx座標
     * @param distY  終点をあらわすy座標
     * @param aColor 描画色
     */
    void drawLine(const int& fromX, const int& fromY, const int& distX, const int& distY, const color& aColor);
    void drawLineSafety(const int& fromX, const int& fromY, const int& distX, const int& distY, const color& aColor);
    void drawLine(const KVector& fromVec, const KVector& toVec, const color& aColor);
    void drawHLine(const int& fromX, const int& distX, const int& y, const color& aColor); // 水平線
    void drawVLine(const int& fromY, const int& distY, const int& x, const color& aColor); // 垂直線
    /**
     * @brief ウィンドウに矩形を描画
     * @param aRect  描画する矩形
     * @param aColor 描画色
     */
    void drawRect(const KRect& aRect, const color& aColor);
    /**
     * @brief ウィンドウに透明な矩形(枠のみ)を描画
     * @param aRect  描画する矩形
     * @param aColor 描画色
     */
    void drawClearRect(const KRect& aRect, const color& aColor);

    /**
     * @brief 円を描画
     * @param aRadius 半径
     * @param aCenter 中心座標
     * @param aColor  描画色
     */
    void drawCircle(const int& aRadius, const KVector aCenter, const color& aColor);

    /**
     * @brief ウィンドウに文字を描画
     * @param aTxt   描画文字列
     * @param aVec   1文字目左上の座標
     * @param aColor 描画色(透過値無視)
     */
    void drawText(const String& aTxt, const KVector& aVec, const color& aColor);
    /**
     * @brief 画像の描画
     * @param aImage 画像
     * @param aSrc   画像描画領域
     * @param aDist  描画座標
     */
    void drawImage(const KImage& aImage, const KRect& aSrc, const KVector& aDist);
    /** @brief 反転描画 */
    void drawImageR(const KImage& aImage, const KRect& aSrc, const KVector& aDist);
};

#endif /* KGLUI_H */

