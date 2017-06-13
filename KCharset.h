/**
 * @file   KCharset.h
 * @brief  KCharset
 * @author Maeda Takumi
 */
#ifndef KCHARSET_H
#define KCHARSET_H

#include "KNonCopy.h"
#include "KUtility.h"
#include "KVector.h"

class KImage;
class KRect;

/**
 * @brief  \~english  charset by image
 * @brief  \~japanese 画像による文字セット
 * @author \~ Maeda Takumi
 */
class KCharset final : private KNonCopy {
private:
    /* 文字セット */ static const List<String> CHARSET;
    /* 文字に対応する画像の位置インデックス */
    HashMap<unsigned long, KVector> mCharMap;
    /* 文字に対応する画像の位置インデックスを返します。 */
    KVector getOffsetIndex(const char* aChar) const;
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

    /**
     * \~english
     * @param aImage image of charcter set
     * @param aSize  size of a character
     * \~japanese
     * @param aImage 文字セットの画像
     * @param aSize  1文字のサイズ
     */
    KCharset(const KImage& aImage, const int& aSize);
    ~KCharset() = default;

    /**
     * \~english
     * @brief  get image area for drawing character.
     * @param  aChar drawing character
     * @return image arae.
     * \~japanese
     * @brief  文字描画に使用する画像領域を返します。
     * @param  aChar 描画文字
     * @return 画像領域
     */
    KRect getArea(const char* aChar) const;

    /**
     * \~english
     * @brief  get drawing width required for drawing the character string.
     * @param  aStr drawing string
     * @return drawing width
     * \~japanese
     * @brief  文字列描画に必要な描画幅を取得します。
     * @param  aStr 描画文字列
     * @return 描画幅
     */
    int getWidth(const String& aStr) const;

    /**
     * \~english
     * @brief  get whether character string can be drawed.
     * @param  aStr check string
     * @return whether drawing
     * \~japanese
     * @brief  文字列が描画可能かを取得します。
     * @param  aStr 確認文字列
     * @return 描画可能か
     */
    bool getDrawable(const String& aStr) const;
};

#endif /* KCHARSET_H */

