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
    /**
     * @brief \~english  default view angle
     * @brief \~japanese 初期視野角
     */
    static const float DEFAULT_ANGLE;

    /**
     * @brief \~english  
     * @brief \~japanese 
     */
    static KVector sDirection_UL;
    /**
     * @brief \~english  
     * @brief \~japanese 
     */
    static KVector sDirection_UR;
    /**
     * @brief \~english  
     * @brief \~japanese 
     */
    static KVector sDirection_DL;
    /**
     * @brief \~english  
     * @brief \~japanese 
     */
    static KVector sDirection_DR;

    float mAngle; ///< 上下視野角
    float mAspect; ///< 水平視野倍率
    float mNearLimit; ///< 近距離描画限界距離
    float mFarLimit; ///< 遠距離描画限界距離

    KVector mPosition; ///< カメラ位置
    KVector mDirection; ///< カメラ方向
    KVector mHeadSlope; ///< カメラ頭方向

    KCamera();
    virtual ~KCamera() = default;

    /**
     * @brief \~english  update view
     * @brief \~japanese 視点の更新
     */
    void set();

    /**
     * \~english
     * @brier  determine the necessity of drawing from normals.
     * @param  aNormal normal of target polygon
     * @return necessity of drawing
     * \~japanese
     * @brier  法線から描画の必要性を判定します。
     * @param  aNormal 対象ポリゴンの法線
     * @return 描画範囲の必要性
     */
    static inline bool checkHidden(const KVector& aNormal) {
        return aNormal.dot(KCamera::sDirection_UL) <= 0
                || aNormal.dot(KCamera::sDirection_UR) <= 0
                || aNormal.dot(KCamera::sDirection_DL) <= 0
                || aNormal.dot(KCamera::sDirection_DR) <= 0;
    };
};

#endif /* KCAMERA_H */

