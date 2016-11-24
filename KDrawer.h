/**
 * @file KDrawer.h
 * @author Maeda Takumi
 */
#ifndef KDRAWER_H
#define KDRAWER_H

#include "KUtility.h"

#include "KNonCopy.h"

class KWindow;
class KVector;

class KDrawer : private KNonCopy {
private:
    /** @brief Drawerリスト */ typedef List<KDrawer*> Drawers;
    /** @brief Drawerリスト */ static Drawers sDrawers;
protected:
    KDrawer();
    virtual ~KDrawer();
public:

    virtual void draw() {
    };
    /**
     * @brief リスト内一括描画
     * @param aWindow 描画オブジェクト
     * @param aOff オフセット値
     */
    static void const DRAW();
    /** @brief リストに自分を追加   */ void add();
    /** @brief リストから自分を消す */ void remove();
    /** @brief リストを返す         */ static const Drawers& LIST();
};

#endif /* KDRAWER_H */
