/**
 * @file   KOpenGL.h
 * @brief  KOpenGL
 * @author Maeda Takumi
 */
#ifndef KOPENGL_H
#define KOPENGL_H

#include "KawazuInclude.h"

#include "KNonCopy.h"

class KWindow;

/* OpenGL関数群 */
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

/**
 * @brief  \~english  Enable OpenGL
 * @brief  \~japanese OpenGLの有効化
 * @author \~ Maeda Takumi
 */
class KOpenGL : private KNonCopy {
private:
    /* ピクセルフォーマット */ PIXELFORMATDESCRIPTOR mPixelFormat;
    /* OpenGLコンテキスト   */ HGLRC mGLRC;
public:
    /**
     * @param \~english  aWindow Enable Window
     * @param \~japanese aWindow 有効にするウィンドウ
     */
    KOpenGL(const KWindow& aWindow);
    virtual ~KOpenGL();
};

#endif /* KOPENGL_H */

