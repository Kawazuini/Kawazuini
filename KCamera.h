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
    static KVector sPosition;
    static KVector sDirection;
    static KVector sDirection_UL;
    static KVector sDirection_UR;
    static KVector sDirection_DL;
    static KVector sDirection_DR;

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

    /***/
    static inline bool checkHidden(const KVector& aNormal) {
        return aNormal.dot(KCamera::sDirection_UL - KCamera::sPosition) <= 0
                || aNormal.dot(KCamera::sDirection_UR - KCamera::sPosition) <= 0
                || aNormal.dot(KCamera::sDirection_DL - KCamera::sPosition) <= 0
                || aNormal.dot(KCamera::sDirection_DR - KCamera::sPosition) <= 0;
    };
};

#endif /* KCAMERA_H */

