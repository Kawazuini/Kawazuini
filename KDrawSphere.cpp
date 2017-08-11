/**
 * @file   KDrawSphere.cpp
 * @brief  KDrawSphere
 * @author Maeda Takumi
 */
#include "KDrawSphere.h"

#include "KMath.h"
#include "KOpenGL.h"
#include "KSphere.h"
#include "KTexture.h"

const int KDrawSphere::SURFACE_POINT;

KDrawSphere::KDrawSphere(
        const KSphere& aSphere,
        const int& aStack,
        const int& aSlice,
        const color& aColor,
        const int& aInner
        ) :
mSphere(KVector(), aSphere.mRadius),
mStack(aStack),
mSlice(aSlice),
mColor(aColor),
mVertexSize((mStack + 1) * (mSlice + 1)),
mIndexSize(mStack * mSlice * 2),
mVertex(mVertexSize, GL_ARRAY_BUFFER, GL_STREAM_DRAW),
mNormal(mVertexSize, GL_ARRAY_BUFFER, GL_STREAM_DRAW),
mIndex(mIndexSize, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
    const float thetaStack(Math::PI / mStack);
    const float thetaSlice((Math::PI * 2) / mSlice);

    unsigned int number((mSlice + 1) * (mStack + 1));

    // 頂点の割り当て
    KVector * vertex(mVertex.data());
    for (int i = 0; i <= mStack; ++i) {
        float stack(thetaStack * i);
        float y(cosf(stack)); // 輪切り高さ
        float r(sinf(stack)); // 輪切り半径

        for (int j = 0; j <= mSlice; ++j) {
            float slice(thetaSlice * j);
            *vertex++ = KVector(r * cosf(slice), y, r * sinf(slice)) * mSphere.mRadius * aInner;
        }
    }
    vertex -= number;

    // 法線の割り当て
    KVector * normal(mNormal.data());
    for (int i = 0; i <= mStack; ++i) {
        for (int j = 0; j <= mSlice; ++j) {
            *normal++ = (*vertex++).normalization() * aInner;
        }
    }

    auto index(mIndex.data());
    for (int i = 0; i < mStack; ++i) {
        for (int j = 0; j < mSlice; ++j) {
            int count((mSlice + 1) * i + j);

            // 上三角形
            (*index)[0] = count;
            (*index)[1] = count + 1;
            (*index)[2] = count + mSlice + 2;
            ++index;

            // 下三角形
            (*index)[0] = count;
            (*index)[1] = count + mSlice + 2;
            (*index)[2] = count + mSlice + 1;
            ++index;
        }
    }
    translate(aSphere.mPosition);
}

void KDrawSphere::draw() const {
    glColor(mColor);

    mVertex.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    mNormal.bind();
    glNormalPointer(GL_FLOAT, 0, 0);
    mIndex.bind();
    glDrawElements(GL_TRIANGLES, mIndex.size() * SURFACE_POINT, GL_UNSIGNED_INT, 0);
}

void KDrawSphere::translate(const KVector& aVec) {
    KVector move(aVec - mSphere.mPosition);
    mSphere.mPosition += move;
    // 頂点の割り当て
    KVector * vertex(mVertex.data());
    for (int i = 0; i <= mStack; ++i) {
        for (int j = 0; j <= mSlice; ++j) {
            *vertex++ += move;
        }
    }
}

void KDrawSphere::rotate(const KQuaternion& aQuater) {
    //    for (int i = 0; i <= mStack; ++i) {
    //        for (int j = 0; j < mSlice; ++j) {
    //            mVertex[i][j] = (mVertex[i][j] - mPosition).rotate(aQuater) + mPosition;
    //            mNormal[i][j] = mNormal[i][j].rotate(aQuater);
    //        }
    //    }
}

