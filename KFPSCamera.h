/**
 * @file KFPSCamera.h
 * @author Maeda Takumi
 */
#ifndef KFPSCAMERA_H
#define KFPSCAMERA_H

#include "KCamera.h"

class KFPSCamera : public KCamera {
private:
    static const KVector BASE_DIRECTION;

    float mVirticalAngle; ///< 垂直視点角度
public:
    KFPSCamera();
    KFPSCamera(const KFPSCamera& orig) = default;
    virtual ~KFPSCamera() = default;


    /**
     * @brief カメラを回転させる
     * @param aVAngle 垂直な回転角
     * @param aHAngle 水平な回転角
     */
    void rotate(const float& aVAngle, const float& aHAngle);

    /**
     * @brief 視点からの指定方向をワールド座標のベクトルへ変換
     * @param aDirection 視点からの指定方向
     */
    KVector convertDirection(const KVector& aVec);
};

#endif /* KFPSCAMERA_H */

