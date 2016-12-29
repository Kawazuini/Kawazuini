/**
 * @file KVector.h
 * @author Maeda Takumi
 */
#ifndef KVECTOR_H
#define KVECTOR_H

#include "KawazuInclude.h"

class KQuaternion;

#define DEPLOYMENT(aVec) (aVec).x, (aVec).y, (aVec).z

class KVector {
public:
    float x; ///< x scalar
    float y; ///< y scalar
    float z; ///< z scalar

    KVector(const float& ax = 0, const float& ay = 0, const float& az = 0);
    KVector(const POINT& aPoint);

    KVector(const KVector& orig) = default;
    virtual ~KVector() = default;

    bool operator==(const KVector& aVec) const;
    bool operator!=(const KVector& aVec) const;
    KVector operator-() const;
    KVector& operator+=(const KVector& aVec);
    KVector& operator-=(const KVector& aVec);
    KVector& operator*=(const float& aTimes);
    KVector& operator/=(const float& aTimes);
    KVector operator+(const KVector& aVec) const;
    KVector operator-(const KVector& aVec) const;
    KVector operator*(const float& aTimes) const;
    KVector operator/(const float& aTimes) const;

    /** @brief 2次元座標に変換 */ operator POINT() const;

    /**
     * @brief ベクトルの長さを計算する
     * @return ベクトルの長さ
     */
    float length() const;
    /**
     * \~japanese
     * @brief  ベクトルの長さの二乗を計算します。
     * @return ベクトルの長さの二乗
     */
    float lengthSquared() const;
    /**
     * @brief 正規化したベクトルを返す
     * @return 正規化したベクトル
     */
    KVector normalization() const;

    /**
     * @brief 内積を計算
     * @param aVec 計算対象
     * @return 内積
     */
    float dot(const KVector& aVec) const;
    /**
     * @brief 外積を計算
     * @param aVec 計算対象
     * @return 外積
     */
    KVector cross(const KVector& aVec) const;

    /**
     * @brief ベクトルに平行な成分を計算する。
     * @param aVec 指定ベクトル
     * @return 平行なベクトル
     */
    KVector extractParallel(const KVector& aVec) const;
    /**
     * @brief ベクトルに垂直な成分を計算する。
     * @param aVec 指定ベクトル
     * @return 垂直なベクトル
     */
    KVector extractVertical(const KVector& aVec) const;

    /**
     * @brief ベクトルを回転させる
     * @param aQuaternion 回転を表すクォータニオン
     * @return 回転結果のベクトル
     */
    KVector rotate(const KQuaternion& aQuaternion) const;

    /**
     * @brief ベクトル同士の角度を計算する。
     * @param aVec 対象となるベクトル
     * @return ベクトル同士の角度
     */
    float angle(const KVector& aVec) const;
    /**
     * @brief ベクトル同士の回転を計算する。
     * @param aVec 対象となるベクトル
     * @return ベクトル同士の回転
     */
    KQuaternion roundAngle(const KVector& aVec) const;

    /**
     * @brief ベクトル内にベクトルをまとめる
     * @param aVec 範囲を表すベクトル
     */
    void fit(const KVector& aVec);
    /** @return 零ベクトルか */ bool isZero() const;
};

#endif /* KVECTOR_H */

