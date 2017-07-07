/**
 * @file   KTexture.cpp
 * @brief  KTexture
 * @author Maeda Takumi
 */
#include "KTexture.h"

#include "KImage.h"
#include "KOpenGL.h"
#include "KRect.h"
#include "KShading.h"

KTexture::KTexture(
        const unsigned int& aSize,
        const bool& aFiltering
        ) :
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

    // 補間方法の選択
    if (aFiltering) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    // 縁の描画方法の選択
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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
    glUniform1i(glGetUniformLocation(KShader::Program(), "uTexture"), 1);
}

void KTexture::bindOFF() const {
    glDisable(GL_TEXTURE_2D);
    glUniform1i(glGetUniformLocation(KShader::Program(), "uTexture"), 0);
}

