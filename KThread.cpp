/**
 * @file   KThread.cpp
 * @brief  KThread
 * @author Maeda Takumi
 */
#include "KThread.h"

KThread::KThread(const ThreadFunction& aFunction, void* args) :
mThreadFunction(aFunction) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, nullptr);
    pthread_create(&mThread, nullptr, mThreadFunction, args);
}

KThread::~KThread() {
    stop();
}

void KThread::join() {
    pthread_join(mThread, nullptr);
}

void KThread::detach() {
    pthread_detach(mThread);
}

void KThread::stop() {
    pthread_cancel(mThread);
    pthread_join(mThread, nullptr);
}

