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

    int mVertexSize;

    Vector<String> mObject;

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
};

#endif /* KOBJECT_H */

