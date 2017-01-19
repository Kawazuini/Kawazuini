/**
 * @file KSegment.h
 * @author Maeda Takumi
 */
#ifndef KSEGMENT_H
#define KSEGMENT_H

#include "KVector.h"

class KSegment {
public:
    KVector mVec1;
    KVector mVec2;

    KSegment() = default;
    KSegment(const KVector& aVec1, const KVector& aVec2);
    KSegment(const KSegment& orig) = default;
    virtual ~KSegment() = default;

    float length() const;
    KVector direction() const;
};

#endif /* KSEGMENT_H */

