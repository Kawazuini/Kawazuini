/**
 * @file   KObject.h
 * @brief  KObject
 * @author Maeda Takumi
 */
#ifndef KOBJECT_H
#define KOBJECT_H

#include "KDrawer.h"
#include "KImage.h"
#include "KTexture.h"
#include "KVertexBufferObject.h"

class KFile;

class KObject final : public KDrawer {
private:

    struct uvcoord {
        float x, y;
    };

    struct Index {
        int mVertex = 0;
        int mTexture = 0;
        int mNormal = 0;
    };

    int mVertexSize;
    KVector mCentroid;

    Vector<KVector> mObjectVertex;
    Vector<uvcoord> mObjectCoord;
    Vector<KVector> mObjectNormal;
    Vector<Index> mObjectIndicies;

    KVertexBufferObject<KVector>* mVertex;
    KVertexBufferObject<uvcoord>* mCoord;
    KVertexBufferObject<KVector>* mNormal;

    KImage mTexImage;
    KTexture mTexture;
public:
    GLenum mDrawMode;

    KObject(const KFile& aFile);
    ~KObject();

    void draw() const override;

    void translate(const KVector& aCoordinate);
    void rotate(const KQuaternion& aQuaternion);

    const KVector& centroid() const;
};

#endif /* KOBJECT_H */

