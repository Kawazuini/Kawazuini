/**
 * @file   KShading.cpp
 * @brief  KShading
 * @author Maeda Takumi
 */
#include "KShading.h"

#include "KOpenGL.h"

const char* const KShading::SHADER_VERTEX[]{
    "#version 120\n",
    "",
    "varying vec4 vPosition;", //   頂点座標
    "varying vec3 vNormal;", //     法線ベクトル
    "varying vec4 vGLPosition;", // 頂点座標(無変換)
    "varying vec4 vGLColor;", //    描画色
    "",
    "void main(void) {",
    "    vPosition   =           gl_ModelViewMatrix * gl_Vertex;",
    "    vNormal     = normalize(gl_NormalMatrix    * gl_Normal);",
    "    vGLPosition = gl_Vertex;",
    "    vGLColor    = gl_Color;",
    "",
    "    gl_Position    = ftransform();",
    "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;",
    "}\n",
};
const char* const KShading::SHADER_FRAGMENT_COLOR[]{
    "#version 120\n",
    "",
    "varying vec4 vGLColor;", // 描画色
    "",
    "void main(void) {",
    "    gl_FragColor = vGLColor;" // 描画色そのまま
    "}\n",
};
const char* const KShading::SHADER_FRAGMENT_TEXTURE[]{
    "#version 120\n",
    ""
    "uniform sampler2D texture;",
    "",
    "void main(void) {",
    "    gl_FragColor = texture2DProj(texture, gl_TexCoord[0]);" // テクスチャの色そのまま
    "}\n",
};
const char* const KShading::SHADER_FRAGMENT_PHONG[]{
    "#version 120\n",
    ""
    "uniform sampler2D texture;",
    "",
    "varying vec4 vPosition;", //   頂点座標
    "varying vec3 vNormal;", //     法線ベクトル
    "",
    "void main(void) {",
    "    vec4 color   = texture2DProj(texture, gl_TexCoord[0]);", // テクスチャの色
    "",
    "", // 光線ベクトル・視線ベクトル
    "    vec3 light  = (gl_LightSource[0].position * vPosition.w - gl_LightSource[0].position.w * vPosition).xyz;",
    "    vec3 nLight = normalize(light);",
    "    vec3 view   = -vPosition.xyz;",
    "    vec3 nView  = normalize(view);",
    "    vec3 nHalf  = normalize(nLight + nView);",
    "",
    "", // 距離での減衰
    "    float distance    = length(light);",
    "    float attenuation = min(1.0 / ",
    "                      ( gl_LightSource[0].constantAttenuation",
    "                      + gl_LightSource[0].linearAttenuation    * distance",
    "                      + gl_LightSource[0].quadraticAttenuation * distance * distance)"
    "                      , 1.0);",
    "",
    "", // 角度での減衰
    "    float angle = acos(dot(nLight, nView));",
    "    float LS = dot(-nLight, normalize(gl_LightSource[0].spotDirection));",
    "    if (LS < gl_LightSource[0].spotCosCutoff) attenuation = 0.0;", //スポットライトの外側
    "    else attenuation *= pow(LS, gl_LightSource[0].spotExponent);",
    "",
    "", // 拡散反射率と鏡面反射率
    "    float diffuse  = max(dot(vNormal, nLight), 0.0);",
    "    float specular = pow(max(dot(vNormal, nHalf), 0.0), gl_FrontMaterial.shininess);",
    "", // 計算結果(フラグメントの色)
    "    gl_FragColor = color * gl_LightSource[0].diffuse  * diffuse",
    "                 +   gl_FrontLightProduct[0].specular * specular",
    "                 + color * gl_LightSource[0].ambient;",
    "    gl_FragColor = vec4((gl_FragColor * attenuation).xyz, color.w);" // 透過値は変更しない
    "}\n",
};

const int KShading::CHAR_SIZE(sizeof SHADER_VERTEX[0]);
const int KShading::VERTEX_SIZE(sizeof SHADER_VERTEX / CHAR_SIZE);

KShader* KShading::ColorShading(NULL);
KShader* KShading::TextureShading(NULL);
KShader* KShading::PhongShading(NULL);

KShading::KShading() {
    if (!ColorShading) ColorShading = new KShader(VERTEX_SIZE, SHADER_VERTEX, sizeof SHADER_FRAGMENT_COLOR / CHAR_SIZE, SHADER_FRAGMENT_COLOR);

    if (!TextureShading) TextureShading = new KShader(VERTEX_SIZE, SHADER_VERTEX, sizeof SHADER_FRAGMENT_TEXTURE / CHAR_SIZE, SHADER_FRAGMENT_TEXTURE);
    TextureShading->ON();
    glUniform1i(glGetUniformLocation(TextureShading->program(), "texture"), 0);

    if (!PhongShading) PhongShading = new KShader(VERTEX_SIZE, SHADER_VERTEX, sizeof SHADER_FRAGMENT_PHONG / CHAR_SIZE, SHADER_FRAGMENT_PHONG);
    PhongShading->ON();
    glUniform1i(glGetUniformLocation(PhongShading->program(), "texture"), 0);

}

KShading::~KShading() {
    delete ColorShading;
    delete TextureShading;
    delete PhongShading;
}

