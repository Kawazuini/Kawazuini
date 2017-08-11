/**
 * @file   KUpdater.h
 * @brief  KUpdater
 * @author Maeda Takumi
 */
#ifndef KUPDATER_H
#define KUPDATER_H

#include "KNonCopy.h"
#include "KUtility.h"

/**
 * @brief  \~english  Base for Update
 * @brief  \~japanese 更新用基底
 * @author \~ Maeda Takumi
 */
class KUpdater : private KNonCopy {
private:
    /* 更新リスト */ static List<KUpdater*> sUpdaters;
    /* 更新状態   */ bool mUpdated;
protected:
    KUpdater();
    virtual ~KUpdater();
public:
    /// @brief \~english  update processing
    /// @brief \~japanese 更新処理
    virtual void update() = 0;
    /// @brief \~english  bulk update in list.
    /// @brief \~japanese リスト内一括更新。
    static void const UPDATE();
    /// @brief \~english  add myself to list.
    /// @brief \~japanese リストに自分を追加します。
    void add();
    /// @brief \~english  remove myself form list.
    /// @brief \~japanese リストから自分を消します。
    void remove();
};

#endif /* KUPDATER_H */

