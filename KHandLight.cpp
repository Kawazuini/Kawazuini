/**
 * @file   KHandLight.cpp
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#include "KHandLight.h"

#include "KUtility.h"

const float KHandLight::DIFFUSE[3]{
    1.0, 1.0, 1.0
}; //拡散光
const float KHandLight::AMBIENT[3]{0.25, 0.25, 0.25}; //環境光
const float KHandLight::SPECULAR[3]{1.0, 1.0, 1.0}; //鏡面光

KHandLight::KHandLight() {
}

void KHandLight::at() {
    float lightPosition[4] = {DEPLOYMENT(mPosition), 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    float lightDirection[3] = {DEPLOYMENT(mDirection)};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT);
    glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.001);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0); // スポットライトの絞り（デフォルト 180.0）
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 7.5); // スポットライトの中心からの減衰の度合い（デフォルト 0）
}

