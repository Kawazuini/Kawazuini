/**
 * @file   KPolygon.cpp
 * @brief  KPolygon
 * @author Maeda Takumi
 */
#include "KPolygon.h"

#include "KSegment.h"

KPolygon::KPolygon(const List<KVector>& aVertex) {
    mVertex = aVertex;
    mNormal = (mVertex[1] - mVertex[0]).cross(mVertex[2] - mVertex[1]).normalization();
}

bool KPolygon::operator*(const KVector& aPoint) {
    // 交差点と頂点との外積がすべて等しい場合衝突(交差点がポリゴン内にある)
    for (auto i = mVertex.begin(), i_e = mVertex.end(); i != i_e; ++i) {
        KVector ver = (i + 1 == i_e) ? *(mVertex.begin()) : *i;
        if (mNormal != (ver - *i).cross(aPoint - ver)) return false;
    }
    return true;
}

bool KPolygon::operator*(const KSegment& aSegment) {
    return operator*(hitPoint(aSegment));
}

KVector KPolygon::hitPoint(const KSegment& aSegment) {
    // 線分と面との衝突判定(線分の端がそれぞれ面の表裏に存在するか)
    if (aSegment.mVec1.dot(mNormal) * aSegment.mVec2.dot(mNormal) < 0) {
        KVector v1 = aSegment.mVec1 - mVertex[0];
        KVector v2 = aSegment.mVec2 - mVertex[0];
        float m = v1.dot(mNormal);
        float n = v2.dot(mNormal);
        return (aSegment.mVec2 - aSegment.mVec1) * m / (m + n) + aSegment.mVec1;
    }
    return KVector(); // 衝突していないときは零ベクトルを返す
}

