/**
 * @file   KShading.h
 * @brief  KShading
 * @author Maeda Takumi
 */
#ifndef KSHADING_H
#define KSHADING_H

#include "KShader.h"

class KShading final : private KNonCopy {
private:
    /* フラグメントシェーダのソースコード */
    /* 色そのまま           */ static const Vector<String> SHADER_FRAGMENT_COLOR;
    /* フォンシェーディング */ static const Vector<String> SHADER_FRAGMENT_PHONG;
public:
    /// @brief \~english  source code of vertex shader
    /// @brief \~japanese 頂点シェーダのソースコード
    static const Vector<String> SHADER_VERTEX;
    /// @brief \~english  color intact
    /// @brief \~japanese 色そのまま
    static KShader* ColorShading;
    /// @brief \~english  phong shading
    /// @brief \~japanese フォンシェーディング
    static KShader* PhongShading;

    KShading();
    virtual ~KShading();
};

#endif /* KSHADING_H */

