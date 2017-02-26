/**
 * @file   KShader.cpp
 * @brief  KShader
 * @author Maeda Takumi
 */
#ifndef KSHADER_H
#define KSHADER_H

class KShader {
private:
    unsigned int mVertexShader;
    unsigned int mFragmentShader;
    unsigned int mProgram;
    
    void compileResult(const unsigned int& aShader);
public:
    KShader(
            int aVertexShaderLength,
            const char* const* aVertexShader,
            int aFragmentShaderLength,
            const char* const* aFragmentShader
            );
    virtual ~KShader() = default;

    void ON();
    void OFF();

    const unsigned int& program() const;
};

#endif /* KSHADER_H */

