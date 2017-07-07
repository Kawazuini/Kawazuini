/**
 * @file   KFont.h
 * @brief  KFont
 * @author Maeda Takumi
 */
#ifndef KFONT_H
#define KFONT_H

#include "KNonCopy.h"
#include "KUtility.h"

/**
 * @brief  \~english  Font System
 * @brief  \~japanese フォント
 * @author \~ Maeda Takumi
 */
class KFont final : private KNonCopy {
public:

    /// @brief \~english  font type
    /// @brief \~japanese フォントタイプ

    enum FontType {
        NORMAL = 0x00000000,
        ITALIC = 0x00000001,
        UNDER = 0x00000010,
        STRIKE = 0x00000100,
        BOLD = 0x00001000,
    };
private:
    /* フォント名       */ String mName;
    /* フォントサイズ   */ int mSize;
    /* フォントタイプ   */ FontType mType;

    /* フォント設計     */ LOGFONT mLog;
    /* フォントハンドル */ HFONT mFont;
public:
    KFont(
            const String& aName,
            const int& aSize,
            const FontType& aType = NORMAL
            );
    ~KFont();

    const HFONT& font() const;
};

#endif /* KFONT_H */
