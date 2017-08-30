/**
 * @file   KFile.h
 * @brief  KFile
 * @author Maeda Takumi
 */
#ifndef KFILE_H
#define KFILE_H

#include "KUtility.h"

#include "KNonCopy.h"

/** @brief ファイル入出力 */

/**
 * @brief  \~english  File I/O
 * @brief  \~japanese ファイル入出力
 * @author \~ Maeda Takumi
 */
class KFile : private KNonCopy {
    typedef std::ifstream InPut;
    typedef std::ofstream OutPut;
    typedef std::ios::openmode OpenMode;
private:
    /* バイナリモード */ static const OpenMode BIN;
    /* 追加出力       */ static const OpenMode ADD;

    /* ファイル名     */ String mFileName;
public:
    /**
     * \~english
     * @param aName File name (Relative path from program)
     * \~japanese
     * @param aName ファイル名(プログラムからの相対パス)
     */
    KFile(const String& aName);
    virtual ~KFile() = default;

    /**
     * \~english
     * @brief change file name.
     * @param aName new file name
     * \~japanese
     * @brief ファイル名を変更します。
     * @param aName 新しいファイル名
     */
    void change(const String& aName);

    /**
     * \~english
     * @brief  read file.
     * @return file contents per line
     * \~japanese
     * @brief  ファイルを読み込みます。
     * @return 一行ごとのファイル内容
     */
    Vector<String> read() const;
    /**
     * \~english
     * @brief write in file
     * @param aTxt write content per line
     * \~japanese
     * @brief ファイルに書き込みます。
     * @param aTxt 行ごとの書き込み内容
     */
    void write(const Vector<String>& aTxt) const;
    /**
     * \~english
     * @brief add write in file
     * @param aTxt write content per line
     * \~japanese
     * @brief ファイルに書き足します。
     * @param aTxt 行ごとの書き込み内容
     */
    void add(const Vector<String>& aTxt) const;
};

#endif /* KFILE_H */

