/**
 * @file   KTexture.cpp
 * @brief  KTesture
 * @author Maeda Takumi
 */
#include "KTexture.h"

#include "KImage.h"
#include "KRect.h"

KTexture::KTexture(const unsigned int& aSize) :
mPixel(new byte[aSize * aSize * 4]),
mSize(aSize),
mName(0),
mLevel(0) {
    clearRect(KRect(mSize, mSize));

    glGenTextures(1, const_cast<unsigned int*> (&mName));
    glBindTexture(GL_TEXTURE_2D, mName);
    glTexImage2D(
            GL_TEXTURE_2D, mLevel, GL_RGBA,
            mSize, mSize, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, mPixel
            );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

KTexture::~KTexture() {
    glDeleteTextures(1, const_cast<unsigned int*> (&mName));
    delete[] mPixel;
}

void KTexture::reflect() const {
    glBindTexture(GL_TEXTURE_2D, mName);
    glTexSubImage2D(
            GL_TEXTURE_2D, mLevel,
            0, 0, mSize, mSize,
            GL_RGBA, GL_UNSIGNED_BYTE, mPixel
            );
}

void KTexture::bindON() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mName);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void KTexture::bindOFF() const {
    glDisable(GL_TEXTURE_2D);
}

