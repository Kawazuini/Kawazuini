/**
 * @file KPolygon.h
 * @author Maeda Takumi
 */
#ifndef KPOLYGON_H
#define KPOLYGON_H

#include "KUtility.h"

#include "KVector.h"

class KSegment;

/**
 * @brief Polygon for collision determination
 * @author Maeda Takumi
 */
class KPolygon {
public:
    /** @brief vertex list   */ List<KVector> mVertex;
    /** @brief normal vector */ KVector mNormal;

    KPolygon() = default;
    KPolygon(const List<KVector>& aVertex);
    KPolygon(const KPolygon& orig) = default;
    virtual ~KPolygon() = default;

    /**
     * @brief evaluate collision with Point.
     * @param aPoint target Point
     * @return collision determination
     */
    bool operator*(const KVector& aPoint);

    /**
     * @brief evaluate collision with Segment
     * @param aSegment target Segment
     * @return collision determination
     */
    bool operator*(const KSegment& aSegment);

    /**
     * @brief compute intersection with Segment
     * @param aSegment target Segment
     * @return intersection
     */
    KVector hitPoint(const KSegment& aSegment);
};

#endif /* KPOLYGON_H */

