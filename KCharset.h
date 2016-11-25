/**
 * @file KCharset.h
 * @author Maeda Takumi
 */
#ifndef KCHARSET_H
#define KCHARSET_H

#include "KUtility.h"

#include "KNonCopy.h"

class KImage;
class KRect;
class KVector;

class KCharset : private KNonCopy {
public:
    const KImage * const mImage;
    const int mSize;

    /**
     * @brief 画像から文字セットを作成
     * @param aImage 文字セット画像
     * @param aSize 文字の大きさ
     */
    KCharset(const KImage& aImage, const int& aSize);
    virtual ~KCharset() = default;

    
    KRect getArea(const char* aChar) const;
    KRect getArea(const String& aStr) const;

    KVector getOffsetIndex(const char* aChar) const;
};

#endif /* KCHARSET_H */

