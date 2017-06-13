/**
 * @file   KRect.cpp
 * @brief  KRect
 * @author Maeda Takumi
 */
#include "KRect.h"

#include "KMath.h"
#include "KVector.h"

KRect::KRect(const int& ax, const int& ay, const int& aw, const int& ah) {
    x = ax;
    y = ay;
    width = aw;
    height = ah;
}

KRect::KRect(const int& aw, const int& ah)
: KRect(0, 0, aw, ah) {
}

KRect::KRect(const KVector& aVec)
: KRect(aVec.x, aVec.y) {
}

KRect::KRect(const KVector& fromVec, const KVector& toVec)
: KRect(fromVec.x, fromVec.y, toVec.x - fromVec.x, toVec.y - fromVec.y) {
}

KRect::KRect(const RECT& aRec)
: KRect(aRec.left, aRec.top, aRec.right - aRec.left, aRec.bottom - aRec.top) {
}

bool KRect::operator==(const KRect& aRect) const {
    return x == aRect.x && y == aRect.y
            && width == aRect.width && height == aRect.height;
}

bool KRect::operator>(const KRect& aRect) const {
    return width * height > aRect.width * aRect.height;
}

bool KRect::operator<(const KRect& aRect) const {
    return width * height < aRect.width * aRect.height;
}

KRect::operator RECT() const {
    return RECT{x, y, width, height};
}

bool KRect::isColision(const KRect& aRec) const {
    return (x < aRec.x + aRec.width &&
            aRec.x < right() &&
            y < aRec.y + aRec.height &&
            aRec.y < bottom());
}

KRect KRect::intersect(const KRect& aRec) const {
    int sx = Math::max(x, aRec.x);
    int sy = Math::max(y, aRec.y);
    int w = Math::min(x + width, aRec.x + aRec.width) - sx;
    int h = Math::min(y + height, aRec.y + aRec.height) - sy;

    if (w > 0 && h > 0) return KRect(sx, sy, w, h);
    return KRect();
}

bool KRect::isColision(const KVector& aVec) const {
    return (x <= aVec.x && aVec.x <= right() && y <= aVec.y && aVec.y <= bottom());
}

bool KRect::isZero() const {
    return width == 0 || height == 0;
}

int KRect::top() const {
    return y;
}

int KRect::bottom() const {
    return y + height;
}

int KRect::left() const {
    return x;
}

int KRect::right() const {
    return x + width;
}

int KRect::centerX() const {
    return x + width / 2;
}

int KRect::centerY() const {
    return y + height / 2;
}

KVector KRect::begin() const {
    return KVector(x, y);
}

KVector KRect::end() const {
    return KVector(x + width, y + height);
}

KVector KRect::center() const {
    return KVector(centerX(), centerY());
}

