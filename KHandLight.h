/**
 * @file   KHandLight.h
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#ifndef KHANDLIGHT_H
#define KHANDLIGHT_H

#include "KLight.h"
#include "KUpdater.h"

/**
 * @brief  \~english  handy light
 * @brief  \~japanese ハンドライト
 * @author \~ Maeda Takumi
 */
class KHandLight : public KLight, private KUpdater {
private:
    /* 同期用位置ベクトル */ const KVector& mHandPosition;
    /* 同期用方向ベクトル */ const KVector& mHandDirection;
public:
    KHandLight(
            const KVector& aPosition,
            const KVector& aDirection
            );
    virtual ~KHandLight() = default;

    void update() override;
};

#endif /* KHANDLIGHT_H */

