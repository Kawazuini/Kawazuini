/**
 * @file KOpenGL.h
 * @author Maeda Takumi
 */
#ifndef KOPENGL_H
#define KOPENGL_H

#include "KawazuInclude.h"
#include "KNonCopy.h"

class KWindow;

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

class KOpenGL : private KNonCopy {
private:
    /* ピクセルフォーマット */ PIXELFORMATDESCRIPTOR mPixelFormat;
    /* OpenGLコンテキスト   */ HGLRC mGLRC;
public:
    static const char* SHADER_VERTEX[];
    static const char* SHADER_FRAGMENT[];

    KOpenGL(const KWindow& aWindow);
    virtual ~KOpenGL();
};

#endif /* KOPENGL_H */

