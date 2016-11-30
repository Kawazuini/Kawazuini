/**
 * @file   KUpdater.h
 * @brief  KUpdater
 * @author Maeda Takumi
 */
#ifndef KUPDATER_H
#define KUPDATER_H

#include "KUtility.h"

#include "KNonCopy.h"

/**
 * @brief  \~english  Base for Update
 * @brief  \~japanese 更新用基底
 * @author \~ Maeda Takumi
 */
class KUpdater : private KNonCopy {
private:
    /**
     * @brief \~english  list of KUpdater
     * @brief \~japanese KUpdaterリスト
     */
    static List<KUpdater*> sUpdaters;
    /**
     * @brief \~english  whether updated
     * @brief \~japanese 更新有無
     */
    bool mUpdated;
protected:
    KUpdater();
    virtual ~KUpdater();
public:

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    virtual void update() {
    };
    /**
     * @brief \~english  bulk update in list.
     * @brief \~japanese リスト内一括更新。
     */
    static void const UPDATE();
    /**
     * @brief \~english  add myself to list.
     * @brief \~japanese リストに自分を追加。
     */
    void add();
    /**
     * @brief \~english  erase myself form list.
     * @brief \~japanese リストから自分を消す。
     */
    void erase();
};

#endif /* KUPDATER_H */

