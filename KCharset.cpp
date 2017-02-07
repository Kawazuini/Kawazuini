/**
 * @file   KCharset.cpp
 * @brief  KCharset
 * @author Maeda Takumi
 */
#include "KCharset.h"

#include "KRect.h"

const List<String> KCharset::CHARSET
{
    " ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?",
    "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\", "]", "^", "_",
    "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
    "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~", "",
    "あ", "い", "う", "え", "お", "か", "き", "く", "け", "こ", "", "", "", "", "", "",
    "さ", "し", "す", "せ", "そ", "た", "ち", "つ", "て", "と", "", "", "", "", "", "",
    "な", "に", "ぬ", "ね", "の", "は", "ひ", "ふ", "へ", "ほ", "", "", "", "", "", "",
    "ま", "み", "む", "め", "も", "や", "、", "ゆ", "。", "よ", "", "", "", "", "", "",
    "ら", "り", "る", "れ", "ろ", "わ", "ゐ", "を", "ゑ", "ん", "", "", "", "", "", "",
    "が", "ぎ", "ぐ", "げ", "ご", "ざ", "じ", "ず", "ぜ", "ぞ", "", "", "", "", "", "",
    "だ", "ぢ", "づ", "で", "ど", "ば", "び", "ぶ", "べ", "ぼ", "", "", "", "", "", "",
    "ぱ", "ぴ", "ぷ", "ぺ", "ぽ", "っ", "ゃ", "ゅ", "ょ", "　", "", "", "", "", "", "",
    "ア", "イ", "ウ", "エ", "オ", "カ", "キ", "ク", "ケ", "コ", "", "", "", "", "", "",
    "サ", "シ", "ス", "セ", "ソ", "タ", "チ", "ツ", "テ", "ト", "", "", "", "", "", "",
    "ナ", "ニ", "ヌ", "ネ", "ノ", "ハ", "ヒ", "フ", "ヘ", "ホ", "", "", "", "", "", "",
    "マ", "ミ", "ム", "メ", "モ", "ヤ", "　", "ユ", "　", "ヨ", "", "", "", "", "", "",
    "ラ", "リ", "ル", "レ", "ロ", "ワ", "　", "ヲ", "　", "ン", "", "", "", "", "", "",
    "ガ", "ギ", "グ", "ゲ", "ゴ", "ザ", "ジ", "ズ", "ゼ", "ゾ", "", "", "", "", "", "",
    "ダ", "ヂ", "ヅ", "デ", "ド", "バ", "ビ", "ブ", "ベ", "ボ", "", "", "", "", "", "",
    "パ", "ピ", "プ", "ペ", "ポ", "ッ", "ャ", "ュ", "ョ", "ー", "", "", "", "", "", "",
    "ァ", "ィ", "ゥ", "ェ", "ォ", "操", "作", "説", "明", "前", "", "", "", "", "", "",
    "進", "後", "退", "左", "右", "選", "択", "画", "面", "視", "", "", "", "", "", "",
    "点", "移", "動", "決", "定", "攻", "撃", "武", "器", "構", "", "", "", "", "", "",
    "確", "認", "解", "除", "中", "断", "再", "開", "読", "切", "", "", "", "", "", "",
};

KCharset::KCharset(const KImage& aImage, const int& aSize) :
mImage(aImage),
mSize(aSize) {
    int count(0);
    for (String i : CHARSET) {
        const char* ch(i.data());
        if (*ch < 0) { // 全角文字(char文字を3つ繋げる)
            unsigned long chhh(((*(ch + 0) & 0xff) << 16) | ((*(ch + 1) & 0xff) << 8) | ((*(ch + 2) & 0xff) << 0));
            mCharMap[chhh] = KVector(count % 16, count / 16);
        } else {
            if (*ch != 0) mCharMap[*ch] = KVector(count % 16, count / 16);
        }
        count++;
    }
}

KVector KCharset::getOffsetIndex(const char* aChar) const {
    if (*aChar < 0) { // 全角文字(char文字を3つ繋げる)
        unsigned long chhh(((*(aChar + 0) & 0xff) << 16) | ((*(aChar + 1) & 0xff) << 8) | ((*(aChar + 2) & 0xff) << 0));
        return mCharMap.at(chhh);
    } else {
        return mCharMap.at(*aChar);
    }
    return KVector();
}

KRect KCharset::getArea(const char* aChar) const {
    KVector index = getOffsetIndex(aChar);
    KVector offset = index * mSize;
    int kana = index.y > 5 ? 2 : 1; // 仮名の時横幅2倍
    return KRect(offset.x * kana, offset.y * 2, mSize * kana, mSize * 2);
}

KRect KCharset::getArea(const String& aStr) const {
    return getArea(aStr.data());
}

int KCharset::getWidth(const String& aStr) const {
    const char* txt = aStr.data();
    int width = 0;
    for (int i = 0, i_e = aStr.size(); i < i_e; ++i) {
        KRect area = getArea(txt + i);
        width += area.width;
        if (area.width > mSize) i += 2;
    }
    return width;
}

