/**
 * @file   KUpdater.cpp
 * @brief  KUpdater
 * @author Maeda Takumi
 */
#include "KUpdater.h"

List<KUpdater*> KUpdater::sUpdaters;

KUpdater::KUpdater() :
mUpdated(false) {
    add();
}

KUpdater::~KUpdater() {
    remove();
}

void const KUpdater::UPDATE() {
    List<KUpdater*> tmp(sUpdaters);
    int size(sUpdaters.size()), currentSize;
    while (!tmp.empty()) {
        tmp.front()->mUpdated = true; // 自殺考慮で事前に書き換える
        tmp.front()->update();
        if (size != (currentSize = sUpdaters.size())) { // リストの増減が起きた
            // 最新状態に上書きし、更新位置を調整する
            size = currentSize;
            tmp = sUpdaters;
            while (!tmp.empty() && tmp.front()->mUpdated) tmp.pop_front();
        } else tmp.pop_front();
    }
    // 更新状態を戻す
    for (KUpdater* i : sUpdaters) i->mUpdated = false;
}

void KUpdater::add() {
    remove(); // 二重追加を防ぐ
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

