/**
 * @file   KShader.h
 * @brief  KShader
 * @author Maeda Takumi
 */
#ifndef KSHADER_H
#define KSHADER_H

/**
 * @brief  \~english  shader system
 * @brief  \~japanese シェーダシステム
 * @author \~ Maeda Takumi
 */
class KShader {
private:
    /* 頂点シェーダ番号         */ unsigned int mVertexShader;
    /* フラグメントシェーダ番号 */ unsigned int mFragmentShader;
    /* シェーダプログラム番号   */ unsigned int mProgram;

    /* コンパイル結果の表示 */
    void compileResult(const unsigned int& aShader);
public:
    /**
     * \~english
     * @param aVertexShaderLength   source code length of vertex shader
     * @param aVertexShader         source code of vertex shader
     * @param aFragmentShaderLength source code length of fragment shader
     * @param aFragmentShader       source code of fragment shader
     * \~japanese
     * @param aVertexShaderLength   頂点シェーダのソースコードの長さ
     * @param aVertexShader         頂点シェーダのソースコード
     * @param aFragmentShaderLength フラグメントシェーダのソースコードの長さ
     * @param aFragmentShader       フラグメントシェーダのソースコード
     */
    KShader(
            int aVertexShaderLength,
            const char* const* aVertexShader,
            int aFragmentShaderLength,
            const char* const* aFragmentShader
            );
    virtual ~KShader() = default;

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

    /**
     * \~english
     * @brief  get program number.
     * @return program number
     * \~japanese
     * @brief  プログラム番号を取得します。
     * @return プログラム番号
     */
    const unsigned int& program() const;
};

#endif /* KSHADER_H */

