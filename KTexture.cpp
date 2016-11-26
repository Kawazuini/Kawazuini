/**
 * @file   KTexture.cpp
 * @brief  KTesture
 * @author Maeda Takumi
 */
#include "KTexture.h"

#include "KImage.h"

KTexture::KTexture(const unsigned int& aSize) :
mPixel(new unsigned char[aSize * aSize * 4]),
mSize(aSize),
mName(0) {
    unsigned char* pix = mPixel;
    for (int i = mSize * mSize * 4 - 1; i >= 0; --i, ++pix) {
        *pix = 0;
    }

    glGenTextures(1, const_cast<unsigned int*> (&mName));
    glBindTexture(GL_TEXTURE_2D, mName);
    glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA,
            aSize, aSize, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, mPixel
            );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

KTexture::~KTexture() {
    glDeleteTextures(1, const_cast<unsigned int*> (&mName));
}

void KTexture::update() {
    glBindTexture(GL_TEXTURE_2D, mName);
    glTexSubImage2D(
            GL_TEXTURE_2D, 0,
            0, 0, mSize, mSize,
            GL_RGBA, GL_UNSIGNED_BYTE, mPixel
            );
}

void KTexture::bindON() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mName);
}

void KTexture::bindOFF() const {
    glDisable(GL_TEXTURE_2D);
}

