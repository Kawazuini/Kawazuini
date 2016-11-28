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
public:
    KVector mPosition;
    KVector mDirection;
public:
    KHandLight();
    KHandLight(const KHandLight& orig);
    virtual ~KHandLight();
    
    void at();
};

#endif /* KHANDLIGHT_H */

