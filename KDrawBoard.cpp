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
mNormal((mVertex[1] - mVertex[0]).cross(mVertex[2] - mVertex[1]).normalization()),
mTexture(aTexture) {
    // 中心座標の計算
    for (KVector i : mVertex) mCenter += i;
    mCenter /= mVertex.size();
}

void KDrawBoard::draw() const {
    // テクスチャ縁調整
    static const float TEX_VERTEX[4][2]{
        {0.00, 1.00},
        {1.00, 1.00},
        {1.00, 0.00},
        {0.00, 0.00},
    };

    if (mTexture) {
        mTexture->bindON();
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(DEPLOY_VEC(mNormal));
        for (int i = 0; i < 4; ++i) {
            glTexCoord2f(TEX_VERTEX[i][0], TEX_VERTEX[i][1]);
            glVertex3f(DEPLOY_VEC(mVertex[i]));
        }
        glEnd();
        mTexture->bindOFF();
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
    for (auto i = mVertex.begin(), i_e(mVertex.end()); i != i_e; ++i) {
        i->operator-=(mCenter);
        *i = i->rotate(aQuater);
        i->operator+=(mCenter);
    }
}

const KVector& KDrawBoard::position() const {
    return mCenter;
}

const KVector& KDrawBoard::normal() const {
    return mNormal;
}

