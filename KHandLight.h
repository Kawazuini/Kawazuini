/**
 * @file   KHandLight.h
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#ifndef KHANDLIGHT_H
#define KHANDLIGHT_H

#include "KLight.h"
#include "KVector.h"

class KHandLight : public KLight {
private:
    static const float DIFFUSE[3];
    static const float AMBIENT[3];
    static const float SPECULAR[3];
public:
    KVector mPosition;
    KVector mDirection;

    KHandLight();
    virtual ~KHandLight() = default;

    void at();
};

#endif /* KHANDLIGHT_H */

