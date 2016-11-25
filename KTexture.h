/**
 * @file KTexture.h
 * @author Maeda Takumi
 */
#ifndef KTEXTURE_H
#define KTEXTURE_H

#include "KUtility.h"

#include "KNonCopy.h"

class KCharset;
class KImage;
class KRect;
class KVector;

class KTexture : private KNonCopy {
private:
    byte * const mPixel;

    const unsigned int mSize;
    const unsigned int mName;
public:
    KTexture(const unsigned int& aSize);
    KTexture(const unsigned int& aSize, const KImage& aImage);
    virtual ~KTexture();

    void update();

    void bindON() const;
    void bindOFF() const;

    /* ------------------------- Paint.cpp ------------------------- */

    /**
     * 
     * @param x
     * @param y
     * @return 
     */
    inline byte* getPixel(const int&x, const int& y) {
        if (x < 0 || mSize - 1 < x || y < 0 || mSize - 1 < y) return NULL;
        return mPixel + y * mSize * 4 + x * 4;
    };

    /**
     * 
     * @param pixel
     * @param aColor
     */
    static inline void setPixel(byte * const pixel, const color& aColor) {
        if (pixel) {
            byte alpha = aColor >> 24, disAlpha = 255 ^ alpha;
            if (alpha) {
                byte alphaTmp = disAlpha * *(pixel + 3) / 0xff;
                byte alphaResult = alpha + alphaTmp;
                *(pixel + 0) = (((aColor & 0xff0000) >> 8 * 2) * alpha + *(pixel + 0) * alphaTmp) / alphaResult;
                *(pixel + 1) = (((aColor & 0x00ff00) >> 8 * 1) * alpha + *(pixel + 1) * alphaTmp) / alphaResult;
                *(pixel + 2) = (((aColor & 0x0000ff) >> 8 * 0) * alpha + *(pixel + 2) * alphaTmp) / alphaResult;
                *(pixel + 3) = alphaResult;
            }
        }
    }

    /**
     * 
     * @param aRect
     */
    void clearRect(const KRect& aRect);

    /**
     * @brief ウィンドウに直線を描画
     * @param fromX  始点をあらわすx座標
     * @param fromY  始点をあらわすy座標
     * @param distX  終点をあらわすx座標
     * @param distY  終点をあらわすy座標
     * @param aColor 描画色
     */
    void drawLine(const int& fromX, const int& fromY, const int& distX, const int& distY, const color& aColor);
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
     * 
     * @param aCharset
     * @param aTxt
     * @param aVec
     * @param aColor
     */
    void drawText(const KCharset& aCharset, const String& aTxt, const KVector& aVec, const color& aColor);
    /**
     * @brief 画像の描画
     * @param aImage 画像
     * @param aSrc   画像描画領域
     * @param aDist  描画座標
     */
    void drawImage(const KImage& aImage, const KRect& aSrc, const KVector& aDist);
};

#endif /* KTEXTURE_H */

