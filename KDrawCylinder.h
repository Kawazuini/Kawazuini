/**
 * @file   KDrawCylinder.h
 * @brief  KDrawCylinder
 * @author Maeda Takumi
 */
#ifndef KDRAWCYLINDER_H
#define KDRAWCYLINDER_H

#include "KCylinder.h"
#include "KDrawer.h"
#include "KVertexBufferObject.h"

/**
 * @brief  \~english  Cylinder for drawing
 * @brief  \~japanese 描画用円筒
 * @author \~ Maeda Takumi
 */
class KDrawCylinder final : public KDrawer {
private:
    KCylinder mCylinder;
    KVector mDirection;
    int mQuality;
    color mColor;

    KVertexBufferObject<KVector> mVertex;
    KVertexBufferObject<KVector> mNormal;
    KVertexBufferObject<unsigned int> mIndex1;
    KVertexBufferObject<unsigned int> mIndex2;
public:
    KDrawCylinder(
            const KCylinder& aCylinder,
            const int& aQuality,
            const color& aColor
            );
    ~KDrawCylinder() = default;

    void draw() const override;

    void move(const KVector& aMoveAmount);
    void rotate(
            const KQuaternion& aQuaternion,
            const KVector& aOrigin
            );
};

#endif /* KDRAWCYLINDER_H */

