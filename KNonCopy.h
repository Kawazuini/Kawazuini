/**
 * @file   KNonCopy.h
 * @brief  KNonCopy
 * @author Maeda Takumi
 */
#ifndef KNONCOPY_H
#define KNONCOPY_H

/**
 * @brief  \~english  base of copy inhibit
 * @brief  \~japanese コピー禁止クラス
 * @author \~ Maeda Takumi
 */
class KNonCopy {
protected:
    KNonCopy() = default;
    virtual ~KNonCopy() = default;
private:
    KNonCopy(const KNonCopy& orig) = delete;
    KNonCopy(KNonCopy&&) = delete;
    KNonCopy& operator=(const KNonCopy& orig) = delete;
    KNonCopy& operator=(KNonCopy&&) = delete;
};

#endif /* KNONCOPY_H */

