/**
 * @file KFile.h
 * @brief ファイル入出力クラス
 */
#ifndef KFILE_H
#define KFILE_H

#include "KUtility.h"

#include "KNonCopy.h"

/** @brief ファイル入出力 */
class KFile : private KNonCopy {
    typedef std::ifstream InPut;
    typedef std::ofstream OutPut;
    typedef std::ios::openmode OpenMode;
private:
    /** @brief バイナリモード */ static const OpenMode BIN = std::ios::binary;
    /** @brief 追加出力       */ static const OpenMode ADD = std::ios::app;

    /** @brief ファイル名     */ String mFileName;
public:
    /** @param aName ファイル名(プログラムからの相対パス) */
    KFile(const String& aName);
    virtual ~KFile() = default;

    /** @brief ファイル名の変更 */ void change(const String& aName);
    /**
     * @brief ファイルを読み込む
     * @param aCO コメントを外すか
     * @return 一行ごとのファイル内容
     */
    List<String> read(const bool& aCommOut = true) const;
    /** @brief ファイルに書き込む */ void write(const List<String>& aTxt) const;
    /** @brief ファイルに書き足す */ void add(const List<String>& aTxt) const;
};

#endif /* KFILE_H */
