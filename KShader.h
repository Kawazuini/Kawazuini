/**
 * @file   KShader.h
 * @brief  KShader
 * @author Maeda Takumi
 */
#ifndef KSHADER_H
#define KSHADER_H

#include "KNonCopy.h"
#include "KUtility.h"

/**
 * @brief  \~english  shader system
 * @brief  \~japanese シェーダシステム
 * @author \~ Maeda Takumi
 */
class KShader final : private KNonCopy {
private:
    /* 最後に適用されたシェーダ番号 */
    static unsigned int sProgram;

    int mVertexSourceLength;
    const char** mVertexSource;
    int mFragmentSourceLength;
    const char** mFragmentSource;

    /* 頂点シェーダ番号         */ unsigned int mVertexShader;
    /* フラグメントシェーダ番号 */ unsigned int mFragmentShader;
    /* シェーダプログラム番号   */ unsigned int mProgram;

    /* コンパイル結果の表示 */
    void compileResult(const unsigned int& aShader);
public:
    /**
     * \~english
     * @param aVertexShader   source code of vertex shader
     * @param aFragmentShader source code of fragment shader
     * \~japanese
     * @param aVertexShader   頂点シェーダのソースコード
     * @param aFragmentShader フラグメントシェーダのソースコード
     */
    KShader(
            const Vector<String> aVertexShader,
            const Vector<String> aFragmentShader
            );
    ~KShader() = default;

    static const unsigned int& Program();

    /**
     * @brief \~english  enable shader.
     * @brief \~japanese シェーダを有効にします。
     */
    void ON();
    /**
     * @brief \~english  disable shader.
     * @brief \~japanese シェーダを無効にします。
     */
    void OFF();

    const unsigned int& program() const;
};

#endif /* KSHADER_H */

