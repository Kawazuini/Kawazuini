/**
 * @file KTexture.cpp
 * @author Maeda Takumi
 */
#include "KTexture.h"
#include "KImage.h"

KTexture::KTexture(const unsigned int& aSize) :
mPixel(new unsigned char[aSize * aSize * 4]),
mName(0) {
}

KTexture::KTexture(const unsigned int& aSize, const KImage& aImage) :
KTexture(aSize) {
    // 配列に写しをとる
    unsigned char* pix = mPixel;
    const color* img = aImage.mPixel;
    for (int i = aSize - 1; i >= 0; --i, pix += 4, ++img) {
        *(pix + 0) = (*img & 0x00ff0000) >> 8 * 2;
        *(pix + 1) = (*img & 0x0000ff00) >> 8 * 1;
        *(pix + 2) = (*img & 0x000000ff) >> 8 * 0;
        *(pix + 3) = (*img & 0xff000000) >> 8 * 3;
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

void KTexture::bindON() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mName);
}

void KTexture::bindOFF() const {
    glDisable(GL_TEXTURE);
}

