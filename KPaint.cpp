/**
 * @file KPaint.cpp
 * @author Maeda Takumi
 */
#include "KTexture.h"

#include "KImage.h"
#include "KMath.h"
#include "KVector.h"
#include "KRect.h"

void KTexture::drawLine(const int& fromX, const int& fromY, const int& distX, const int& distY, const color& aColor) {
    int width = distX - fromX, height = distY - fromY, abW = Math::abs(width), abH = Math::abs(height), dWidth = mSize; // 描画・画面幅
    int x = fromX, y = fromY;
    byte* pixel;

    // Bresenham's algorithm
    int delSum = 0; // 増加値に対する変化値
    if (abW > abH) {
        int sigH = Math::sign(height);
        if (fromX > distX) { // 反転
            x = distX;
            y = distY;
            sigH *= -1;
        }
        for (int i = 0; i < abW; ++i, ++x) {
            if ((delSum += abH) >= abW) {
                y += sigH;
                delSum -= abW;
            }
            setPixel(getPixel(x, y), aColor);
        }
    } else {
        int sigW = Math::sign(width);
        if (fromY > distY) { // 反転
            x = distX;
            y = distY;
            sigW *= -1;
        }
        for (int i = 0; i < abH; ++i, ++y) {
            if ((delSum += abW) >= abH) {
                x += sigW;
                delSum -= abH;
            }
            setPixel(getPixel(x, y), aColor);
        }
    }
}

void KTexture::drawLine(const KVector& fromVec, const KVector& toVec, const color& aColor) {
    drawLine(fromVec.x, fromVec.y, toVec.x, toVec.y, aColor);
}

void KTexture::drawHLine(const int& fromX, const int& distX, const int& y, const color& aColor) {
    int width = Math::abs(distX - fromX); // 描画・画面幅
    byte* pixel = mPixel + y * mSize * 4 + Math::min(fromX, distX) * 4;
    for (int i = 0; i < width; ++i, pixel += 4) setPixel(pixel, aColor);

}

void KTexture::drawVLine(const int& fromY, const int& distY, const int& x, const color& aColor) {
    int height = Math::abs(distY - fromY); // 描画・画面幅
    byte* pixel = mPixel + Math::min(fromY, distY) * mSize * 4 + x * 4;
    for (int i = 0; i < height; ++i, pixel += mSize * 4) setPixel(pixel, aColor);
}

void KTexture::drawRect(const KRect& aRect, const color& aColor) {
    for (int i = aRect.y, i_e = aRect.height + i; i < i_e; ++i) {
        for (int j = aRect.x, j_e = aRect.width + j; j < j_e; ++j) {
            setPixel(getPixel(j, i), aColor);
        }
    }
}

void KTexture::drawClearRect(const KRect& aRect, const color& aColor) {
    drawHLine(aRect.x, aRect.right(), aRect.y, aColor); // ↑
    drawHLine(aRect.x, aRect.right(), aRect.bottom(), aColor); // ↓
    drawVLine(aRect.y, aRect.bottom(), aRect.x, aColor); // ←
    drawVLine(aRect.y, aRect.bottom(), aRect.right(), aColor); // →
}

void KTexture::drawCircle(const int& aRadius, const KVector aCenter, const color& aColor) {
    int x = aCenter.x, y = aCenter.y;
    int d = 1 - aRadius, dH = 3, dD = 5 - 2 * aRadius;
    for (int cx = 0, cy = aRadius; cx < cy; cx++) {
        if (d < 0) {
            d += dH;
            dH += 2;
            dD += 2;
        } else {
            d += dD;
            dH += 2;
            dD += 4;
            --cy;
        }
        // 45度ずつ描画
        setPixel(getPixel(x - cx, y - cy), aColor);
        setPixel(getPixel(x - cx, y + cy), aColor);
        setPixel(getPixel(x + cx, y - cy), aColor);
        setPixel(getPixel(x + cx, y + cy), aColor);
        setPixel(getPixel(x - cy, y - cx), aColor);
        setPixel(getPixel(x - cy, y + cx), aColor);
        setPixel(getPixel(x + cy, y - cx), aColor);
        setPixel(getPixel(x + cy, y + cx), aColor);
    }
}

void KTexture::drawText(const String& aTxt, const KVector& aVec, const color& aColor) {
}

void KTexture::drawImage(const KImage& aImage, const KRect& aSrc, const KVector& aDist) {
    // const KArray<color>* tmp = aImage.mData;
    // color* data = tmp->mArray + aSrc.y * tmp->mIndexY + aSrc.x * tmp->mIndexX;
    // for (int i = aDist.y, i_e = aSrc.height + i; i < i_e; ++i, data += tmp->mIndexY - aSrc.width) {
    //     for (int j = aDist.x, j_e = aSrc.width + j; j < j_e; ++j, ++data) {
    //         setPixel(getPixel(j, i), *data);
    //     }
    // }
}

void KTexture::drawImageR(const KImage& aImage, const KRect& aSrc, const KVector& aDist) {
}

