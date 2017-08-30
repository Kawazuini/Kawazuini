/**
 * @file   KFileDialog.cpp
 * @brief  KFileDialog
 * @author Maeda Takumi
 */
#include "KFileDialog.h"

#include "KWindow.h"

KFileDialog::KFileDialog(
        const KWindow& aWindow,
        const Filters& aFilters,
        const String& aExtension,
        const int& aDefaultIndex
        ) :
mPathName(MAX_PATH, '\0'),
mFileName(MAX_PATH, '\0'),
mCustomFilter(MAX_PATH, '\0'),
mDefaultExt(W(aExtension)),
mOfn{
    /* size of struct    */ sizeof (OPENFILENAME),
    /* owner    hundle   */ aWindow.mWindow,
    /* instance hundle   */ aWindow.mArgs.mInst,
    /* filter            */ nullptr,
    /* selected filter   */ const_cast<char*> (mCustomFilter.data()), MAX_PATH,
    /* default select    */ DWORD(aDefaultIndex),
    /* file path name    */ const_cast<char*> (mPathName.data()), MAX_PATH,
    /* only file name    */ const_cast<char*> (mFileName.data()), MAX_PATH,
    /* default directory */ nullptr,
    /* title of dialog   */ nullptr,
    /* flags of dialog   */ OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT,
    /* offset            */ 0, 0,
    /* default extension */ mDefaultExt.data(),
    /* to hook function  */ 0,
    /* hook function     */ nullptr,
    /* template name     */ nullptr
}
{
    for (Filter i : aFilters) {
        mFilter += W(i.mBrief) + '\0' + W(i.mFilter) + '\0';
    }
    mFilter += '\0';
    mOfn.lpstrFilter = mFilter.data();
}

bool KFileDialog::open() {
    return GetOpenFileName(&mOfn);
}

bool KFileDialog::save() {
    return GetSaveFileName(&mOfn);
}

const String& KFileDialog::pathName() const {
    return mPathName;
}

const String& KFileDialog::fileName() const {
    return mFileName;
}

