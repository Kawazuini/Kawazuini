/**
 * @file   KLight.cpp
 * @brief  KLight
 * @author Maeda Takumi
 */
#include "KLight.h"

#include "KUtility.h"

KLight::KLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

KLight::KLight(const KLight& orig) {
}

KLight::~KLight() {
}

