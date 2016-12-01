/**
 * @file   KTexture.h
 * @brief  KTesture
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

/**
 * @brief  \~english  System of Texture Mapping
 * @brief  \~japanese テクスチャマッピングシステム
 * @author \~ Maeda Takumi
 */
class KTexture : private KNonCopy {
private:
    /**
     * @brief \~english  pixel info
     * @brief \~japanese 画素情報
     */
    byte * const mPixel;

    /**
     * @brief \~english  size of texture
     * @brief \~japanese テクスチャサイズ
     */
    const unsigned int mSize;
    /**
     * @brief \~english  name of registration
     * @brief \~japanese テクスチャ登録名
     */
    const unsigned int mName;
public:
    KTexture(const unsigned int& aSize);
    virtual ~KTexture();

    /**
     * @brief \~english  reflect drawing change.
     * @brief \~japanese 描画内容を反映します。
     */
    void reflect();

    /**
     * @brief \~english  enable texture.
     * @brief \~japanese テクスチャを使用可能にします。
     */
    void bindON() const;
    /**
     * @brief \~english  disable texture.
     * @brief \~japanese テクスチャを使用不可にします。
     */
    void bindOFF() const;

    /* ------------------------- in Paint.cpp ------------------------- */

    /**
     * \~english
     * @brief  return a pixel information pointer at the specified position.
     * @param  x x-coordinate
     * @param  y y-coordinate
     * @return pixel information pointer
     * @note   when specify out of pixel information, return NULL.
     * \~japanese
     * @brief  指定位置の画素情報ポインタを返します。
     * @param  x x座標
     * @param  y y座標
     * @return 画素情報ポインタ
     * @note   画僧情報外が指定された場合NULLを返します。
     */
    inline byte* getPixel(const int&x, const int& y) {
        if (x < 0 || mSize - 1 < x || y < 0 || mSize - 1 < y) return NULL;
        return mPixel + y * mSize * 4 + x * 4;
    };

    /**
     * \~english
     * @brief Mix color information to the entity of the pixel information pointer.
     * @param pixel  pixel information
     * @param aColor color information
     * @note  If the pixel information pointer is NULL, processing is not performed.
     * \~japanese
     * @brief 画素情報ポインタの実体に色情報を混合します。
     * @param pixel  画素情報ポインタ
     * @param aColor 色情報
     * @note  画素情報ポインタがNULLの場合は処理を行いません。
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
     * \~english
     * @brief Clear the pixel information of the specified area.
     * @param aRect specified area
     * \~japanese
     * @brief 指定領域の画素情報をクリアします。
     * @param aRect 指定領域
     */
    void clearRect(const KRect& aRect);

    /**
     * \~english
     * @brief draw a straight line in pixel information.
     * @param fromX  start point x-coordinate
     * @param fromY  start point y-coordinate
     * @param toX   end point x-coordinate
     * @param toY   end point y-coordinate
     * @param aColor drawing color
     * \~japanese
     * @brief 画素情報に直線を描画します。
     * @param fromX  始点x座標
     * @param fromY  始点y座標
     * @param toX   終点x座標
     * @param toY   終点y座標
     * @param aColor 描画色
     */
    void drawLine(const int& fromX, const int& fromY, const int& toX, const int& toY, const color& aColor);
    void drawLine(const KVector& fromVec, const KVector& toVec, const color& aColor);
    void drawHLine(const int& fromX, const int& distX, const int& y, const color& aColor);
    void drawVLine(const int& fromY, const int& distY, const int& x, const color& aColor);

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
     * \~english
     * @brief draw Image in pixel information.
     * @param aImage Image information
     * @param aSrc   Image area
     * @param aDist  drawing area
     * \~japanese
     * @brief 画素情報に画像を描画します。
     * @param aImage 画像情報
     * @param aSrc   画像領域
     * @param aDist  描画領域
     */
    void drawImage(const KImage& aImage, const KRect& aSrc, const KVector& aDist);
    /**
     * \~english
     * @brief draw monochrome Image with specified color in pixel information.
     * @param aImage Image information
     * @param aSrc   Image area
     * @param aDist  drawing area
     * @param aColor drawing color
     * \~japanese
     * @brief 画素情報に指定色でモノクロ画像を描画します。
     * @param aImage 画像情報
     * @param aSrc   画像領域
     * @param aDist  描画領域
     * @param aColor 描画色
     */
    void drawImageMono(
            const KImage& aImage,
            const KRect& aSrc,
            const KVector& aDist,
            const color& aColor
            );
    /**
     * 
     * @param aCharset
     * @param aTxt
     * @param aVec
     * @param aColor
     */
    void drawText(const KCharset& aCharset, const String& aTxt, const KVector& aVec, const color& aColor);
};

#endif /* KTEXTURE_H */

