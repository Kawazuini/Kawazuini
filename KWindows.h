/**
 * @file   KWindows.h
 * @brief  Header of Windows Utility
 * @author Maeda Takumi
 */
#ifndef KWINDOWS_H
#define KWINDOWS_H

#include "KUtility.h"

/** @brief メッセージボックスの表示 */
static inline void message(
        const String& aTxt,
        const String& aTitle = "",
        const HWND& aHwnd = NULL,
        const UINT& aFlag = 0
        ) {
    MessageBox(aHwnd, W(aTxt).data(), W(aTitle).data(), aFlag);
}

#endif /* KWINDOWS_H */

