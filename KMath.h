/**
 * @file   KMath.h
 * @brief  Header of Math Utility
 * @author Maeda Takumi
 */
#ifndef KMATH_H
#define KMATH_H

namespace Math {
    /** @brief π   */ static const float PI(3.141592653589793);
    /** @brief π/2 */ static const float HALF_PI(PI / 2.0f);
    /** @breif ε   */ static const float EPSILON(0.00001);

    /**
     * \~english
     * @brief  compare arguments and return larger value.
     * @return larger value.
     * \~japanese
     * @brief  引数を比較し、より大きい値を返却します。
     * @return より大きい値
     */
    template <class Type>
    static inline Type max(const Type& aData1, const Type& aData2) {
        return aData1 > aData2 ? aData1 : aData2;
    }

    /**
     * \~english
     * @brief  compare arguments and return smaller value.
     * @return smaller value.
     * \~japanese
     * @brief  引数を比較し、より小さい値を返却します。
     * @return より小さい値
     */
    template <class Type>
    static inline Type min(const Type& aData1, const Type& aData2) {
        return aData1 < aData2 ? aData1 : aData2;
    }

    /**
     * \~english
     * @brief  return absolute value of argument.
     * @return absolute value of argumetn
     * \~japanese
     * @brief  引数の絶対値を返却します。
     * @return 引数の絶対値
     */
    template <class Type>
    static inline Type abs(const Type& aData) {
        return 0 < aData ? aData : -aData;
    }

    /**
     * \~english
     * @brief  return sign of argument.
     * @return sign of argument
     * \~japanese
     * @brief  引数の符号を返却します。
     * @return 引数の符号
     */
    template <class Type>
    static inline Type sign(const Type& aData) {
        return !aData ? 0 : 0 < aData ? 1 : -1;
    }

    /**
     * \~english
     * @brief  determine whether numerical value is included in the error range (ε).
     * @param  ideal  ideal value
     * @param  actual actual value
     * @return whether numerical value is included in the error range
     * \~japanese
     * @brief  数値が誤差範囲内(ε)に含まれているかを判定します。
     * @param  ideal  理論値
     * @param  actual 測定値
     * @return 誤差範囲内に含まれているか
     */
    template <class Type>
    static inline bool approximately(const Type& ideal, const Type& actual) {
        return ideal - EPSILON < actual && actual < ideal + EPSILON;
    }

    template <class Type>
    static inline Type toDegree(const Type& aRadian) {
        return aRadian / PI * 180;
    }

    template <class Type>
    static inline Type toRadian(const Type& aDegree) {
        return aDegree / 180 * PI;
    }
}

#endif /* KMATH_H */

