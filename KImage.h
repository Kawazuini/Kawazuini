/**
 * @file   KImage.h
 * @brief  KImage
 * @author Maeda Takumi
 */
#ifndef KIMAGE_H
#define KIMAGE_H

#include "KUtility.h"
#include "KNonCopy.h"

/**
 * @brief  \~english  image object
 * @brief  \~japanese 画像オブジェクト
 * @author \~ Maeda Takumi
 */
class KImage : private KNonCopy {
private:

    /* GDI+の初期化 */
    static const class KInit final : private KNonCopy {
    private:
        ULONG_PTR mGdiplus;
    public:

        KInit() {
            Gdiplus::GdiplusStartupInput startUp;
            Gdiplus::GdiplusStartup(&mGdiplus, &startUp, nullptr);
        };

        ~KInit() {
            Gdiplus::GdiplusShutdown(mGdiplus);
        };
    } GPINIT;

    /* GDI+画像定義 */ using GBitmap = Gdiplus::Bitmap;
    /* リソース画像 */ GBitmap * const mResource;

    /* リソースからイメージを読み込みます。 */
    GBitmap* loadImage(const int& aId, const Extension& aExt);
    /* ファイルパスからイメージを読み込みます。 */
    GBitmap* loadImage(const String& aFileName);
    /* ファイルダイアログからイメージを読み込みます。 */
    GBitmap* loadImage();

    KImage(GBitmap* aResource);
public:
    /// @brief \~english  width
    /// @brief \~japanese 横幅
    const int mWidth;
    /// @brief \~english  height
    /// @brief \~japanese 縦幅
    const int mHeight;
    /// @brief \~english  pixel information
    /// @brief \~japanese 画素情報
    const color * const mPixel;

    KImage();
    /**
     * \~english
     * @param aId  resource ID
     * @param aExt image extension
     * \~japanese
     * @param aId  リソースID
     * @param aExt 画像拡張子
     */
    KImage(const int& aId, const Extension& aExt = PNG);
    virtual ~KImage();
};

#endif /* KIMAGE_H */

