/**
 * @file   KThread.cpp
 * @brief  KThread
 * @author Maeda Takumi
 */
#include "KThread.h"

KThread::KThread(const ThreadFunction& aFunction) :
mThreadFunction(aFunction) {
    int tmp;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &tmp);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &tmp);
}

KThread::~KThread() {
    stop();
}

void KThread::join(void* arg) {
    pthread_create(&mThread, NULL, mThreadFunction, arg);
    pthread_join(mThread, NULL);
}

void KThread::detach(void* arg) {
    pthread_create(&mThread, NULL, mThreadFunction, arg);
    pthread_detach(mThread);
}

void KThread::stop() {
    pthread_cancel(mThread);
}

