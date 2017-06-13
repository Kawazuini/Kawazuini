/**
 * @file   KShader.cpp
 * @brief  KShader
 * @author Maeda Takumi
 */
#include "KShader.h"

#include "KOpenGL.h"
#include "KWindows.h"

KShader::KShader(
        int aVertexShaderLength,
        const char* const* aVertexShader,
        int aFragmentShaderLength,
        const char* const* aFragmentShader
        ) :
mVertexShader(glCreateShader(GL_VERTEX_SHADER)),
mFragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
mProgram(glCreateProgram()) {
    int result;

    glShaderSource(mVertexShader, aVertexShaderLength, aVertexShader, NULL);
    glShaderSource(mFragmentShader, aFragmentShaderLength, aFragmentShader, NULL);

    // バーテックスシェーダのコンパイル
    glCompileShader(mVertexShader);
    compileResult(mVertexShader);
    glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        message(_T("Compile error in vertex shader"), _T("初期化に失敗しました。"));
        exit(1);
    }
    // フラグメントシェーダのコンパイル
    glCompileShader(mFragmentShader);
    compileResult(mFragmentShader);
    glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        message(_T("Compile error in fragment shader"), _T("初期化に失敗しました"));
        exit(1);
    }

    // シェーダをプログラムへ登録
    glAttachShader(mProgram, mVertexShader);
    glAttachShader(mProgram, mFragmentShader);

    // シェーダオブジェクトの削除
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);

    // シェーダプログラムのリンク
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &result);
    if (!result) {
        message(_T("Link error in shader"), _T("初期化に失敗しました"));
        exit(1);
    }
}

void KShader::compileResult(const unsigned int& aShader) {
    int bufSize;

    glGetShaderiv(aShader, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1) {
        char* infoLog(new char[bufSize]);

        int length;
        glGetShaderInfoLog(aShader, bufSize, &length, infoLog);
        // fprintf(stderr, "InfoLog:\n%s\n\n", infoLog);
        println(*infoLog);
        delete[] infoLog;
    }
}

void KShader::ON() {
    glUseProgram(mProgram);
}

void KShader::OFF() {
    glUseProgram(0);
}

const unsigned int& KShader::program() const {
    return mProgram;
}

