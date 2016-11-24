/**
 * @file KCharset.h
 * @author Maeda Takumi
 */
#ifndef KCHARSET_H
#define KCHARSET_H

#include "KNonCopy.h"

class KImage;

class KCharset : private KNonCopy {
private:
    const KImage* mImage;
    int mSize;
public:
    /**
     * @brief 画像から文字セットを作成
     * @param aImage 文字セット画像
     * @param aSize 文字の大きさ
     */
    KCharset(const KImage& aImage, const int& aSize);
    virtual ~KCharset() = default;
};

#endif /* KCHARSET_H */

