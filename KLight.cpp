/**
 * @file   KLight.cpp
 * @brief  KLight
 * @author Maeda Takumi
 */
#include "KLight.h"

#include "KUtility.h"

int KLight::sLightCount(0);

KLight::KLight() :
mLightNumber(sLightCount) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0 + sLightCount);
    ++sLightCount;

    setDiffuse(1.0f, 1.0f, 1.0f);
    setAmbient(0.3f, 0.3f, 0.3f);
    setSpecular(1.0f, 1.0f, 1.0f);
}

KLight::~KLight() {
    --sLightCount;
}

void KLight::setDiffuse(const float& aRed, const float& aGreen, const float& aBlue) {
    mDiffuse[0] = aRed;
    mDiffuse[1] = aGreen;
    mDiffuse[2] = aBlue;
    glLightfv(GL_LIGHT0 + mLightNumber, GL_DIFFUSE, mDiffuse);
}

void KLight::setAmbient(const float& aRed, const float& aGreen, const float& aBlue) {
    mAmbient[0] = aRed;
    mAmbient[1] = aGreen;
    mAmbient[2] = aBlue;
    glLightfv(GL_LIGHT0 + mLightNumber, GL_AMBIENT, mAmbient);
}

void KLight::setSpecular(const float& aRed, const float& aGreen, const float& aBlue) {
    mSpecular[0] = aRed;
    mSpecular[1] = aGreen;
    mSpecular[2] = aBlue;
    glLightfv(GL_LIGHT0 + mLightNumber, GL_SPECULAR, mSpecular);
}

void KLight::setPosition(const KVector& aPosition) {
    mPosition = aPosition;
    float lightPosition[4]{DEPLOY_VEC(mPosition), 1.0f};
    glLightfv(GL_LIGHT0 + mLightNumber, GL_POSITION, lightPosition);
}

void KLight::setDirection(const KVector& aDirection) {
    mDirection = aDirection;
    float lightDirection[3]{DEPLOY_VEC(mDirection)};
    glLightfv(GL_LIGHT0 + mLightNumber, GL_SPOT_DIRECTION, lightDirection);
}

void KLight::setAttenutation(const float& aConstant, const float& aLinear, const float& aQuadratic) {
    mAttenutation[0] = aConstant;
    mAttenutation[1] = aLinear;
    mAttenutation[2] = aQuadratic;
    glLightf(GL_LIGHT0 + mLightNumber, GL_CONSTANT_ATTENUATION, mAttenutation[0]);
    glLightf(GL_LIGHT0 + mLightNumber, GL_LINEAR_ATTENUATION, mAttenutation[1]);
    glLightf(GL_LIGHT0 + mLightNumber, GL_QUADRATIC_ATTENUATION, mAttenutation[2]);
}

void KLight::setSpotCutoff(const float& aSpotCutoff) {
    mSpotCutoff = aSpotCutoff;
    glLightf(GL_LIGHT0 + mLightNumber, GL_SPOT_CUTOFF, mSpotCutoff);
}

void KLight::setSpotExponent(const float& aSpotExponent) {
    mSpotExponent = aSpotExponent;
    glLightf(GL_LIGHT0 + mLightNumber, GL_SPOT_EXPONENT, mSpotExponent);
}

const KVector& KLight::position() const {
    return mPosition;
}

const KVector& KLight::direction() const {
    return mDirection;
}

