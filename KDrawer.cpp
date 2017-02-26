/**
 * @file   KDrawer.cpp
 * @brief  KDrawer
 * @author Maeda Takuni
 */
#include "KDrawer.h"

List<KDrawer*> KDrawer::sDrawers;

KDrawer::KDrawer() {
    add();
}

KDrawer::~KDrawer() {
    remove();
}

void const KDrawer::DRAW() {
    for (KDrawer* i : sDrawers) i->draw();
}

void KDrawer::add() {
    remove(); // 二重追加を防ぐ
    sDrawers.push_back(this);
}

void KDrawer::remove() {
    for (auto i = sDrawers.begin(), i_e = sDrawers.end(); i != i_e; ++i) {
        if (*i == this) {
            sDrawers.erase(i);
            return;
        }
    }
}

