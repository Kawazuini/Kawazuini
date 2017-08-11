/**
 * @file   KMutex.cpp
 * @brief  KMutex
 * @author Maeda Takumi
 */
#include "KMutex.h"

KMutex::KMutex() {
    pthread_mutex_init(&mMutex, nullptr);
    pthread_mutex_lock(&mMutex);
}

KMutex::~KMutex() {
    pthread_mutex_destroy(&mMutex);
}

void KMutex::lock() {
    pthread_mutex_lock(&mMutex);
}

void KMutex::unlock() {
    pthread_mutex_unlock(&mMutex);
}

