/**
 * @file KDrawer.cpp
 * @author Maeda Takuni
 */
#include "KDrawer.h"
#include "KVector.h"

#include "KVector.h"

KDrawer::Drawers KDrawer::sDrawers;

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

const KDrawer::Drawers& KDrawer::LIST() {
    return sDrawers;
}

