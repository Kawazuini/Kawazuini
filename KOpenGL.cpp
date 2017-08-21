/**
 * @file   KOpenGL.cpp
 * @brief  KOpenGL
 * @author Maeda Takumi
 */
#include "KOpenGL.h"

#include "KWindow.h"

PFNGLCREATESHADERPROC glCreateShader(nullptr);
PFNGLSHADERSOURCEPROC glShaderSource(nullptr);
PFNGLCOMPILESHADERPROC glCompileShader(nullptr);
PFNGLGETSHADERIVPROC glGetShaderiv(nullptr);
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog(nullptr);
PFNGLCREATEPROGRAMPROC glCreateProgram(nullptr);
PFNGLATTACHSHADERPROC glAttachShader(nullptr);
PFNGLDELETESHADERPROC glDeleteShader(nullptr);
PFNGLLINKPROGRAMPROC glLinkProgram(nullptr);
PFNGLGETPROGRAMIVPROC glGetProgramiv(nullptr);
PFNGLUSEPROGRAMPROC glUseProgram(nullptr);
PFNGLUNIFORM1IPROC glUniform1i(nullptr);
PFNGLUNIFORM1FPROC glUniform1f(nullptr);
PFNGLUNIFORM2FPROC glUniform2f(nullptr);
PFNGLUNIFORM2FVPROC glUniform2fv(nullptr);
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation(nullptr);
PFNGLGENBUFFERSPROC glGenBuffers(nullptr);
PFNGLBINDBUFFERPROC glBindBuffer(nullptr);
PFNGLBUFFERDATAPROC glBufferData(nullptr);
PFNGLDELETEBUFFERSPROC glDeleteBuffers(nullptr);
PFNGLMAPBUFFERPROC glMapBuffer(nullptr);
PFNGLUNMAPBUFFERPROC glUnmapBuffer(nullptr);

KOpenGL::KOpenGL(const KWindow& aWindow) :
mPixelFormat({
    sizeof (PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32, // color
    0, 0, // R
    0, 0, // G
    0, 0, // B
    0, 0, // A
    0, 0, 0, 0, 0, // AC R G B A
    24, // depth
    8, // stencil
    0, // aux
    0, // layertype
    0, // reserved
    0, // layermask
    0, // visiblemask
    0 // damagemask
}) {
    // ピクセルフォーマットの選択
    HDC hdc(GetDC(aWindow.mWindow));
    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &mPixelFormat), &mPixelFormat);
    mGLRC = wglCreateContext(hdc); // OpenGL コンテキストの作成
    wglMakeCurrent(hdc, mGLRC);
    ReleaseDC(aWindow.mWindow, hdc);

    // OpenGL関数の初期化
    glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
    glDeleteShader = (PFNGLDELETESHADERPROC) wglGetProcAddress("glDeleteShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");
    glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
    glUniform1i = (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
    glUniform1f = (PFNGLUNIFORM1FPROC) wglGetProcAddress("glUniform1f");
    glUniform2f = (PFNGLUNIFORM2FPROC) wglGetProcAddress("glUniform2f");
    glUniform2fv = (PFNGLUNIFORM2FVPROC) wglGetProcAddress("glUniform2fv");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
    glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffers");
    glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");
    glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferData");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffers");
    glMapBuffer = (PFNGLMAPBUFFERPROC) wglGetProcAddress("glMapBuffer");
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) wglGetProcAddress("glUnmapBuffer");

    glClearColor(0, 0, 0, 1);
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

KOpenGL::~KOpenGL() {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(mGLRC);
}

