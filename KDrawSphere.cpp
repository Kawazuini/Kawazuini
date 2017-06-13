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
        ) :
mRadius(aRadius),
mStack(aStack),
mSlice(aSlice),
mVertex(mStack + 1, Vector<KVector>(mSlice)),
mNormal(mStack + 1, Vector<KVector>(mSlice)),
mVertexSize((mStack - 1) * mSlice + 2),
mTexture(NULL) {
    static const float DOUBLE_PI(2.0f * Math::PI);
    // 頂点と法線の割り当て
    for (int i = 0; i <= mStack; ++i) {
        float theta(Math::PI * (float) i / mStack);
        float y(mRadius * cos(theta)); // 輪切り高さ
        float r(mRadius * sin(theta)); // 輪切り半径
        for (int j = 0; j < mSlice; ++j) {
            float phi(DOUBLE_PI * (float) j / mSlice);
            if (validIndex(i, j)) {
                mVertex[i][j] = KVector(r * sin(phi), y, r * cos(phi));
                mNormal[i][j] = mVertex[i][j];
            }
        }
    }
    KDrawSphere::translate(aPosition);
}

const KVector& KDrawSphere::getVertex(const int& aStack, const int& aSlice) const {
    int stack(aStack < 0 ? 0 : aStack > mStack ? mStack : aStack);
    int slice(aSlice < 0 ? mSlice : aSlice);

    bool yend(stack == 0 || stack == mStack); // 上端か下端
    if ((yend && slice != 0) || (!yend && slice == mSlice)) {
        return mVertex[stack][0];
    }
    return mVertex[stack][slice];
}

const KVector& KDrawSphere::getNormal(const int& aStack, const int& aSlice) const {
    int stack(aStack < 0 ? 0 : aStack > mStack ? mStack : aStack);
    int slice(aSlice < 0 ? mSlice : aSlice);

    bool yend(stack == 0 || stack == mStack); // 上端か下端
    if ((yend && slice != 0) || (!yend && slice == mSlice)) {
        return mNormal[stack][0];
    }
    return mNormal[stack][slice];
}

bool KDrawSphere::validIndex(const int& aStack, const int& aSlice) {
    bool yend(aStack == 0 || aStack == mStack); // 上端か下端
    return !yend || (yend && aSlice == 0);
}

void KDrawSphere::draw() const {
    // テクスチャ繰り返し数
    static const int repeatY(1);
    static const int repeatX(1);

    for (int i = 0; i < mStack; ++i) {
        float y0((float) (i + 0) / mStack * repeatY);
        float y1((float) (i + 1) / mStack * repeatY);

        mTexture->bindON();
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= mSlice; ++j) {
            float x = (float) j / mSlice * repeatX;

            KVector v0(getVertex(i, j));
            KVector v1(getVertex(i + 1, j));
            KVector n0(getNormal(i, j));
            KVector n1(getNormal(i + 1, j));

            glTexCoord2f(x, y0);
            glNormal3f(DEPLOY_VEC(n0));
            glVertex3f(DEPLOY_VEC(v0));

            glTexCoord2f(x, y1);
            glNormal3f(DEPLOY_VEC(n1));
            glVertex3f(DEPLOY_VEC(v1));
        }
        glEnd();
        mTexture->bindOFF();
    }
}

void KDrawSphere::translate(const KVector& aVec) {
    KVector move(aVec - mPosition);
    mPosition += move;
    for (int i = 0; i <= mStack; ++i) {
        for (int j = 0; j < mSlice; ++j) {
            if (validIndex(i, j)) {
                mVertex[i][j] += move;
            }
        }
    }
}

void KDrawSphere::rotate(const KQuaternion& aQuater) {
    for (int i = 0; i <= mStack; ++i) {
        for (int j = 0; j < mSlice; ++j) {
            if (validIndex(i, j)) {
                mVertex[i][j] = (mVertex[i][j] - mPosition).rotate(aQuater) + mPosition;
                mNormal[i][j] = mNormal[i][j].rotate(aQuater);
            }
        }
    }
}

