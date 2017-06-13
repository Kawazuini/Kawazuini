/**
 * @file   KGLContent.cpp
 * @brief  KGLContetn
 * @author Maeda Takumi
 */
#include "KGLContent.h"

KGLContent::KGLContent(const KRect& aArea) :
mArea(aArea),
mActive(false),
mUpdated(true),
mFrontColor(0x00000000),
mBackColor(0x00000000) {
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

