/**
 * @file   KVertexBufferObject.h
 * @brief  KVertexBufferObject
 * @author Maeda Takumi
 */
#ifndef KVERTEXBUFFEROBJECT_H
#define KVERTEXBUFFEROBJECT_H

#include "KDrawer.h"
#include "KUpdater.h"
#include "KUtility.h"
#include "KOpenGL.h"

template <class Type>
class KVertexBufferObject final {
private:
    unsigned int mName;
    unsigned int mSize;
    unsigned int mTarget;
public:

    KVertexBufferObject(
            const unsigned int& aSize,
            const unsigned int& aTarget,
            const unsigned int& aUsage
            ) :
    mSize(aSize),
    mTarget(aTarget) {
        // メモリの確保
        glGenBuffers(1, &mName);
        glBindBuffer(mTarget, mName);
        glBufferData(mTarget, mSize * sizeof (Type), nullptr, aUsage);
    };

    ~KVertexBufferObject() {
        glDeleteBuffers(1, &mName);
    };

    Type* data() const {
        bind();
        return (Type*) glMapBuffer(mTarget, GL_READ_WRITE);
    };

    void bind() const {
        glUnmapBuffer(mTarget);
        glBindBuffer(mTarget, mName);
    };

    const unsigned int size() const {
        return mSize;
    };
};

#endif /* KVERTEXBUFFEROBJECT_H */

