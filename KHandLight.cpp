/**
 * @file   KHandLight.cpp
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#include "KHandLight.h"

#include "KUtility.h"

KHandLight::KHandLight() {
}

KHandLight::KHandLight(const KHandLight& orig) {
}

KHandLight::~KHandLight() {
}

static GLfloat lightDiffuse[3] = {1.0, 1.0, 1.0}; //拡散光
static GLfloat lightAmbient[3] = {0.25, 0.25, 0.25}; //環境光
static GLfloat lightSpecular[3] = {1.0, 1.0, 1.0}; //鏡面光

void KHandLight::at() {
    float lightPosition[4] = {DEPLOYMENT(mPosition), 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    float lightDirection[3] = {DEPLOYMENT(mDirection)};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0); // スポットライトの絞り（デフォルト 180.0）
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.1); // スポットライトの中心からの減衰の度合い（デフォルト 0）
}

