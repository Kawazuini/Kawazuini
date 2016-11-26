/**
 * @file KDrawSphere.cpp
 * @brief KDrawSphere
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

    // 頂点の割り当て
    KVector* vertex = mVertex;
    for (int i = mStack; i >= 0; --i) {
        float theta = Math::PI * (float) i / mStack;
        float y = mRadius * cos(theta);
        float r = mRadius * sin(theta);
        for (int j = mSlice; j >= 0; --j, ++vertex) {
            float phi = 2.0f * Math::PI * (float) j / mSlice;
            *vertex = KVector(-r * cos(phi), y, -r * sin(phi)) + mPosition;
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
    for (int i = mStack - 1; i >= 0; --i) {
        float y0 = (1.0 - (float) i / mStack) * repeatY;
        float y1 = (1.0 - (float) (i - 1) / mStack) * repeatY;

        mTexture->bindON();
        glBegin(GL_QUAD_STRIP);
        for (int j = mSlice; j >= 0; --j, ++vertex) {
            float x = (float) j / mSlice * repeatX;

            glTexCoord2d(x, y0);
            glNormal3f(DEPLOYMENT(*vertex));
            glVertex3f(DEPLOYMENT(*vertex));

            glTexCoord2d(x, y1);
            glNormal3f(DEPLOYMENT(*(vertex + mSlice + 1)));
            glVertex3f(DEPLOYMENT(*(vertex + mSlice + 1)));
        }
        glEnd();
        mTexture->bindOFF();
    }
}

