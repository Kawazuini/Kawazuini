/**
 * @file   KFileDialog.h
 * @brief  KFileDialog
 * @author Maeda Takumi
 */
#ifndef KFILEDIALOG_H
#define KFILEDIALOG_H

#include "KUtility.h"

class KWindow;

class KFileDialog {
public:

    struct Filter {
        String mBrief;
        String mFilter;
    };
    using Filters = Vector<Filter>;
private:
    String mPathName;
    String mFileName;
    String mFilter;
    String mCustomFilter;
    String mDefaultExt;

    OPENFILENAME mOfn;
public:
    KFileDialog(
            const KWindow& aWindow,
            const Filters& aFilters,
            const String& aExtension,
            const int& aDefaultIndex = 0
            );
    virtual ~KFileDialog() = default;

    bool open();
    bool save();

    const String& pathName() const;
    const String& fileName() const;
};

#endif /* KFILEDIALOG_H */

