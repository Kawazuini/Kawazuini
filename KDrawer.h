/**
 * @file   KDrawer.h
 * @brief  KDrawer
 * @author Maeda Takuni
 */
#ifndef KDRAWER_H
#define KDRAWER_H

#include "KNonCopy.h"
#include "KUtility.h"

/**
 * @brief  \~english  Base for Drawing
 * @brief  \~japanese 描画用基底
 * @author \~ Maeda Takumi
 */
class KDrawer : private KNonCopy {
private:
    /* 描画リスト */ static List<KDrawer*> sDrawers;
protected:
    KDrawer();
    virtual ~KDrawer();
public:
    /// @brief \~english  drawing processing
    /// @brief \~japanese 描画処理
    virtual void draw() const = 0;
    /// @brief \~english  bulk drawing in list.
    /// @brief \~japanese リスト内一括描画。
    static void const DRAW();
    /// @brief \~english  add myself to list.
    /// @brief \~japanese リストに自分を追加します。
    void add();
    /// @brief \~english  remove myself form list.
    /// @brief \~japanese リストから自分を消します。
    void remove();
};

#endif /* KDRAWER_H */

