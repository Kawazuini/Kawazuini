/**
 * @file   KDrawObject.h
 * @brief  KDrawObject
 * @author Maeda Takumi
 */
#ifndef KDRAWOBJECT_H
#define KDRAWOBJECT_H

#include "KDrawer.h"

/**
 * @brief  \~english  Object for drawing
 * @brief  \~japanese 描画用オブジェクト
 * @author \~ Maeda Takumi
 */
class KDrawObject : public KDrawer {
protected:
    KDrawObject() = default;
    virtual ~KDrawObject() = default;
};

#endif /* KDRAWOBJECT_H */

