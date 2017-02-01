/**
 * @file   KFPSCamera.h
 * @brief  KFPSCamera
 * @author Maeda Takumi
 */
#ifndef KFPSCAMERA_H
#define KFPSCAMERA_H

#include "KCamera.h"
#include "KUpdater.h"

class KFPSCamera : public KCamera, public KUpdater {
private:
    static const KVector BASE_DIRECTION;

    float mVerticalAngle; ///< 垂直視点角度

    KVector& mFPSPosition;
    KVector& mFPSDirection;
public:
    KFPSCamera(
            KVector& aPosition,
            KVector& aDirection
            );
    virtual ~KFPSCamera() = default;

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
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

