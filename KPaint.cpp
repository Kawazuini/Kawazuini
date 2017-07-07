/**
 * @file   KPaint.cpp
 * @brief  KTexture
 * @author Maeda Takumi
 */
#include "KTexture.h"

#include "KCharset.h"
#include "KImage.h"
#include "KMath.h"
#include "KRect.h"
#include "KVector.h"

void KTexture::clearRect(const KRect& aRect) {
    for (int i = aRect.y, i_e = aRect.height + i; i < i_e; ++i) {
        for (int j = aRect.x, j_e = aRect.width + j; j < j_e; ++j) {
            byte * pix(getPixel(j, i));
            if (pix) *(pix + 0) = *(pix + 1) = *(pix + 2) = *(pix + 3) = 0;
        }
    }
}

void KTexture::drawLine(const int& fromX, const int& fromY, const int& toX, const int& toY, const color& aColor) {
    int width(toX - fromX);
    int height(toY - fromY);
    int abW(Math::abs(width));
    int abH(Math::abs(height));

    int x(fromX);
    int y(fromY);

    // Bresenham's algorithm
    int delSum = 0; // 増加値に対する変化値
    if (abW > abH) {
        int sigH = Math::sign(height);
        if (fromX > toX) { // 反転
            x = toX;
            y = toY;
            sigH *= -1;
        }
        for (int i = 0; i < abW; ++i, ++x) {
            if ((delSum += abH) >= abW) {
                y += sigH;
                delSum -= abW;
            }
            drawPixel(getPixel(x, y), aColor);
        }
    } else {
        int sigW = Math::sign(width);
        if (fromY > toY) { // 反転
            x = toX;
            y = toY;
            sigW *= -1;
        }
        for (int i = 0; i < abH; ++i, ++y) {
            if ((delSum += abW) >= abH) {
                x += sigW;
                delSum -= abH;
            }
            drawPixel(getPixel(x, y), aColor);
        }
    }
}

void KTexture::drawLine(const KVector& fromVec, const KVector& toVec, const color& aColor) {
    drawLine(fromVec.x, fromVec.y, toVec.x, toVec.y, aColor);
}

void KTexture::drawHLine(const int& fromX, const int& distX, const int& y, const color& aColor) {
    for (int i = Math::min(fromX, distX), i_e(Math::max(fromX, distX)); i <= i_e; ++i) {
        drawPixel(getPixel(i, y), aColor);
    }
}

void KTexture::drawVLine(const int& fromY, const int& distY, const int& x, const color& aColor) {
    for (int i = Math::min(fromY, distY), i_e(Math::max(fromY, distY)); i <= i_e; ++i) {
        drawPixel(getPixel(x, i), aColor);
    }
}

void KTexture::drawRect(const KRect& aRect, const color& aColor) {
    for (int i = aRect.y, i_e(aRect.height + i); i < i_e; ++i) {
        for (int j = aRect.x, j_e(aRect.width + j); j < j_e; ++j) {
            drawPixel(getPixel(j, i), aColor);
        }
    }
}

void KTexture::drawClearRect(const KRect& aRect, const color& aColor) {
    const int right(aRect.right() - 1), bottom(aRect.bottom() - 1);
    drawHLine(aRect.x, right, aRect.y, aColor); // ↑
    drawHLine(aRect.x, right, bottom, aColor); // ↓
    drawVLine(aRect.y, bottom, aRect.x, aColor); // ←
    drawVLine(aRect.y, bottom, right, aColor); // →
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
        drawPixel(getPixel(x - cx, y - cy), aColor);
        drawPixel(getPixel(x - cx, y + cy), aColor);
        drawPixel(getPixel(x + cx, y - cy), aColor);
        drawPixel(getPixel(x + cx, y + cy), aColor);
        drawPixel(getPixel(x - cy, y - cx), aColor);
        drawPixel(getPixel(x - cy, y + cx), aColor);
        drawPixel(getPixel(x + cy, y - cx), aColor);
        drawPixel(getPixel(x + cy, y + cx), aColor);
    }
}

void KTexture::drawImage(const KImage& aImage, const KRect& aSrc, const KVector& aDist) {
    const color * data(aImage.mPixel + aSrc.y * aImage.mWidth + aSrc.x);
    for (int i = aDist.y, i_e = aSrc.height + i, i_diff = aImage.mWidth - aSrc.width; i < i_e; ++i, data += i_diff) {
        for (int j = aDist.x, j_e = aSrc.width + j; j < j_e; ++j, ++data) {
            drawPixel(getPixel(j, i), *data);
        }
    }
}

void KTexture::drawImageMono(
        const KImage& aImage,
        const KRect& aSrc,
        const KVector& aDist,
        const color& aColor
        ) {
    double alphaCoef((double) (aColor & 0xff000000) / 0xff000000);
    color monoColor(aColor & 0x00ffffff);

    const color * data(aImage.mPixel + aSrc.y * aImage.mWidth + aSrc.x);
    for (int i = aDist.y, i_e = aSrc.height + i, i_diff = aImage.mWidth - aSrc.width; i < i_e; ++i, data += i_diff) {
        for (int j = aDist.x, j_e = aSrc.width + j; j < j_e; ++j, ++data) {
            color alpha(*data & 0xff000000);
            if (alpha) {
                alpha = ((int) ((alpha >> 24) * alphaCoef) << 24);
                drawPixel(getPixel(j, i), alpha | monoColor);
            }
        }
    }
}

void KTexture::drawText(const KCharset& aCharset, const String& aTxt, const KVector& aVec, const color& aColor) {
    const TCHAR * txt(aTxt.data());
    KVector cursor(aVec);
    for (int i = 0, i_e = aTxt.size(); i < i_e; ++i) {
        KRect area(aCharset.getArea(txt + i));
        drawImageMono(aCharset.mImage, area, cursor, aColor);
        cursor += KVector(area.width);
        if (area.width > aCharset.mSize) i += 2;
    }
}

