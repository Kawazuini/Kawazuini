/**
 * @file   KDrawSphere.cpp
 * @brief  KDrawSphere
 * @author Maeda Takumi
 */
#include "KDrawSphere.h"

#include "KMath.h"
#include "KOpenGL.h"
#include "KTexture.h"

KDrawSphere::KDrawSphere(
        const KVector& aPosition,
        const float& aRadius,
        const int& aStack,
        const int& aSlice
        ) {
    mPosition = aPosition;
    mRadius = aRadius;
    mStack = aStack;
    mSlice = aSlice;
    mVertex = new KVector[(mStack + 1) * (mSlice + 1)];

    // 頂点と法線の割り当て
    KVector* vertex = mVertex;
    for (int i = 0; i <= mStack; ++i) {
        float theta = Math::PI * (float) i / mStack;
        float y = mRadius * cos(theta);
        float r = mRadius * sin(theta);
        for (int j = 0; j <= mSlice; ++j, ++vertex) {
            float phi = 2.0f * Math::PI * (float) j / mSlice;
            *vertex = KVector(r * sin(phi), y, r * cos(phi));
        }
    }

    mTexture = NULL;
}

KDrawSphere::~KDrawSphere() {
    delete[] mVertex;
}

void KDrawSphere::draw() const {
    // テクスチャ繰り返し数
    static const int repeatY = 1;
    static const int repeatX = 1;

    KVector* vertex = mVertex;
    for (int i = 0; i < mStack; ++i) {
        float y0 = (float) (i + 0) / mStack * repeatY;
        float y1 = (float) (i + 1) / mStack * repeatY;

        mTexture->bindON();
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= mSlice; ++j, ++vertex) {
            float x = (float) j / mSlice * repeatX;

            KVector n0 = *vertex;
            KVector n1 = *(vertex + mSlice + 1);
            KVector v0 = n0 + mPosition;
            KVector v1 = n1 + mPosition;

            glTexCoord2f(x, y0);
            glNormal3f(DEPLOYMENT(n0));
            glVertex3f(DEPLOYMENT(v0));

            glTexCoord2f(x, y1);
            glNormal3f(DEPLOYMENT(n1));
            glVertex3f(DEPLOYMENT(v1));
        }
        glEnd();
        mTexture->bindOFF();
    }
}

void KDrawSphere::tlanslate(const KVector& aVec) {
    mPosition = aVec;
}

void KDrawSphere::rotate(const KQuaternion& aQuater) {
    KVector* vertex = mVertex;
    for (int i = (mStack + 1) * (mSlice + 1) - 1; i >= 0; --i, ++vertex)
        *vertex = vertex->rotate(aQuater);
}

