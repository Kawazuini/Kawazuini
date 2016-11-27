/**
 * @file   KCamera.h
 * @brief  KCamera
 * @author Maeda Takumi
 */
#ifndef KCAMERA_H
#define KCAMERA_H

#include "KVector.h"

class KCamera {
public:
    float mAngle; ///< 上下視野角
    float mAspect; ///< 水平視野倍率
    float mNearLimit; ///< 近距離描画限界距離
    float mFarLimit; ///< 遠距離描画限界距離

    KVector mPosition; ///< カメラ位置
    KVector mDirection; ///< カメラ方向
    KVector mHeadSlope; ///< カメラ頭方向

    KCamera();
    KCamera(const KCamera& orig) = default;
    virtual ~KCamera() = default;

    /** @brief 視点の確定 */
    void set();
};

#endif /* KCAMERA_H */

