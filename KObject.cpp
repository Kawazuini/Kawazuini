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
mTexture(Math::max(mTexImage.mWidth, mTexImage.mHeight)),
mDrawMode(GL_TRIANGLES) {
    // 表面情報の確認(ループ外で処理削減)
    int polySize(0);
    bool texture(false), normal(false);
    for (const String& i : mObject) {
        if (i[0] == 'f') {
            Vector<String> info(split(i, R"(\s)"));
            polySize = info.size() - 1;

            Vector<String> face(split(info[1], "/"));
            int faceSize(face.size());
            if (faceSize >= 2) texture = !face[1].empty();
            if (faceSize >= 3) normal = !face[2].empty();
            break;
        }
    }

    // テクスチャサイズの調整
    float iw(mTexImage.mWidth), ih(mTexImage.mHeight);
    float correctX(1.0f), correctY(1.0f);
    if (iw < ih) correctX = iw / ih; // 縦長
    if (iw > ih) correctY = ih / iw; // 横長


    // ファイル読み込み & 変換
    Vector<KVector> fileVertex, objVertex;
    Vector<uvcoord> fileCoord, objCoord;
    Vector<KVector> fileNormal, objNormal;
    for (const String& i : mObject) {
        Vector<String> info(split(i, R"(\s)"));

        // 頂点情報
        if (info[0] == "v") {
            fileVertex.push_back(KVector(toFloat(info[1]), toFloat(info[2]), toFloat(info[3])));
        }

        // テクスチャ情報
        if (info[0] == "vt") {
            float x(toFloat(info[1]));
            float y(1.0f - toFloat(info[2])); // y軸反転

            fileCoord.push_back(uvcoord({x * correctX, y * correctY}));
        }

        // 法線情報
        if (info[0] == "vn") {
            fileNormal.push_back(KVector(toFloat(info[1]), toFloat(info[2]), toFloat(info[3])));
        }

        if (info[0] == "f") { // 表面情報
            for (auto j = info.begin() + 1, j_e(info.end()); j != j_e; ++j) {
                Vector<String> face(split(*j, "/")); // 頂点/テクスチャ/法線
                // 頂点
                objVertex.push_back(fileVertex[toInt(face[0]) - 1]);
                // テクスチャ
                if (texture) {
                    objCoord.push_back(fileCoord[toInt(face[1]) - 1]);
                }
                // 法線
                if (normal) {
                    objNormal.push_back(fileNormal[toInt(face[2]) - 1]);
                }
            }
        }
    }
    if (objNormal.empty()) { // 法線情報の補填(ポリゴンから法線を割り出す)
        for (auto i = objVertex.begin(), i_e(objVertex.end()); i != i_e; i += polySize) {
            KVector v1(*(i + 0)), v2(*(i + 1)), v3(*(i + 2));
            for (int j = 0; j < polySize; ++j) objNormal.push_back((v2 - v1).cross(v3 - v2).normalization());
        }
    }

    mVertex = new KVertexBufferObject<KVector>(objVertex, GL_ARRAY_BUFFER, GL_STREAM_DRAW);
    mCoord = new KVertexBufferObject<uvcoord>(objCoord, GL_ARRAY_BUFFER, GL_STREAM_DRAW);
    mNormal = new KVertexBufferObject<KVector>(objNormal, GL_ARRAY_BUFFER, GL_STREAM_DRAW);

    mTexture.drawImage(
            mTexImage,
            KRect(mTexImage.mWidth, mTexImage.mHeight),
            KVector()
            );
    mTexture.reflect();

    mVertexSize = mVertex->size();
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

    glDrawArrays(mDrawMode, 0, mVertexSize);

    mTexture.bindOFF();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

