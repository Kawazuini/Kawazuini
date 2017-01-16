/**
 * @file   KCharset.h
 * @brief  KCharset
 * @author Maeda Takumi
 */
#ifndef KCHARSET_H
#define KCHARSET_H

#include "KNonCopy.h"
#include "KUtility.h"

class KImage;
class KRect;
class KVector;

/**
 * @brief  \~english  charset by image
 * @brief  \~japanese 画像による文字セット
 * @author \~ Maeda Takumi
 */
class KCharset : private KNonCopy {
private:
    /**
     * \~english
     * @brief  
     * @param  aChar
     * @return 
     * \~japanese
     * @brief  文字(仮名含む)に対応する画像の位置インデックスを返します。
     * @param  aChar 文字ポインタ
     * @return 位置インデックス
     */
    static KVector getOffsetIndex(const char* aChar);
public:
    /**
     * @brief \~english  charset image
     * @brief \~japanese 文字セット画像
     */
    const KImage& mImage;
    /**
     * @brief \~english  charcter size
     * @brief \~japanese 文字サイズ
     */
    const int mSize;

    KCharset(const KImage& aImage, const int& aSize);
    virtual ~KCharset() = default;

    KRect getArea(const char* aChar) const;
    KRect getArea(const String& aStr) const;

    /**
     * \~english
     * @brief  
     * @param  aStr
     * @return 
     * \~japanese
     * @brief  文字列描画に必要な描画幅を返します。
     * @param  aStr 描画文字列
     * @return 描画幅
     */
    int getWidth(const String& aStr) const;
};

#endif /* KCHARSET_H */

