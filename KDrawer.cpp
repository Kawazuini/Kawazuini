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
    erase();
}

void const KDrawer::DRAW() {
    for (KDrawer* i : sDrawers) i->draw();
}

void KDrawer::add() {
    sDrawers.push_back(this);
}

void KDrawer::erase() {
    for (auto i = sDrawers.begin(), i_e = sDrawers.end(); i != i_e; ++i) {
        if (*i == this) {
            sDrawers.erase(i);
            return;
        }
    }
}

