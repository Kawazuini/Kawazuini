/**
 * @file KNonCopy.h
 * @author Maeda Takumi
 */
#ifndef KNONCOPY_H
#define KNONCOPY_H

class KNonCopy {
protected:
    KNonCopy() = default;
    virtual ~KNonCopy() = default;
private:
    KNonCopy(const KNonCopy& orig) = delete;
    KNonCopy(KNonCopy&&) = delete;
    void operator=(const KNonCopy& orig) = delete;
    KNonCopy& operator=(KNonCopy&&) = delete;
};

#endif /* KNONCOPY_H */

