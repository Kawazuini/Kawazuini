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

Vector<String> KFile::read() const {
    InPut stream(mFileName);
    Vector<String> txt;

    String content;
    while (std::getline(stream, content)) txt.push_back(content);
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
