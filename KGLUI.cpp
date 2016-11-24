/**
 * @file KGLUI.cpp
 * @author Maeda Takumi
 */
#include "KGLUI.h"
#include "KWindow.h"

const int KGLUI::WIDTH = 1024;
const int KGLUI::HEIGHT = WIDTH * KWindow::ASPECT;

KGLUI::KGLUI(const KCamera& aCamera) :
mCamera(&aCamera),
mPixel(new color[WIDTH * WIDTH]) {
}

KGLUI::~KGLUI() {
    delete[] mPixel;
}

void KGLUI::draw() const {
}
