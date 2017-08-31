/**
 * @file   KImage.cpp
 * @brief  KImage
 * @author Maeda Takumi
 */
#include "KImage.h"

#include "KFileDialog.h"

const KImage::KInit KImage::GPINIT;

KImage::KImage(GBitmap* aResource) :
mResource(aResource),
mWidth(mResource->GetWidth()),
mHeight(mResource->GetHeight()),
mPixel(new color[mWidth * mHeight]) {
    using namespace Gdiplus;

    // 画像内容にアクセス可能に
    Rect rect(0, 0, mWidth, mHeight);
    BitmapData source;
    mResource->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &source);
    byte * array((byte*) source.Scan0);

    // 配列の写しをとる
    color * pixel(const_cast<color*> (mPixel));
    for (int i = 0, i_e(mWidth * mHeight - 1); i < i_e; ++i, ++pixel) {
        *pixel = *array++ | *array++ << 8 | *array++ << 16 | *array++ << 24;
    }
    mResource->UnlockBits(&source);
}

KImage::KImage() :
KImage(loadImage()) {
}

KImage::KImage(const int& aId, const Extension& aExt) :
KImage(loadImage(aId, aExt)) {
}

KImage::~KImage() {
    delete mResource;
    delete[] mPixel;
}

KImage::GBitmap* KImage::loadImage(const int& aId, const Extension& aExt) {
    using namespace Gdiplus;

    Bitmap* bmp; // 返却値
    String resName("#" + toString(aId));

    String imageType;
    switch (aExt) {
        case BMP:
            bmp = Bitmap::FromResource(GetModuleHandle(nullptr), (const WCHAR *) MAKEINTRESOURCE(aId));
            if (bmp->GetLastStatus() == Ok) return bmp;
        case JPG: imageType = "JPEG";
            break;
        case GIF: imageType = "GIF";
            break;
        case PNG: imageType = "PNG";
    }

    HRSRC hResource(FindResource(nullptr, resName.data(), imageType.data()));
    if (!hResource) throw Error(resName + " is not found");
    DWORD resSize(SizeofResource(nullptr, hResource));
    if (!resSize) throw Error(resName + "'s size is zero");
    const void* resData(LockResource(LoadResource(nullptr, hResource)));
    if (!resData) throw Error("Loading is failed : " + resName);
    HGLOBAL hResBuffer(GlobalAlloc(GMEM_MOVEABLE, resSize));
    if (!hResBuffer) {
        GlobalFree(hResBuffer);
        throw Error("Securing memory is failed");
    }
    LPVOID resBuffer(GlobalLock(hResBuffer));
    if (!resBuffer) {
        GlobalUnlock(hResBuffer);
        GlobalFree(hResBuffer);
        throw Error("GlobalLock is failed");
    }

    CopyMemory(resBuffer, resData, resSize);

    IStream * iStream(nullptr);
    if (CreateStreamOnHGlobal(hResBuffer, false, &iStream) == S_OK) {
        bmp = Bitmap::FromStream(iStream);

        iStream->Release();
        GlobalUnlock(hResBuffer);
        GlobalFree(hResBuffer);

        if (!bmp) throw Error("Creating BMP is failed");

        if (bmp->GetLastStatus() == Ok) return bmp;
        delete bmp;
        throw Error(resName + " is failed");
    }
    GlobalUnlock(hResBuffer);
    GlobalFree(hResBuffer);
    throw Error("Creating Stream is failed");
}

KImage::GBitmap* KImage::loadImage(const String& aFileName) {
    WCHAR wpath[MAX_PATH];
    std::mbstowcs(wpath, aFileName.data(), aFileName.size());
    return GBitmap::FromFile(wpath);
}

KImage::GBitmap* KImage::loadImage() {
    KFileDialog fd(
            KFileDialog::Filters{
        {"BMP", "*.bmp"},
        {"GIF", "*.gif"},
        {"JPEG", "*.jpg"},
        {"PNG", "*.png"},
        {"All Types", "*.*"}
    },
    "png",
    4
    );

    while (true) { // 開くまで続行
        if (fd.open()) return loadImage(fd.pathName());
    }
}

