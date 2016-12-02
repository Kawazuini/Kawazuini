/**
 * @file   KDrawer.h
 * @brief  KDrawer
 * @author Maeda Takuni
 */
#ifndef KDRAWER_H
#define KDRAWER_H

#include "KUtility.h"

#include "KNonCopy.h"

/**
 * @brief  \~english  Base for Drawing
 * @brief  \~japanese 描画用基底
 * @author \~ Maeda Takumi
 */
class KDrawer : private KNonCopy {
private:
    /**
     * @brief \~english  list of KDrawer
     * @brief \~japanese KDrawerリスト
     */
    static List<KDrawer*> sDrawers;
protected:
    KDrawer();
    virtual ~KDrawer();
public:

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    virtual void draw() const {
    };
    /**
     * @brief \~english  bulk drawing in list.
     * @brief \~japanese リスト内一括描画。
     */
    static void const DRAW();
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

#endif /* KDRAWER_H */
