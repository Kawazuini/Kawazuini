/**
 * @file   KShading.cpp
 * @brief  KShading
 * @author Maeda Takumi
 */
#include "KShading.h"

#include "KOpenGL.h"

const Vector<String> KShading::SHADER_FRAGMENT_COLOR
{
    "#version 120\n",
    "",
    "uniform bool      uTexture;    ", // テクスチャ描画の有無
    "uniform sampler2D uTextureUnit;", // テクスチャユニット
    "",
    "varying vec4 vColor;", // 描画色
    "",
    "void main(void) {",
    "    if(uTexture) gl_FragColor = texture2DProj(uTextureUnit, gl_TexCoord[0]);",
    "    else         gl_FragColor = vColor;                                     "
    "}\n",
};

const Vector<String> KShading::SHADER_FRAGMENT_PHONG{
    "#version 120\n",
    "",
    "uniform bool      uTexture;    ", // テクスチャ描画の有無
    "uniform sampler2D uTextureUnit;", // テクスチャユニット
    "",
    "varying vec4 vPosition;        ", // 頂点座標
    "varying vec3 vNView;           ", // 視線ベクトルの正規化
    "varying vec3 vNormal;          ", // 法線ベクトル
    "varying vec4 vColor;           ", // 描画色
    "",
    "void main(void) {",
    "    vec4 color;                                                      "
    "    if(uTexture) color = texture2DProj(uTextureUnit, gl_TexCoord[0]);",
    "    else         color = vColor;                                     ",
    "",
    "    for(int i = 0; i < 8; ++i) {", // 光源数は8個まで
    "        float attenuation;      ", // 減衰係数
    "",
    "     ", // 光線ベクトル
    "        vec3 light  = (gl_LightSource[i].position - vPosition).xyz;",
    "        vec3 nLight = normalize(light);                            ",
    "        vec3 nHalf  = normalize(nLight + vNView);                  ",
    "",
    "     ", // 距離での減衰
    "        float distance = length(light);                                               ",
    "        attenuation    = min(1.0 /                                                    ",
    "                       ( gl_LightSource[i].constantAttenuation                        ",
    "                       + gl_LightSource[i].linearAttenuation    * distance            ",
    "                       + gl_LightSource[i].quadraticAttenuation * distance * distance)"
    "                       , 1.0);                                                        ",
    "",
    "     ", // 角度での減衰
    "        if(gl_LightSource[i].spotCutoff <= 90.0) {                                    ", // スポットライト
    "            float dotAngle = dot(-nLight, normalize(gl_LightSource[i].spotDirection));",
    "            if (dotAngle < gl_LightSource[i].spotCosCutoff) attenuation = 0.0;        ", //スポットライトの外側
    "            else attenuation *= pow(dotAngle, gl_LightSource[i].spotExponent);        ",
    "        }                                                                             ",
    "",
    "     ", // 拡散反射率と鏡面反射率
    "        float diffuse  = max(dot(vNormal, nLight), 0.0);                                ",
    "        float specular = pow(max(dot(vNormal, nHalf), 0.0), gl_FrontMaterial.shininess);",
    "     ", // 計算結果(フラグメントの色)
    "        vec4 col = color * gl_LightSource[i].diffuse  * diffuse    ",
    "                 +   gl_FrontLightProduct[i].specular * specular   ",
    "                 + color * gl_LightSource[i].ambient;              ",
    "        gl_FragColor += vec4((col * attenuation).rgb, color.a);    " // 合成(透過値は変更しない)
    "    }",
    "}\n",
};

const Vector<String> KShading::SHADER_VERTEX{
    "#version 120\n",
    "",
    "uniform bool      uTexture;    ", // テクスチャ描画の有無
    "",
    "varying vec4 vPosition;        ", // 頂点座標
    "varying vec3 vNView;           ", // 頂点までの視線ベクトル(正規化)
    "varying vec3 vNormal;          ", // 法線ベクトル
    "varying vec4 vColor;           ", // 描画色
    "",
    "void main(void) {",
    "    vPosition = gl_ModelViewMatrix * gl_Vertex;",
    "    vNView    = normalize(-vPosition.xyz);     ",
    "    vNormal   = gl_NormalMatrix    * gl_Normal;",
    "",
    "    if(uTexture) gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;",
    "    else vColor = gl_Color;                                               ",
    "    gl_Position = ftransform();",
    "}\n",
};

KShader* KShading::ColorShading(NULL);
KShader* KShading::PhongShading(NULL);

KShading::KShading() {
    if (!ColorShading) ColorShading = new KShader(SHADER_VERTEX, SHADER_FRAGMENT_COLOR);
    ColorShading->ON();
    glUniform1i(glGetUniformLocation(ColorShading->program(), "uTexture"), 0);
    glUniform1i(glGetUniformLocation(ColorShading->program(), "uTextureUnit"), 0);

    if (!PhongShading) PhongShading = new KShader(SHADER_VERTEX, SHADER_FRAGMENT_PHONG);
    PhongShading->ON();
    glUniform1i(glGetUniformLocation(PhongShading->program(), "uTexture"), 0);
    glUniform1i(glGetUniformLocation(PhongShading->program(), "uTextureUnit"), 0);
}

KShading::~KShading() {
    delete ColorShading;
    delete PhongShading;
}

