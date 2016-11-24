/**
 * @file KTexture.h
 * @author Maeda Takumi
 */
#ifndef KTEXTURE_H
#define KTEXTURE_H

#include "KNonCopy.h"

class KImage;

class KTexture : private KNonCopy {
private:
    unsigned char * const mPixel;

    const unsigned int mName;
public:
    KTexture(const unsigned int& aSize);
    KTexture(const unsigned int& aSize, const KImage& aImage);
    virtual ~KTexture();

    void bindON() const;
    void bindOFF() const;
};

#endif /* KTEXTURE_H */

