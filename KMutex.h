/**
 * @file   KMutex.h
 * @brief  KMutex
 * @author Maeda Takumi
 */
#ifndef KMUTEX_H
#define KMUTEX_H

#include "KUtility.h"

class KMutex {
private:
    pthread_mutex_t mMutex;
public:
    KMutex();
    ~KMutex();

    void lock();
    void unlock();
};

#endif /* KMUTEX_H */

