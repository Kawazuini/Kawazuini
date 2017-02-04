/**
 * @file KOpenGL.h
 * @author Maeda Takumi
 */
#ifndef KOPENGL_H
#define KOPENGL_H

#include "KNonCopy.h"

class KOpenGL : private KNonCopy {
public:

    /** @brief GL設定構造体 */
    typedef struct {
        bool a;
        bool b;
        bool c;
        bool d;
    } GLConfig;

    KOpenGL(const GLConfig& aConfig);
    virtual ~KOpenGL() = default;
};

#endif /* KOPENGL_H */

