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
    mNormal = new KVector[(mStack + 1) * (mSlice + 1)];

    // 頂点と法線の割り当て
    KVector* vertex = mVertex;
    KVector* normal = mNormal;
    for (int i = 0; i <= mStack; ++i) {
        float theta = Math::PI * (float) i / mStack;
        float y = mRadius * cos(theta);
        float r = mRadius * sin(theta);
        for (int j = 0; j <= mSlice; ++j, ++vertex, ++normal) {
            float phi = 2.0f * Math::PI * (float) j / mSlice;
            *vertex = (*normal = KVector(r * cos(phi), y, -r * sin(phi))) + mPosition;
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
    KVector* normal = mNormal;
    for (int i = 0; i < mStack; ++i) {
        float y0 = (float) (i + 0) / mStack * repeatY;
        float y1 = (float) (i + 1) / mStack * repeatY;

        mTexture->bindON();
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= mSlice; ++j, ++vertex, ++normal) {
            float x = (float) j / mSlice * repeatX;

            glTexCoord2f(x, y0);
            glNormal3f(DEPLOYMENT(*normal));
            glVertex3f(DEPLOYMENT(*vertex));

            glTexCoord2f(x, y1);
            glNormal3f(DEPLOYMENT(*(normal + mSlice + 1)));
            glVertex3f(DEPLOYMENT(*(vertex + mSlice + 1)));
        }
        glEnd();
        mTexture->bindOFF();
    }
}

