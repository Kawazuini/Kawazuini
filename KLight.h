/**
 * @file   KLight.h
 * @brief  KLight
 * @author Maeda Takumi
 */
#ifndef KLIGHT_H
#define KLIGHT_H

#include "KNonCopy.h"
#include "KVector.h"

/**
 * @brief  \~english  Lighting System
 * @brief  \~japanese 光源システム
 * @author \~ Maeda Takumi
 */
class KLight : private KNonCopy {
private:
    /* 光源数 */ static int sLightCount;
protected:
    /// @brief \~english  number of light
    /// @brief \~japanese 光源番号
    const int mLightNumber;

    /// @brief \~english  diffuse element of light
    /// @brief \~japanese 光の拡散要素
    float mDiffuse[3];
    /// @brief \~english  ambient element of light
    /// @brief \~japanese 光の環境要素
    float mAmbient[3];
    /// @brief \~english  specular element of light
    /// @brief \~japanese 光の鏡面要素
    float mSpecular[3];

    /// @brief \~english  position coordinates of light source
    /// @brief \~japanese 光源の位置座標
    KVector mPosition;
    /// @brief \~english  direction of light source
    /// @brief \~japanese 光源の向き
    KVector mDirection;

    /// @brief \~english  attenutation rate by distance
    /// @brief \~japanese 距離による減衰率
    float mAttenutation[3]; // constant, linear, quadratic

    /// @brief \~english  cutoff of spot light
    /// @brief \~japanese スポットライトのカットオフ
    float mSpotCutoff;
    /// @brief \~english  attenutation rate from the center of the spotlight
    /// @brief \~japanese スポットライトの中心からの減衰率
    float mSpotExponent;
public:
    KLight();
    virtual ~KLight();

    void setDiffuse(const float& aRed, const float& aGreen, const float& aBlue);
    void setAmbient(const float& aRed, const float& aGreen, const float& aBlue);
    void setSpecular(const float& aRed, const float& aGreen, const float& aBlue);
    void setPosition(const KVector& aPosition);
    void setDirection(const KVector& aDirection);
    void setAttenutation(const float& aConstant, const float& aLinear, const float& aQuadratic);
    void setSpotCutoff(const float& aSpotCutoff);
    void setSpotExponent(const float& aSpotExponent);
    
    const KVector& position() const;
    const KVector& direction() const;
};

#endif /* KLIGHT_H */

