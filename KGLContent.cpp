/**
 * @file   KGLContent.cpp
 * @brief  KGLContent
 * @author Maeda Takumi
 */
#include "KGLContent.h"

#include "KVector.h"

KGLContent::KGLContent(const KRect& aArea) :
mParent(NULL),
mArea(aArea),
mActive(false),
mUpdated(true),
mFrontColor(0x00000000),
mBackColor(0x00000000) {
}

void KGLContent::setParent(const KGLContent* aContent) {
    mParent = aContent;
    mArea = mArea.slide(aContent->mArea.begin());
}

const bool& KGLContent::isActive() const {
    return mActive;
}

const bool& KGLContent::isUpdated() const {
    return mUpdated;
}

void KGLContent::setFrontColor(const color& aColor) {
    mUpdated = true;
    mFrontColor = aColor;
}

void KGLContent::setBackColor(const color& aColor) {
    mUpdated = true;
    mBackColor = aColor;
}

const color& KGLContent::frontColor() const {
    return mFrontColor;
}

const color& KGLContent::backColor() const {
    return mBackColor;
}

void KGLContent::slide(const KVector& aSlide) {
    mUpdated = true;
    mArea = mArea.slide(aSlide);
}

const KRect& KGLContent::area() const {
    return mArea;
}

