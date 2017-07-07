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
        const String& aExtension
        ) :
mPathName(MAX_PATH, '\0'),
mFileName(MAX_PATH, '\0'),
mCustomFilter(MAX_PATH, '\0'),
mDefaultExt(W(aExtension)),
mOfn{
    /* size of struct    */ sizeof (OPENFILENAME),
    /* owner    hundle   */ aWindow.mWindow,
    /* instance hundle   */ aWindow.mArgs.mInst,
    /* filter            */ NULL,
    /* selected filter   */ const_cast<char*> (mCustomFilter.data()), MAX_PATH,
    /* default select    */ 0,
    /* file path name    */ const_cast<char*> (mPathName.data()), MAX_PATH,
    /* only file name    */ const_cast<char*> (mFileName.data()), MAX_PATH,
    /* default directory */ NULL,
    /* title of dialog   */ NULL,
    /* flags of dialog   */ OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT,
    /* offset            */ 0, 0,
    /* default extension */ mDefaultExt.data(),
    /* to hook function  */ 0,
    /* hook function     */ NULL,
    /* template name     */ NULL
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

