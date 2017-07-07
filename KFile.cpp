/**
 * @file   KFile.cpp
 * @brief  KFile
 * @author Maeda Takumi
 */
#include "KFile.h"

#include "KUtility.h"

const KFile::OpenMode KFile::ADD(std::ios::app);
const KFile::OpenMode KFile::BIN(std::ios::binary);

KFile::KFile(const String& aName) {
    mFileName = aName;
}

void KFile::change(const String& aName) {
    mFileName = aName;
}

Vector<String> KFile::read(const bool& aCommOut) const {
    InPut stream(mFileName);
    Vector<String> txt;

    String str;
    stream >> str;
    while (stream) {
        txt.push_back(str);
        stream >> str;
    }

    if (aCommOut) { // コメントアウト
        bool comment = false;
        Vector<String> tmp, sep;
        for (auto i = txt.begin(), i_e = txt.end(); i != i_e; ++i) {
            if (!comment) {
                sep = split(*i, "//"); // 「[0] // [1]」
                if ((sep = split(sep[0], R"(/\*)")).size() > 1) { // 「[0] /* [1]」
                    if (!sep[0].empty()) tmp.push_back(sep[0]); // 「[0] /*」追加
                    comment = true; // コメント開始
                } else {
                    sep = split(*i, "//"); // 「[0] // [1]」
                    if (!sep[0].empty()) tmp.push_back(sep[0]);
                    if (sep.size() > 1) ++i; // 空白が改行になるので飛ばす
                }
            } else {
                if ((sep = split(*i, R"(\*/)")).size() > 1) { // 「[0] */ [1]」
                    if (!sep[1].empty()) tmp.push_back(sep[1]); // 「/* [1]」追加
                    comment = false; // コメント終了
                }
            }
        }
        return tmp;
    }
    return txt;
}

void KFile::write(const Vector<String>& aTxt) const {
    OutPut stream(mFileName);
    for (String i : aTxt) stream << i << std::endl;
}

void KFile::add(const Vector<String>& aTxt) const {
    OutPut stream(mFileName, ADD);
    for (String i : aTxt) stream << i << std::endl;
}
