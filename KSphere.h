/**
 * @file KSphere.h
 * @author Maeda Takumi
 */
#ifndef KSPHERE_H
#define KSPHERE_H

#include "KVector.h"

class KSphere {
public:
    KVector mPosition;
    float mRadius;

    KSphere() = default;
    KSphere(const KVector& aPosition, const float& aRadius);
    KSphere(const KSphere& orig) = default;
    virtual ~KSphere() = default;
};

#endif /* KSPHERE_H */

