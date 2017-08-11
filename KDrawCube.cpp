/**
 * @file   KDrawCube.cpp
 * @brief  KDrawCube
 * @author Maeda Takumi
 */
#include "KDrawCube.h"

const int KDrawCube::CENTROID = 8;

const int KDrawCube::DRAW_VERTEX_INDEX[6][4] = {
    {5, 1, 3, 7},
    {0, 4, 6, 2},
    {3, 2, 6, 7},
    {0, 1, 5, 4},
    {4, 5, 7, 6},
    {1, 0, 2, 3},
};

KDrawCube::KDrawCube(const float& aScale, const KVector& aPosition) :
mVertex({
    KVector(0, 0, 0) * aScale,
    KVector(1, 0, 0) * aScale,
    KVector(0, 1, 0) * aScale,
    KVector(1, 1, 0) * aScale,
    KVector(0, 0, 1) * aScale,
    KVector(1, 0, 1) * aScale,
    KVector(0, 1, 1) * aScale,
    KVector(1, 1, 1) * aScale,
    KVector(1, 1, 1) * aScale / 2
}),
mNormal({
    KVector(1.00f, 0.00f, 0.00f),
    KVector(-1.0f, 0.00f, 0.00f),
    KVector(0.00f, 1.00f, 0.00f),
    KVector(0.00f, -1.0f, 0.00f),
    KVector(0.00f, 0.00f, 1.00f),
    KVector(0.00f, 0.00f, -1.0f)
}),
mRadius((mVertex[0] - mVertex[CENTROID]).length()) {
    translate(aPosition);
}

void KDrawCube::draw() const {
    for (int i = 0; i < 6; ++i) { // 六個の面
        glBegin(GL_POLYGON);
        glNormal(mNormal[i]);
        for (int j = 0; j < 4; ++j) { // 四角形
            glVertex(mVertex[DRAW_VERTEX_INDEX[i][j]]);
        }
        glEnd();
    }
}

void KDrawCube::translate(const KVector& aVec) {
    KVector move(aVec - mVertex[CENTROID]);

    for (int i = 0; i < 9; ++i) mVertex[i] += move;
}

void KDrawCube::rotate(KVector aOrigin, const KQuaternion& aQuater) {
    for (KVector& i : mVertex) i = (i - aOrigin).rotate(aQuater) + aOrigin;
    for (KVector& i : mNormal) i = i.rotate(aQuater);
}

const KVector& KDrawCube::position() const {
    return mVertex[CENTROID];
}

const float& KDrawCube::radius() const {
    return mRadius;
}

