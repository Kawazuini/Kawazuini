/**
 * @file   KShader.cpp
 * @brief  KShader
 * @author Maeda Takumi
 */
#include "KShader.h"

#include "KOpenGL.h"
#include "KWindows.h"

unsigned int KShader::sProgram;

KShader::KShader(
        const Vector<String> aVertexShader,
        const Vector<String> aFragmentShader) :
mVertexSourceLength(aVertexShader.size()),
mVertexSource(new const char*[mVertexSourceLength]),
mFragmentSourceLength(aFragmentShader.size()),
mFragmentSource(new const char*[mFragmentSourceLength]),
mVertexShader(glCreateShader(GL_VERTEX_SHADER)),
mFragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
mProgram(glCreateProgram()) {
    for (int i = 0; i < mVertexSourceLength; ++i) mVertexSource[i] = aVertexShader[i].data();
    for (int i = 0; i < mFragmentSourceLength; ++i) mFragmentSource[i] = aFragmentShader[i].data();

    int result;

    glShaderSource(mVertexShader, mVertexSourceLength, mVertexSource, nullptr);
    glShaderSource(mFragmentShader, mFragmentSourceLength, mFragmentSource, nullptr);

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

const unsigned int& KShader::Program() {
    return sProgram;
}

void KShader::compileResult(const unsigned int& aShader) {
    int bufSize;

    glGetShaderiv(aShader, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1) {
        char* infoLog(new char[bufSize]);

        int length;
        glGetShaderInfoLog(aShader, bufSize, &length, infoLog);
        println(infoLog);
        delete[] infoLog;
    }
}

void KShader::ON() {
    sProgram = mProgram;
    glUseProgram(mProgram);
}

void KShader::OFF() {
    glUseProgram(0);
}

const unsigned int& KShader::program() const {
    return mProgram;
}

