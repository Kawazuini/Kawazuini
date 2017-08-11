/**
 * @file   KThread.h
 * @brief  KThread
 * @author Maeda Takumi
 */
#ifndef KTHREAD_H
#define KTHREAD_H

#include "KUtility.h"

/**
 * @brief  \~english  Thread system
 * @brief  \~japanese スレッドシステム
 * @author \~ Maeda Takumi
 */
class KThread final {
private:
    /* スレッド用関数 */ using ThreadFunction = void* (*)(void*);

    /* スレッド       */ pthread_t mThread;
    /* スレッド用関数 */ ThreadFunction mThreadFunction;
public:
    /**
     * \~english
     * @param aFunction functions handled by thread
     * @param args      arguments to pass to the function
     * \~japanese
     * @param aFunction スレッドで処理する関数
     * @param args      関数に渡す引数
     */
    KThread(const ThreadFunction& aFunction, void* args = nullptr);
    ~KThread();

    /**
     * @brief \~english  join thread process.
     * @brief \~japanese スレッド処理を合流させます。
     */
    void join();
    /**
     * @brief \~english  detach thread process.
     * @brief \~japanese スレッド処理を切り離します。
     */
    void detach();
    /**
     * @brief \~english  stop thread.
     * @brief \~japanese スレッドを終了させます。
     */
    void stop();
};

#endif /* KTHREAD_H */

