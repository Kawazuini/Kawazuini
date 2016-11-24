/**
 * @file KImage.h
 * @author Maeda Takumi
 */
#ifndef KIMAGE_H
#define KIMAGE_H

#include "KUtility.h"

#include "KNonCopy.h"

class KImage : private KNonCopy {
public:

    /** @brief 画像拡張子 */
    typedef enum {
        /** (.ico) */ ICO,
        /** (.bmp) */ BMP,
        /** (.jpg) */ JPG,
        /** (.gif) */ GIF,
        /** (.png) */ PNG,
    } ext;
private:

    static const class KInit {
    private:
        ULONG_PTR mGdiplus;
    public:

        KInit() {
            using namespace Gdiplus;
            GdiplusStartupInput startUp;
            GdiplusStartup(&mGdiplus, &startUp, NULL);
        };

        virtual ~KInit() {
            using namespace Gdiplus;
            GdiplusShutdown(mGdiplus);
        };
    } GPINIT;

    /** @brief GDI+画像定義 */ typedef Gdiplus::Bitmap GBitmap;
    /** @brief リソース画像 */ GBitmap * const mResource;

    /**
     * @brief リソースからイメージを読み込む
     * @note GDI+が開始されていない場合,プログラムは不正終了する
     */
    GBitmap* loadImage(const int& aId, const ext& aExt);
public:
    const int mWidth; ///< 横幅
    const int mHeight; ///< 縦幅
    const color * const mPixel; ///< 画素情報

    /**
     * @param aId リソースID
     * @param aExt 画像拡張子
     */
    KImage(const int& aId, const ext& aExt = ext::PNG);
    virtual ~KImage();
};

#endif /* KIMAGE_H */

