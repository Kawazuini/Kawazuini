/**
 * @file   KHandLight.h
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#ifndef KHANDLIGHT_H
#define KHANDLIGHT_H

#include "KLight.h"
#include "KVector.h"

/**
 * @brief  \~english  handy light
 * @brief  \~japanese ハンドライト
 * @author \~ Maeda Takumi
 */
class KHandLight : public KLight {
private:
    /* 拡散光 */ static const float DIFFUSE[3];
    /* 環境光 */ static const float AMBIENT[3];
    /* 鏡面光 */ static const float SPECULAR[3];
public:
    /**
     * @brief \~english  position coordinates of light source
     * @brief \~japanese 光源の位置座標
     */
    KVector mPosition;
    /**
     * @brief \~english  direction of light source
     * @brief \~japanese 光源の向き
     */
    KVector mDirection;

    KHandLight();
    virtual ~KHandLight() = default;

    /**
     * @brief \~english  update information of light source.
     * @brief \~japanese 光源情報を更新します。
     */
    void at();
};

#endif /* KHANDLIGHT_H */

