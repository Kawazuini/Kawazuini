/**
 * @file   KDrawCylinder.h
 * @brief  KDrawCylinder
 * @author Maeda Takumi
 */
#include "KDrawCylinder.h"
#include "KQuaternion.h"
#include "KVertexBufferObject.h"

KDrawCylinder::KDrawCylinder(
        const KCylinder& aCylinder,
        const int& aQuality,
        const color& aColor
        ) :
mCylinder(aCylinder),
mDirection((mCylinder.mVec2 - mCylinder.mVec1).normalization()),
mQuality(aQuality),
mColor(aColor),
mVertex(mQuality * 2, GL_ARRAY_BUFFER, GL_STREAM_DRAW),
mNormal(mQuality * 2, GL_ARRAY_BUFFER, GL_STREAM_DRAW),
mIndex1(mQuality, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW),
mIndex2(mQuality, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
    // 方向に直行するベクトル
    KVector width;
    if (mDirection.x != 0.0f) {
        width = KVector((mDirection.y + mDirection.z) / mDirection.x, -1, -1);
    } else if (mDirection.y != 0.0f) {
        width = KVector(-1, (mDirection.z + mDirection.x) / mDirection.y, -1);
    } else if (mDirection.z != 0.0f) {
        width = KVector(-1, -1, (mDirection.x + mDirection.y) / mDirection.z);
    }
    width = width.normalization() * mCylinder.mWidth;

    const float rotate(2 * Math::PI / (mQuality - 1));

    KVector * vertex(mVertex.data());
    for (int i = 0; i < mQuality; ++i) {
        KVector v(width.rotate(KQuaternion(mDirection, rotate * i)));
        *vertex++ = mCylinder.mVec1 + v;
        *vertex++ = mCylinder.mVec2 + v;
    }
    KVector * normal(mNormal.data());
    for (int i = 0; i < mQuality; ++i) {
        KVector n(width.rotate(KQuaternion(mDirection, rotate * i)).normalization());
        *normal++ = n;
        *normal++ = n;
    }

    unsigned int* index1(mIndex1.data());
    for (int i = 0, i_e(mQuality * 2); i < i_e; i += 2, ++index1) {
        *index1 = i;
    }
    unsigned int* index2(mIndex2.data());
    for (int i(mQuality * 2 - 1); i > 0; i -= 2, ++index2) {
        *index2 = i;
    }
}

void KDrawCylinder::draw() const {
    glColor(mColor);

    mVertex.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    mNormal.bind();
    glNormalPointer(GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, mVertex.size());

    glDisableClientState(GL_NORMAL_ARRAY);
    glNormal(-mDirection);
    mIndex1.bind();
    glDrawElements(GL_POLYGON, mIndex1.size(), GL_UNSIGNED_INT, 0);
    glNormal(mDirection);
    mIndex2.bind();
    glDrawElements(GL_POLYGON, mIndex2.size(), GL_UNSIGNED_INT, 0);
    glEnableClientState(GL_NORMAL_ARRAY);
}

void KDrawCylinder::move(const KVector& aMoveAmount) {
    KVector * vertex(mVertex.data());
    for (int i = 0, i_e(mVertex.size()); i < i_e; ++i, ++vertex) {
        vertex->operator+=(aMoveAmount);
    }
}

void KDrawCylinder::rotate(
        const KQuaternion& aQuaternion,
        const KVector& aOrigin
        ) {
    mDirection = mDirection.rotate(aQuaternion);
    KVector * vertex(mVertex.data());
    for (int i = 0, i_e(mVertex.size()); i < i_e; ++i, ++vertex) {
        *vertex = (*vertex - aOrigin).rotate(aQuaternion) + aOrigin;
    }
    KVector * normal(mNormal.data());
    for (int i = 0, i_e(mNormal.size()); i < i_e; ++i, ++normal) {
        *normal = normal->rotate(aQuaternion);
    }
}

