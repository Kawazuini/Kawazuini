/**
 * @file KWindow.cpp
 * @brief KWindowクラスの実装
 */
#include "KWindow.h"

/*
#include "KFont.h"
#include "KImage.h"
#include "KInline.h"
#include "KMath.h"

void KWindow::drawLine(const int& fromX, const int& fromY, const int& distX, const int& distY, const color& aColor) {
    int width = distX - fromX, height = distY - fromY, abW = abs(width), abH = abs(height), dWidth = DISPLAY_SIZE.width; // 描画・画面幅
    int x = fromX, y = fromY;
    color* pixel;

    // Bresenham's algorithm
    int delSum = 0; // 増加値に対する変化値
    if (abW > abH) {
        int sigH = sign(height);
        if (fromX > distX) { // 反転
            x = distX;
            y = distY;
            sigH *= -1;
        }
        pixel = mPixel + y * dWidth + x;
        for (int i = 0; i < abW; ++i, ++pixel) {
            if ((delSum += abH) >= abW) {
                pixel += sigH * dWidth;
                delSum -= abW;
            }
            setPixel(pixel, aColor);
        }
    } else {
        int sigW = sign(width);
        if (fromY > distY) { // 反転
            x = distX;
            y = distY;
            sigW *= -1;
        }
        pixel = mPixel + y * dWidth + x;
        color* pixel = mPixel + (fromY < distY ? dWidth * fromY + fromX : dWidth * distY + distX);
        for (int i = 0; i < abH; ++i, pixel += dWidth) {
            if ((delSum += abW) >= abH) {
                pixel += sigW;
                delSum -= abH;
            }
            setPixel(pixel, aColor);
        }
    }
}

void KWindow::drawLineSafety(const int& fromX, const int& fromY, const int& distX, const int& distY, const color& aColor) {
    int width = distX - fromX, height = distY - fromY, abW = abs(width), abH = abs(height), dWidth = DISPLAY_SIZE.width; // 描画・画面幅
    int x = fromX, y = fromY;
    color* pixel;

    // Bresenham's algorithm
    int delSum = 0; // 増加値に対する変化値
    if (abW > abH) {
        int sigH = sign(height);
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
        int sigW = sign(width);
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

void KWindow::drawLine(const KVector& fromVec, const KVector& toVec, const color& aColor) {
    drawLine(fromVec.x, fromVec.y, toVec.x, toVec.y, aColor);
}

void KWindow::drawHLine(const int& fromX, const int& distX, const int& y, const color& aColor) {
    int width = abs(distX - fromX), dWidth = DISPLAY_SIZE.width; // 描画・画面幅
    color* pixel = mPixel + y * dWidth + min(fromX, distX);
    for (int i = 0; i < width; ++i, ++pixel) setPixel(pixel, aColor);

}

void KWindow::drawVLine(const int& fromY, const int& distY, const int& x, const color& aColor) {
    int height = abs(distY - fromY), dWidth = DISPLAY_SIZE.width; // 描画・画面幅
    color* pixel = mPixel + min(fromY, distY) * dWidth + x;
    for (int i = 0; i < height; ++i, pixel += dWidth) setPixel(pixel, aColor);
}

void KWindow::drawRect(const KRect& aRect, const color& aColor) {
    for (int i = aRect.y, i_e = aRect.height + i; i < i_e; ++i) {
        for (int j = aRect.x, j_e = aRect.width + j; j < j_e; ++j) {
            setPixel(getPixel(j, i), aColor);
        }
    }
}

void KWindow::drawClearRect(const KRect& aRect, const color& aColor) {
    drawHLine(aRect.x, aRect.right(), aRect.y, aColor); // ↑
    drawHLine(aRect.x, aRect.right(), aRect.bottom(), aColor); // ↓
    drawVLine(aRect.y, aRect.bottom(), aRect.x, aColor); // ←
    drawVLine(aRect.y, aRect.bottom(), aRect.right(), aColor); // →
}

void KWindow::drawCircle(const int& aRadius, const KVector aCenter, const color& aColor) {
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

void KWindow::drawText(const String& aTxt, const KVector& aVec, const color& aColor) {
    SetTextColor(mCanvas, aColor);
    TextOut(mCanvas, aVec.x, aVec.y, W(aTxt).data(), W(aTxt).size());
}

void KWindow::drawImage(const KImage& aImage, const KRect& aSrc, const KVector& aDist) {
    const KArray<color>* tmp = aImage.mData;
    color* data = tmp->mArray + aSrc.y * tmp->mIndexY + aSrc.x * tmp->mIndexX;
    for (int i = aDist.y, i_e = aSrc.height + i; i < i_e; ++i, data += tmp->mIndexY - aSrc.width) {
        for (int j = aDist.x, j_e = aSrc.width + j; j < j_e; ++j, ++data) {
            setPixel(getPixel(j, i), *data);
        }
    }
}

void KWindow::drawImageR(const KImage& aImage, const KRect& aSrc, const KVector& aDist) {
    const KArray<color>* tmp = aImage.mData;
    color* data = tmp->mArray + aSrc.y * tmp->mIndexY + aSrc.right() * tmp->mIndexX;
    for (int i = aDist.y, i_e = aSrc.height + i; i < i_e; ++i, data += tmp->mIndexY + aSrc.width) {
        for (int j = aDist.x, j_e = aSrc.width + j; j < j_e; ++j, --data) {
            setPixel(getPixel(j, i), *data);
        }
    }
}

void KWindow::drawArray(const KArray<color>& aArray, const int& aPixelSize, const KVector& aOff) {
    color* tmp = aArray.mArray;
    for (int i = aOff.y, i_e = i + aArray.mHeight * aPixelSize; i < i_e; i += aPixelSize) {
        for (int j = aOff.x, j_e = j + aArray.mWidth * aPixelSize; j < j_e; j += aPixelSize, ++tmp) {
            drawRect(KRect(j, i, aPixelSize, aPixelSize), *tmp);
        }
    }
}

void KWindow::drawGradation(const color& fColor, const color& tColor) {
    int width = mCanvasSize.width, height = mCanvasSize.height;
    color* pixel = mPixel;
    int pixelDef = DISPLAY_SIZE.width - width;
    float diff = 255.0 / height; // 全体をかけて目的に近づく
    for (int i = 0, variation = 0; i < height; ++i, pixel += pixelDef, variation = diff * i) {
        for (int j = 0; j < width; ++j, ++pixel) {
            *pixel =
                    ((((tColor & 0xff00ff) * variation + (fColor & 0xff00ff) * (255 ^ variation)) >> 8) & 0xff00ff) |
                    ((((tColor & 0x00ff00) * variation + (fColor & 0x00ff00) * (255 ^ variation)) >> 8) & 0x00ff00);
        }
    }
}

void KWindow::setFont(const KFont& aFont) {
    mFont = &aFont;
    SelectObject(mCanvas, mFont->font());
}

 */

