/**
 * @file KOpenGL.cpp
 * @author Maeda Takumi
 */
#include "KOpenGL.h"

#include "KawazuInclude.h"

KOpenGL::KOpenGL(const GLConfig& aConfig) {
    { // 陰面消去
        glEnable(GL_DEPTH_TEST);
    }

    { // 透過使用
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        { // アンチエイリアス
            glEnable(GL_POINT_SMOOTH);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_POLYGON_SMOOTH);
        }
    }

    { // Culling(裏面を表示しない)
        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
}

