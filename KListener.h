/**
 * @file   KListener.h
 * @brief  KListener
 * @author Maeda Takumi
 */
#ifndef KLISTENER_H
#define KLISTENER_H

#include "KKeyboard.h"
#include "KMouse.h"

/**
 * @brief  \~english  Event processing system
 * @brief  \~japanese イベント処理システム
 * @author \~ Maeda Takumi
 */
class KListener : private KNonCopy {
    friend class KWindow;
protected:
    KKeyboard mKeyboard;
    KMouse mMouse;

    KListener() = default;
    virtual ~KListener() = default;

private:
    /* Response to drawing request of Window */
    virtual void responsiveDraw() const = 0;
public:

    const KKeyboard& keyboard() const {
        return mKeyboard;
    };

    const KMouse& mosue() const {
        return mMouse;
    };
};

#endif /* KLISTENER_H */

