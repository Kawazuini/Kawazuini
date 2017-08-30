/**
 * @file   KHandLight.cpp
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#include "KHandLight.h"

#include "KCamera.h"

KHandLight::KHandLight(
        const KVector& aPosition,
        const KVector& aDirection
        ) :
mHandPosition(aPosition),
mHandDirection(aDirection) {
}

KHandLight::KHandLight(const KCamera& aCamera) :
KHandLight(aCamera.position(), aCamera.direction()) {
}

void KHandLight::update() {
    setPosition(mHandPosition);
    setDirection(mHandDirection);
}

