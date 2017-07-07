/**
 * @file   KFont.cpp
 * @brief  KFont
 * @author Maeda Takumi
 */
#include "KFont.h"

KFont::KFont(
        const String& aName,
        const int& aSize,
        const FontType& aType
        ) :
mName(aName),
mSize(aSize),
mType(aType),
mLog{
    /* 論理フォントの高さ                          */ mSize,
    /* 論理フォントのキャラクタの平均幅            */ 0,
    /* 水平軸から反時計回りの角度(1/10度単位)      */ 0,
    /* 各文字のベースラインのx軸の角度(1/10度単位) */ 0,
    /* フォントの太さ                              */ mType & BOLD ? FW_BOLD : FW_MEDIUM,
    /* 斜体                                        */ (unsigned char) (mType & ITALIC),
    /* 下線の有無                                  */ (unsigned char) (mType & UNDER),
    /* 打消し線の有無                              */ (unsigned char) (mType & STRIKE),
    /* フォントのキャラクタセット                  */ DEFAULT_CHARSET,
    /* 物理フォント検索方法                        */ OUT_DEFAULT_PRECIS,
    /* 領域からはみ出した文字の処理方法            */ CLIP_DEFAULT_PRECIS,
    /* 論理と物理の一致の程度                      */ DEFAULT_QUALITY,
    /* フォントのピッチとファミリ                  */ FF_SWISS | DEFAULT_PITCH,
}

,
mFont(NULL) {
    stringCopy(mLog.lfFaceName, W(mName).data(), LF_FACESIZE);
    mFont = CreateFontIndirect(&mLog);
}

KFont::~KFont() {
    if (mFont) DeleteObject(mFont);
}

const HFONT& KFont::font() const {
    return mFont;
}
