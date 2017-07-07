/**
 * @file   KEvent.h
 * @brief  KEvent
 * @author Maeda Takumi
 */
#ifndef KEVENT_H
#define KEVENT_H

#include "KUpdater.h"
#include "KUtility.h"

class KEventListener;

class KEvent : protected KUpdater {
protected:
    List<KEventListener*> mListeners;
    String mActionCommand;

    KEvent();
    virtual ~KEvent() = default;
private:
    void update() override;
    virtual bool condition() const = 0;
public:
    addEventListener(KEventListener* aListener);

    const String& actionCommand() const;
};

#endif /* KEVENT_H */

