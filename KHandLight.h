/**
 * @file   KHandLight.h
 * @brief  KHandLight
 * @author Maeda Takumi
 */
#ifndef KHANDLIGHT_H
#define KHANDLIGHT_H

#include "KLight.h"
#include "KUpdater.h"

class KCamera;

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
    /**
     * \~english
     * @param aPosition  synchronization position  vector
     * @param aDirection synchronization direction vector
     * \~japanese
     * @param aPosition  同期用位置ベクトル
     * @param aDirection 同期用方向ベクトル
     */
    KHandLight(
            const KVector& aPosition,
            const KVector& aDirection
            );
    /// \~english  @param synchronization camera
    /// \~japanese @param 同期用カメラ
    KHandLight(const KCamera& aCamera);
    virtual ~KHandLight() = default;

    void update() override;
};

#endif /* KHANDLIGHT_H */

