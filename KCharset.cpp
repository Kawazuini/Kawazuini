/**
 * @file   KCharset.cpp
 * @brief  KCharset
 * @author Maeda Takumi
 */
#include "KCharset.h"

#include "KRect.h"
#include "KVector.h"

KCharset::KCharset(const KImage& aImage, const int& aSize) :
mImage(aImage),
mSize(aSize) {
}

KVector KCharset::getOffsetIndex(const char* aChar) {
    switch (*aChar) {
        case ' ': return KVector(0, 0);
        case '!': return KVector(1, 0);
        case '"': return KVector(2, 0);
        case '#': return KVector(3, 0);
        case '$': return KVector(4, 0);
        case '%': return KVector(5, 0);
        case '&': return KVector(6, 0);
        case '\'': return KVector(7, 0);
        case '(': return KVector(8, 0);
        case ')': return KVector(9, 0);
        case '*': return KVector(10, 0);
        case '+': return KVector(11, 0);
        case ',': return KVector(12, 0);
        case '-': return KVector(13, 0);
        case '.': return KVector(14, 0);
        case '/': return KVector(15, 0);
        case '0': return KVector(0, 1);
        case '1': return KVector(1, 1);
        case '2': return KVector(2, 1);
        case '3': return KVector(3, 1);
        case '4': return KVector(4, 1);
        case '5': return KVector(5, 1);
        case '6': return KVector(6, 1);
        case '7': return KVector(7, 1);
        case '8': return KVector(8, 1);
        case '9': return KVector(9, 1);
        case ':': return KVector(10, 1);
        case ';': return KVector(11, 1);
        case '<': return KVector(12, 1);
        case '=': return KVector(13, 1);
        case '>': return KVector(14, 1);
        case '?': return KVector(15, 1);
        case '@': return KVector(0, 2);
        case 'A': return KVector(1, 2);
        case 'B': return KVector(2, 2);
        case 'C': return KVector(3, 2);
        case 'D': return KVector(4, 2);
        case 'E': return KVector(5, 2);
        case 'F': return KVector(6, 2);
        case 'G': return KVector(7, 2);
        case 'H': return KVector(8, 2);
        case 'I': return KVector(9, 2);
        case 'J': return KVector(10, 2);
        case 'K': return KVector(11, 2);
        case 'L': return KVector(12, 2);
        case 'M': return KVector(13, 2);
        case 'N': return KVector(14, 2);
        case 'O': return KVector(15, 2);
        case 'P': return KVector(0, 3);
        case 'Q': return KVector(1, 3);
        case 'R': return KVector(2, 3);
        case 'S': return KVector(3, 3);
        case 'T': return KVector(4, 3);
        case 'U': return KVector(5, 3);
        case 'V': return KVector(6, 3);
        case 'W': return KVector(7, 3);
        case 'X': return KVector(8, 3);
        case 'Y': return KVector(9, 3);
        case 'Z': return KVector(10, 3);
        case '[': return KVector(11, 3);
        case '\\': return KVector(12, 3);
        case ']': return KVector(13, 3);
        case '^': return KVector(14, 3);
        case '_': return KVector(15, 3);
        case '`': return KVector(0, 4);
        case 'a': return KVector(1, 4);
        case 'b': return KVector(2, 4);
        case 'c': return KVector(3, 4);
        case 'd': return KVector(4, 4);
        case 'e': return KVector(5, 4);
        case 'f': return KVector(6, 4);
        case 'g': return KVector(7, 4);
        case 'h': return KVector(8, 4);
        case 'i': return KVector(9, 4);
        case 'j': return KVector(10, 4);
        case 'k': return KVector(11, 4);
        case 'l': return KVector(12, 4);
        case 'm': return KVector(13, 4);
        case 'n': return KVector(14, 4);
        case 'o': return KVector(15, 4);
        case 'p': return KVector(0, 5);
        case 'q': return KVector(1, 5);
        case 'r': return KVector(2, 5);
        case 's': return KVector(3, 5);
        case 't': return KVector(4, 5);
        case 'u': return KVector(5, 5);
        case 'v': return KVector(6, 5);
        case 'w': return KVector(7, 5);
        case 'x': return KVector(8, 5);
        case 'y': return KVector(9, 5);
        case 'z': return KVector(10, 5);
        case '{': return KVector(11, 5);
        case '|': return KVector(12, 5);
        case '}': return KVector(13, 5);
        case '~': return KVector(14, 5);
    }
    // 3文字分の文字コードをくっつける
    unsigned long chhh(((*(aChar + 0) & 0xff) << 16) | ((*(aChar + 1) & 0xff) << 8) | ((*(aChar + 2) & 0xff) << 0));
    switch (chhh) {
        case 'あ': return KVector(0, 6);
        case 'い': return KVector(1, 6);
        case 'う': return KVector(2, 6);
        case 'え': return KVector(3, 6);
        case 'お': return KVector(4, 6);
        case 'か': return KVector(5, 6);
        case 'き': return KVector(6, 6);
        case 'く': return KVector(7, 6);
        case 'け': return KVector(8, 6);
        case 'こ': return KVector(9, 6);
        case 'さ': return KVector(0, 7);
        case 'し': return KVector(1, 7);
        case 'す': return KVector(2, 7);
        case 'せ': return KVector(3, 7);
        case 'そ': return KVector(4, 7);
        case 'た': return KVector(5, 7);
        case 'ち': return KVector(6, 7);
        case 'つ': return KVector(7, 7);
        case 'て': return KVector(8, 7);
        case 'と': return KVector(9, 7);
        case 'な': return KVector(0, 8);
        case 'に': return KVector(1, 8);
        case 'ぬ': return KVector(2, 8);
        case 'ね': return KVector(3, 8);
        case 'の': return KVector(4, 8);
        case 'は': return KVector(5, 8);
        case 'ひ': return KVector(6, 8);
        case 'ふ': return KVector(7, 8);
        case 'へ': return KVector(8, 8);
        case 'ほ': return KVector(9, 8);
        case 'ま': return KVector(0, 9);
        case 'み': return KVector(1, 9);
        case 'む': return KVector(2, 9);
        case 'め': return KVector(3, 9);
        case 'も': return KVector(4, 9);
        case 'や': return KVector(5, 9);
        case '、': return KVector(6, 9);
        case 'ゆ': return KVector(7, 9);
        case '。': return KVector(8, 9);
        case 'よ': return KVector(9, 9);
        case 'ら': return KVector(0, 10);
        case 'り': return KVector(1, 10);
        case 'る': return KVector(2, 10);
        case 'れ': return KVector(3, 10);
        case 'ろ': return KVector(4, 10);
        case 'わ': return KVector(5, 10);
        case 'ゐ': return KVector(6, 10);
        case 'を': return KVector(7, 10);
        case 'ゑ': return KVector(8, 10);
        case 'ん': return KVector(9, 10);
        case 'が': return KVector(0, 11);
        case 'ぎ': return KVector(1, 11);
        case 'ぐ': return KVector(2, 11);
        case 'げ': return KVector(3, 11);
        case 'ご': return KVector(4, 11);
        case 'ざ': return KVector(5, 11);
        case 'じ': return KVector(6, 11);
        case 'ず': return KVector(7, 11);
        case 'ぜ': return KVector(8, 11);
        case 'ぞ': return KVector(9, 11);
        case 'だ': return KVector(0, 12);
        case 'ぢ': return KVector(1, 12);
        case 'づ': return KVector(2, 12);
        case 'で': return KVector(3, 12);
        case 'ど': return KVector(4, 12);
        case 'ば': return KVector(5, 12);
        case 'び': return KVector(6, 12);
        case 'ぶ': return KVector(7, 12);
        case 'べ': return KVector(8, 12);
        case 'ぼ': return KVector(9, 12);
        case 'ぱ': return KVector(0, 13);
        case 'ぴ': return KVector(1, 13);
        case 'ぷ': return KVector(2, 13);
        case 'ぺ': return KVector(3, 13);
        case 'ぽ': return KVector(4, 13);
        case 'っ': return KVector(5, 13);
        case 'ゃ': return KVector(6, 13);
        case 'ゅ': return KVector(7, 13);
        case 'ょ': return KVector(8, 13);
        case '　': return KVector(9, 13);
        case 'ア': return KVector(0, 14);
        case 'イ': return KVector(1, 14);
        case 'ウ': return KVector(2, 14);
        case 'エ': return KVector(3, 14);
        case 'オ': return KVector(4, 14);
        case 'カ': return KVector(5, 14);
        case 'キ': return KVector(6, 14);
        case 'ク': return KVector(7, 14);
        case 'ケ': return KVector(8, 14);
        case 'コ': return KVector(9, 14);
        case 'サ': return KVector(0, 15);
        case 'シ': return KVector(1, 15);
        case 'ス': return KVector(2, 15);
        case 'セ': return KVector(3, 15);
        case 'ソ': return KVector(4, 15);
        case 'タ': return KVector(5, 15);
        case 'チ': return KVector(6, 15);
        case 'ツ': return KVector(7, 15);
        case 'テ': return KVector(8, 15);
        case 'ト': return KVector(9, 15);
        case 'ナ': return KVector(0, 16);
        case 'ニ': return KVector(1, 16);
        case 'ヌ': return KVector(2, 16);
        case 'ネ': return KVector(3, 16);
        case 'ノ': return KVector(4, 16);
        case 'ハ': return KVector(5, 16);
        case 'ヒ': return KVector(6, 16);
        case 'フ': return KVector(7, 16);
        case 'ヘ': return KVector(8, 16);
        case 'ホ': return KVector(9, 16);
        case 'マ': return KVector(0, 17);
        case 'ミ': return KVector(1, 17);
        case 'ム': return KVector(2, 17);
        case 'メ': return KVector(3, 17);
        case 'モ': return KVector(4, 17);
        case 'ヤ': return KVector(5, 17);
        case 'ユ': return KVector(7, 17);
        case 'ヨ': return KVector(9, 17);
        case 'ラ': return KVector(0, 18);
        case 'リ': return KVector(1, 18);
        case 'ル': return KVector(2, 18);
        case 'レ': return KVector(3, 18);
        case 'ロ': return KVector(4, 18);
        case 'ワ': return KVector(5, 18);
        case 'ヲ': return KVector(7, 18);
        case 'ン': return KVector(9, 18);
        case 'ガ': return KVector(0, 19);
        case 'ギ': return KVector(1, 19);
        case 'グ': return KVector(2, 19);
        case 'ゲ': return KVector(3, 19);
        case 'ゴ': return KVector(4, 19);
        case 'ザ': return KVector(5, 19);
        case 'ジ': return KVector(6, 19);
        case 'ズ': return KVector(7, 19);
        case 'ゼ': return KVector(8, 19);
        case 'ゾ': return KVector(9, 19);
        case 'ダ': return KVector(0, 20);
        case 'ヂ': return KVector(1, 20);
        case 'ヅ': return KVector(2, 20);
        case 'デ': return KVector(3, 20);
        case 'ド': return KVector(4, 20);
        case 'バ': return KVector(5, 20);
        case 'ビ': return KVector(6, 20);
        case 'ブ': return KVector(7, 20);
        case 'ベ': return KVector(8, 20);
        case 'ボ': return KVector(9, 20);
        case 'パ': return KVector(0, 21);
        case 'ピ': return KVector(1, 21);
        case 'プ': return KVector(2, 21);
        case 'ペ': return KVector(3, 21);
        case 'ポ': return KVector(4, 21);
        case 'ッ': return KVector(5, 21);
        case 'ャ': return KVector(6, 21);
        case 'ュ': return KVector(7, 21);
        case 'ョ': return KVector(8, 21);
        case 'ー': return KVector(9, 21);
        case 'ァ': return KVector(0, 22);
        case 'ィ': return KVector(1, 22);
        case 'ゥ': return KVector(2, 22);
        case 'ェ': return KVector(3, 22);
        case 'ォ': return KVector(4, 22);
    }
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

