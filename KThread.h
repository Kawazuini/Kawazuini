/**
 * @file   KThread.h
 * @brief  KThread
 * @author Maeda Takumi
 */
#ifndef KTHREAD_H
#define KTHREAD_H

#include "KUtility.h"

class KThread {
private:
    using ThreadFunction = void* (*)(void*);

    pthread_t mThread;
    ThreadFunction mThreadFunction;
public:
    KThread(const ThreadFunction& aFunction);
    ~KThread();

    void join(void* arg = NULL);
    void detach(void* arg = NULL);
    void stop();
};

#endif /* KTHREAD_H */

