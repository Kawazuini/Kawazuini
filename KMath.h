/**
 * @file KMath.h
 * @author Maeda Takumi
 * @brief 数学関数
 */
#ifndef KMATH_H
#define KMATH_H

namespace Math {
    /** @brief π */
    static const float PI = 3.141592653589793;
    /** @breif ε */
    static const float EPSILON = 0.00001;

    /** @return 最大値 */
    template <class Type>
    static inline Type max(const Type& aData1, const Type& aData2) {
        return aData1 > aData2 ? aData1 : aData2;
    }

    /** @return 最小値 */
    template <class Type>
    static inline Type min(const Type& aData1, const Type& aData2) {
        return aData1 < aData2 ? aData1 : aData2;
    }

    /** @return 絶対値 */
    template <class Type>
    static inline Type abs(const Type& aData) {
        return 0 < aData ? aData : -aData;
    }

    /** @return 数の符号 */
    template <class Type>
    static inline Type sign(const Type& aData) {
        return !aData ? 0 : 0 < aData ? 1 : -1;
    }

    template <class Type>
    static inline bool approximately(const Type& ideal, const Type& actual) {
        return ideal - EPSILON < actual && actual < ideal + EPSILON;
    }
}

#endif /* KMATH_H */
