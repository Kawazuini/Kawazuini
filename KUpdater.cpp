/**
 * @file   KUpdater.cpp
 * @brief  KUpdater
 * @author Maeda Takumi
 */
#include "KUpdater.h"

List<KUpdater*> KUpdater::sUpdaters;

KUpdater::KUpdater() {
    mUpdated = false;
    add();
}

KUpdater::~KUpdater() {
    erase();
}

void const KUpdater::UPDATE() {
    // listの増減で今までのiteratorが崩壊する!!!!!
    int pSize = sUpdaters.size();
    for (auto i = sUpdaters.begin(), i_e = sUpdaters.end(); i != i_e;) {
        (*i)->update();
        (*i)->mUpdated = true;
        if (pSize != sUpdaters.size()) { // 削除 or 追加が行われた。
            pSize = sUpdaters.size();
            i = sUpdaters.begin();
            i_e = sUpdaters.end();
            for (; i != i_e; ++i) {
                if (!(*i)->mUpdated) { // 続きを探す。
                    break;
                }
            }
            continue;
        }
        ++i;
    }

    // 更新有無をもとに戻す。
    for (KUpdater* i : sUpdaters) i->mUpdated = false;
}

void KUpdater::add() {
    sUpdaters.push_back(this);
}

void KUpdater::erase() {
    for (auto i = sUpdaters.begin(), i_e = sUpdaters.end(); i != i_e; ++i) {
        if (*i == this) {
            sUpdaters.erase(i);
            return;
        }
    }
}

