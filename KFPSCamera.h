/**
 * @file   KFPSCamera.h
 * @brief  KFPSCamera
 * @author Maeda Takumi
 */
#ifndef KFPSCAMERA_H
#define KFPSCAMERA_H

#include "KCamera.h"
#include "KUpdater.h"

/**
 * @brief  \~english  camera that can synchronize position and direction
 * @brief  \~japanese 位置と方向を同期できるカメラ
 * @author \~ Maeda Takumi
 */
class KFPSCamera : public KUpdater {
private:
    /* 標準カメラ方向 */ static const KVector BASE_DIRECTION;

    KCamera& mCamera;
    /* 垂直視点角度     */ float mVerticalAngle;
    /* 同期用カメラ位置 */ KVector& mFPSPosition;
    /* 同期用カメラ方向 */ KVector& mFPSDirection;
public:
    KFPSCamera(
            KCamera& aCamera,
            KVector& aPosition,
            KVector& aDirection
            );
    virtual ~KFPSCamera() = default;

    void update() override;

    /**
     * @brief 視点からのベクトル方向に移動する。
     * @param aMovement
     */
    void move(const KVector& aMovement);

    /**
     * @brief カメラを回転させる。
     * @param aVAngle 垂直な回転角
     * @param aHAngle 水平な回転角
     */
    void rotate(const float& aVAngle, const float& aHAngle);

    /**
     * @brief 視点からの指定方向をワールド座標のベクトルへ変換。
     * @param aDirection 視点からの指定方向
     */
    KVector convertDirection(const KVector& aVec);
};

#endif /* KFPSCAMERA_H */

