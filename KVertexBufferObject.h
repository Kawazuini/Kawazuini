/**
 * @file   KVertexBufferObject.h
 * @brief  KVertexBufferObject
 * @author Maeda Takumi
 */
#ifndef KVERTEXBUFFEROBJECT_H
#define KVERTEXBUFFEROBJECT_H

#include "KOpenGL.h"
#include "KUtility.h"

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

    KVertexBufferObject(
            const Vector<Type>& aData,
            const unsigned int& aTarget,
            const unsigned int& aUsage
            ) :
    KVertexBufferObject<Type>(aData.size(), aTarget, aUsage) {
        // メモリに書き込み
        Type * d(data(GL_WRITE_ONLY));
        for (const Type& i : aData) *d++ = i;
    };

    ~KVertexBufferObject() {
        glUnmapBuffer(mTarget);
        glBindBuffer(mTarget, 0);
        glDeleteBuffers(1, &mName);
    };

    Type* data(const GLenum& aAccess = GL_READ_WRITE) const {
        bind();
        return (Type*) glMapBuffer(mTarget, aAccess);
    };

    void bind() const {
        glBindBuffer(mTarget, mName);
        glUnmapBuffer(mTarget);
    };

    const unsigned int size() const {
        return mSize;
    };
};

#endif /* KVERTEXBUFFEROBJECT_H */

