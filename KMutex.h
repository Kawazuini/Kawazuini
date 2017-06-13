/**
 * @file   KMutex.h
 * @brief  KMutex
 * @author Maeda Takumi
 */
#ifndef KMUTEX_H
#define KMUTEX_H

#include "KUtility.h"

/**
 * @brief  \~english  Mutex system
 * @brief  \~japanese 排他処理システム
 * @author \~ Maeda Takumi
 */
class KMutex final {
private:
    /* 排他処理 */ pthread_mutex_t mMutex;
public:
    KMutex();
    ~KMutex();

    /**
     * @brief \~english  lock mutex.
     * @brief \~japanese 排他処理を有効にします。
     */
    void lock();
    /**
     * @brief \~english  unlock mutex.
     * @brief \~japanese 排他処理を無効にします。
     */
    void unlock();
};

#endif /* KMUTEX_H */

