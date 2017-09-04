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
mTexImage(),
mTexture(Math::max(mTexImage.mWidth, mTexImage.mHeight)),
mDrawMode(GL_TRIANGLES) {
    Vector<String> objectFile(aFile.read());

    // 表面情報の確認(ループ外で処理削減)
    int polySize(0);
    bool texture(false), normal(false);
    // 終わりから検索(表面定義は後ろの方にある)
    for (auto i = objectFile.end() - 1, i_e(objectFile.begin());; --i) {
        if (i->at(0) == 'f') {
            Vector<String> info(split(*i, R"(\s)"));
            polySize = info.size() - 1;

            Vector<String> face(split(info[1], "/"));
            int faceSize(face.size());
            if (faceSize >= 2) texture = !face[1].empty();
            if (faceSize >= 3) normal = !face[2].empty();
            break;
        } else if (i == i_e) throw Error("Error of [.obj file]"); // 見つからなかったらエラーを返す。
    }


    // テクスチャサイズの調整
    float iw(mTexImage.mWidth), ih(mTexImage.mHeight);
    float correctX(1.0f), correctY(1.0f);
    if (iw < ih) correctX = iw / ih; // 縦長
    if (iw > ih) correctY = ih / iw; // 横長


    // ファイル読み込み & 変換
    Vector<KVector> deployVertex;
    Vector<uvcoord> deployCoord;
    Vector<KVector> deployNormal;
    for (const String& i : objectFile) {
        Vector<String> info(split(i, R"(\s)"));

        // 頂点情報
        if (info[0] == "v") {
            mObjectVertex.push_back(KVector(toFloat(info[1]), toFloat(info[2]), toFloat(info[3])));
        }

        // テクスチャ情報
        if (info[0] == "vt") {
            float x(toFloat(info[1]));
            float y(1.0f - toFloat(info[2])); // y軸反転

            mObjectCoord.push_back(uvcoord({x * correctX, y * correctY}));
        }

        // 法線情報
        if (info[0] == "vn") {
            mObjectNormal.push_back(KVector(toFloat(info[1]), toFloat(info[2]), toFloat(info[3])));
        }

        if (info[0] == "f") { // 表面情報
            for (auto j = info.begin() + 1, j_e(info.end()); j != j_e; ++j) {
                Vector<String> face(split(*j, "/")); // 頂点/テクスチャ/法線
                Index index;

                // 頂点
                index.mVertex = toInt(face[0]) - 1;
                deployVertex.push_back(mObjectVertex[index.mVertex]);
                // テクスチャ
                if (texture) {
                    index.mTexture = toInt(face[1]) - 1;
                    deployCoord.push_back(mObjectCoord[index.mTexture]);
                }
                // 法線
                if (normal) {
                    index.mNormal = toInt(face[2]) - 1;
                    deployNormal.push_back(mObjectNormal[index.mNormal]);
                }

                mObjectIndicies.push_back(index);
            }
        }
    }
    if (deployNormal.empty()) { // 法線情報の補填(ポリゴンから法線を割り出す)
        for (auto i = deployVertex.begin(), i_e(deployVertex.end()); i != i_e; i += polySize) {
            KVector v1(*(i + 0)), v2(*(i + 1)), v3(*(i + 2));
            for (int j = 0; j < polySize; ++j) deployNormal.push_back((v2 - v1).cross(v3 - v2).normalization());
        }
    }

    mVertex = new KVertexBufferObject<KVector>(deployVertex, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    mCoord = new KVertexBufferObject<uvcoord>(deployCoord, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    mNormal = new KVertexBufferObject<KVector>(deployNormal, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);

    mTexture.drawImage(
            mTexImage,
            KRect(mTexImage.mWidth, mTexImage.mHeight),
            KVector()
            );
    mTexture.reflect();

    mVertexSize = mVertex->size();
    KVector sum;
    for (const KVector& i : mObjectVertex) sum += i;
    mCentroid = sum / mObjectVertex.size();
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

void KObject::translate(const KVector& aCoordinate) {
    KVector move(aCoordinate - mCentroid);
    mCentroid += move;
    for (KVector& i : mObjectVertex) i += move;
    KVector * vertex(mVertex->data());
    auto index(mObjectIndicies.begin());
    for (int i = 0; i < mVertexSize; ++i, ++vertex, ++index) *vertex = mObjectVertex[index->mVertex];
}

void KObject::rotate(const KQuaternion& aQuaternion) {
    for (KVector& i : mObjectVertex) i = (i - mCentroid).rotate(aQuaternion) + mCentroid;
    for (KVector& i : mObjectNormal) i = i.rotate(aQuaternion);

    KVector * vertex(mVertex->data());
    KVector * normal(mNormal->data());
    auto index(mObjectIndicies.begin());
    for (int i = 0; i < mVertexSize; ++i, ++vertex, ++normal, ++index) {
        *vertex = mObjectVertex[index->mVertex];
        *normal = mObjectNormal[index->mNormal];
    }
}

void KObject::resize(const float& aRate) {
    for (KVector& i : mObjectVertex) i = (i - mCentroid) * aRate + mCentroid;
    KVector * vertex(mVertex->data());
    auto index(mObjectIndicies.begin());
    for (int i = 0; i < mVertexSize; ++i, ++vertex, ++index) *vertex = mObjectVertex[index->mVertex];
}

const KVector& KObject::centroid() const {
    return mCentroid;
}

