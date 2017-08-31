/**
 * @file   KObject.cpp
 * @brief  KObject
 * @author Maeda Takumi
 */
#include "KObject.h"

#include "KFile.h"
#include "KImage.h"
#include "KRect.h"

KObject::KObject(const KFile& aFile) :
mObject(aFile.read()),
mTexImage(),
mTexture(mTexImage.mWidth),
mDrawMode(GL_TRIANGLES) {
    // ポリゴン当たりの頂点数の確認
    for (const String& i : mObject) {
        if (i[0] == 'f') {
            Vector<String> info(split(i, R"(\s)"));
            mPolygonSize = info.size() - 1;
            break;
        }
    }

    // ファイル読み込み & 変換
    Vector<KVector> fileVertex;
    Vector<float> fileCoord;
    Vector<KVector> fileNormal;
    for (const String& i : mObject) {
        Vector<String> info(split(i, R"(\s)"));
        if (info[0] == "v") { // 頂点情報
            fileVertex.push_back(KVector(toFloat(info[1]), toFloat(info[2]), toFloat(info[3])));
        }
        if (info[0] == "vt") { // テクスチャ情報
            fileCoord.push_back(toFloat(info[1]));
            fileCoord.push_back(1.0f - toFloat(info[2])); // y軸反転
        }
        if (info[0] == "vn") { // 法線情報
            fileNormal.push_back(KVector(toFloat(info[1]), toFloat(info[2]), toFloat(info[3])));
        }
        if (info[0] == "f") { // 表面情報
            for (auto j = info.begin() + 1, j_e(info.end()); j != j_e; ++j) {
                Vector<String> face(split(*j, "/")); // 頂点/テクスチャ/法線
                // 頂点
                mObjectVertex.push_back(fileVertex[toInt(face[0]) - 1]);
                // テクスチャ
                if (face.size() >= 2) {
                    int index(toInt(face[1]) - 1);
                    mObjectCoord.push_back(fileCoord[index * 2]);
                    mObjectCoord.push_back(fileCoord[index * 2 + 1]);
                }
                // 法線
                if (face.size() >= 3) {
                    mObjectNormal.push_back(fileNormal[toInt(face[2]) - 1]);
                }
            }
        }
    }
    if (mObjectNormal.empty()) { // 法線情報の補填(ポリゴンから法線を割り出す)
        for (auto i = mObjectVertex.begin(), i_e(mObjectVertex.end()); i != i_e; i += mPolygonSize) {
            KVector v1(*(i + 0)), v2(*(i + 1)), v3(*(i + 2));
            for (int j = 0; j < mPolygonSize; ++j) mObjectNormal.push_back((v2 - v1).cross(v3 - v2).normalization());
        }
    }

    mVertex = new KVertexBufferObject<KVector>(mObjectVertex, GL_ARRAY_BUFFER, GL_STREAM_DRAW);
    mCoord = new KVertexBufferObject<float>(mObjectCoord, GL_ARRAY_BUFFER, GL_STREAM_DRAW);
    mNormal = new KVertexBufferObject<KVector>(mObjectNormal, GL_ARRAY_BUFFER, GL_STREAM_DRAW);

    mTexture.drawImage(
            mTexImage,
            KRect(mTexImage.mWidth, mTexImage.mHeight),
            KVector()
            );
    mTexture.reflect();
}

KObject::~KObject() {
    delete mVertex;
    delete mCoord;
    delete mNormal;
}

void KObject::draw() const {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    mTexture.bindON();

    mVertex->bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    mCoord->bind();
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    mNormal->bind();
    glNormalPointer(GL_FLOAT, 0, 0);

    glDrawArrays(mDrawMode, 0, mVertex->size());

    mTexture.bindOFF();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

