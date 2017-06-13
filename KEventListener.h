/**
 * @file   KEventListener.cpp
 * @brief  KEventListener
 * @author Maeda Takumi
 */
#ifndef KEVENTLISTENER_H
#define KEVENTLISTENER_H

#include "KNonCopy.h"

class KEvent;

class KEventListener : private KNonCopy {
protected:
    KEventListener();
    virtual ~KEventListener() = default;
private:
    friend class KEvent;
    virtual void processEvent(KEvent* e) = 0;
};

#endif /* KEVENTLISTENER_H */

