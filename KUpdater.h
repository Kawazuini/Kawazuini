/**
 * @file KUpdater.h
 * @author Maeda Takumi
 */
#ifndef KUPDATER_H
#define KUPDATER_H

#include "KUtility.h"

#include "KNonCopy.h"

class KUpdater : private KNonCopy {
private:
    /** @brief Updaterリスト */ typedef List<KUpdater*> Updaters;
    /** @brief Updaterリスト */ static Updaters sUpdaters;
protected:
    KUpdater();
    virtual ~KUpdater();
public:
    /** @brief 死の宣告(trueの時updateで死ぬ) */ bool mDelete;

    /** @brief 更新処理 */
    virtual void update() {
    };
    /** @brief リスト内一括更新     */ static void const UPDATE();
    /** @brief リストに自分を追加   */ void add();
    /** @brief リストから自分を消す */ void remove();
    /** @return リスト              */ static const Updaters& LIST();
};

#endif /* KUPDATER_H */

