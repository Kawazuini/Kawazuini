/**
 * @file   KHandLight.cpp
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#include "KHandLight.h"

KHandLight::KHandLight(
        const KVector& aPosition,
        const KVector& aDirection
        ) :
mHandPosition(aPosition),
mHandDirection(aDirection) {
}

void KHandLight::update() {
    setPosition(mHandPosition);
    setDirection(mHandDirection);
}

