/**
 * @file   KShading.h
 * @brief  KShading
 * @author Maeda Takumi
 */
#ifndef KSHADING_H
#define KSHADING_H

#include "KShader.h"

class KShading {
public:
    static const char* const SHADER_VERTEX[];
    static const char* const SHADER_FRAGMENT_COLOR[];
    static const char* const SHADER_FRAGMENT_TEXTURE[];
    static const char* const SHADER_FRAGMENT_PHONG[];
    static const int CHAR_SIZE;
    static const int VERTEX_SIZE;

    static KShader* ColorShading;
    static KShader* TextureShading;
    static KShader* PhongShading;

    KShading();
    virtual ~KShading();
};

#endif /* KSHADING_H */

