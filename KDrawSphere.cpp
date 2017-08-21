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
mVertexSize((mStack - 1) * mSlice + 2),
mIndexSize(mStack * mSlice * 2),
mVertex(mVertexSize, GL_ARRAY_BUFFER, GL_STREAM_DRAW),
mNormal(mVertexSize, GL_ARRAY_BUFFER, GL_STREAM_DRAW),
mIndex(mIndexSize, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
    const float thetaStack(Math::PI / mStack);
    const float thetaSlice((Math::PI * 2) / mSlice);

    // 頂点の割り当て
    KVector * vertex(mVertex.data());
    for (int i = 0, count = 0; i <= mStack; ++i) {
        float stack(thetaStack * i);
        float y(cosf(stack)); // 輪切り高さ
        float r(sinf(stack)); // 輪切り半径

        for (int j = 0; j <= mSlice; ++j, ++count) {
            if (isValidIndex(count)) {
                float slice(thetaSlice * j);
                *vertex++ = KVector(r * cosf(slice), y, r * sinf(slice)) * mSphere.mRadius * aInner;
            }
        }
    }
    vertex -= mVertexSize;

    // 法線の割り当て
    KVector * normal(mNormal.data(GL_WRITE_ONLY));
    for (int i = 0, count = 0; i <= mStack; ++i) {
        for (int j = 0; j <= mSlice; ++j, ++count) {
            if (isValidIndex(count)) *normal++ = (vertex++)->normalization() * aInner;
        }
    }

    auto index(mIndex.data(GL_WRITE_ONLY));
    for (int i = 0, count = 0; i < mStack; ++i, ++count) {
        for (int j = 0; j < mSlice; ++j, ++count) {
            // 上三角形
            (*index)[0] = convertValidIndex(count);
            (*index)[1] = convertValidIndex(count + 1);
            (*index)[2] = convertValidIndex(count + mSlice + 2);
            ++index;

            // 下三角形
            (*index)[0] = convertValidIndex(count);
            (*index)[1] = convertValidIndex(count + mSlice + 2);
            (*index)[2] = convertValidIndex(count + mSlice + 1);
            ++index;
        }
    }
    translate(aSphere.mPosition);
}

bool KDrawSphere::isValidIndex(const int& aIndex) const {
    const int stack(aIndex / (mSlice + 1)), slice(aIndex % (mSlice + 1));
    return slice == 0 || !(stack == 0 || stack == mStack || slice == mSlice);
}

int KDrawSphere::convertValidIndex(const int& aIndex) const {
    int index(aIndex);
    const int stack(aIndex / (mSlice + 1)), slice(aIndex % (mSlice + 1));
    if (stack == 0) return 0;
    if (stack == mStack) return mVertexSize - 1;
    if (slice == mSlice) index -= mSlice;

    return index - mSlice - (stack - 1);
}

void KDrawSphere::draw() const {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glColor(mColor);

    mVertex.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    mNormal.bind();
    glNormalPointer(GL_FLOAT, 0, 0);
    mIndex.bind();
    glDrawElements(GL_TRIANGLES, mIndex.size() * SURFACE_POINT, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void KDrawSphere::translate(const KVector& aVec) {
    KVector move(aVec - mSphere.mPosition);
    mSphere.mPosition += move;
    KVector * vertex(mVertex.data());
    for (int i = 0, count = 0; i <= mStack; ++i) {
        for (int j = 0; j <= mSlice; ++j, ++count) {
            if (isValidIndex(count)) *vertex++ += move;
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

