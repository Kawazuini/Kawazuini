/**
 * @file   KDrawSphere.h
 * @brief  KDrawSphere
 * @author Maeda Takumi
 */
#ifndef KDRAWSPHERE_H
#define KDRAWSPHERE_H

#include "KDrawer.h"
#include "KSphere.h"
#include "KVector.h"
#include "KVertexBufferObject.h"

/**
 * @brief  \~english  Sphere for drawing
 * @brief  \~japanese 描画用球体
 * @author \~ Maeda Takumi
 */
class KDrawSphere final : public KDrawer {
private:
    static const int SURFACE_POINT = 3;

    /* 球体情報   */ KSphere mSphere;
    /* 水平分割数 */ int mStack;
    /* 垂直分割数 */ int mSlice;
    int mVertexSize;
    int mIndexSize;

    KVertexBufferObject<KVector> mVertex;
    KVertexBufferObject<KVector> mNormal;
    KVertexBufferObject<unsigned int[SURFACE_POINT] > mIndex;
public:
    /// @brief \~english  color for drawing
    /// @brief \~japanese 描画色    
    color mColor;

    KDrawSphere(
            const KSphere& aSphere,
            const int& aStack,
            const int& aSlice,
            const color& aColor = 0xffffffff,
            const int& aInner = 1
            );
    ~KDrawSphere() = default;

    void draw() const override;

    virtual void translate(const KVector& aVec);
    void rotate(const KQuaternion& aQuater);
};

#endif /* KDRAWSPHERE_H */

