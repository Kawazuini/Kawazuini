/**
 * @file KUpdater.cpp
 * @author Maeda Takumi
 */
#include "KUpdater.h"

KUpdater::Updaters KUpdater::sUpdaters;

KUpdater::KUpdater() {
    mDelete = false;
    add();
}

KUpdater::~KUpdater() {
    remove();
}

void const KUpdater::UPDATE() {
    int j = 0;

    // push_backで今までのiteratorが崩壊する!!!!!
    for (auto i = sUpdaters.begin(); i != sUpdaters.end(); ++i, ++j) {
        (*i)->update();
        if ((*i)->mDelete) {
            delete *i;
            --j; // iteratorをずらす
            i = sUpdaters.begin() + j;
        }
    }
}

void KUpdater::add() {
    sUpdaters.push_back(this);
}

void KUpdater::remove() {
    for (auto i = sUpdaters.begin(), i_e = sUpdaters.end(); i != i_e; ++i) {
        if (*i == this) {
            sUpdaters.erase(i);
            return;
        }
    }
}

const KUpdater::Updaters& KUpdater::LIST() {
    return sUpdaters;
}

