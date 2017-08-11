/**
 * @file   KDrawBoard.cpp
 * @brief  KDrawBoard
 * @author Maeda Takumi
 */
#include "KDrawBoard.h"

KDrawBoard::KDrawBoard(
        const Vector<KVector>& aVertex,
        const KTexture* aTexture
        ) :
mVertex(aVertex),
mCenter((mVertex[0] + mVertex[1] + mVertex[2] + mVertex[3]) / 4),
mNormal((mVertex[1] - mVertex[0]).cross(mVertex[2] - mVertex[1]).normalization()),
mTexture(aTexture) {
}

void KDrawBoard::draw() const {
    // テクスチャ縁調整
    static const float TEX_VERTEX[4][2]{
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 0.0f},
    };

    glNormal(mNormal);
    if (mTexture) {
        mTexture->bindON();
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 4; ++i) {
            glTexCoord2f(TEX_VERTEX[i][0], TEX_VERTEX[i][1]);
            glVertex(mVertex[i]);
        }
        glEnd();
        mTexture->bindOFF();
    } else {
        glBegin(GL_TRIANGLE_FAN);
        for (const KVector& i : mVertex) glVertex(i);
        glEnd();
    }
}

void KDrawBoard::translate(const KVector& aVec) {
    KVector move(aVec - mCenter);
    mCenter += move;
    for (auto i = mVertex.begin(), i_e(mVertex.end()); i != i_e; ++i) {
        i->operator+=(move);
    }
}

void KDrawBoard::rotate(const KQuaternion& aQuater) {
    mNormal = mNormal.rotate(aQuater);
    for (KVector& i : mVertex) i = (i - mCenter).rotate(aQuater) + mCenter;
}

const KVector& KDrawBoard::position() const {
    return mCenter;
}

const KVector& KDrawBoard::normal() const {
    return mNormal;
}

