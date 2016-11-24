/**
 * @file KOpenGL.cpp
 * @author Maeda Takumi
 */
#include "KOpenGL.h"

#include "KawazuInclude.h"

KOpenGL::KOpenGL(const GLConfig& aConfig) {
    { // Culling(裏面を表示しない)
        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
}

KOpenGL::~KOpenGL() {
}

