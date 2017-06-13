/**
 * @file   KSegment.h
 * @brief  KSegment
 * @author Maeda Takumi
 */
#ifndef KSEGMENT_H
#define KSEGMENT_H

#include "KVector.h"

/**
 * @brief  \~english  Directed Segment for collision determination
 * @brief  \~japanese 衝突判定用有向線分
 * @author \~ Maeda Takumi
 */
class KSegment {
public:
    /**
     * @brief \~english  line start
     * @brief \~japanese 線分始端
     */
    KVector mVec1;
    /**
     * @brief \~english  line termination
     * @brief \~japanese 線分終端
     */
    KVector mVec2;

    KSegment() = default;
    /**
     * \~english
     * @param aVec1 line start
     * @param aVec2 line termination
     * \~japanese
     * @param aVec1 線分始端
     * @param aVec2 線分終端
     */
    KSegment(const KVector& aVec1, const KVector& aVec2);
    virtual ~KSegment() = default;

    /**
     * \~english
     * @brief  get length of segment.
     * @return length of segment
     * \~japanese
     * @brief  線分の長さを取得します。
     * @return 線分の長さ
     */
    float length() const;
    /**
     * \~english
     * @brief  get direction of directed segment.
     * @return direction of directed segment
     * \~japanese
     * @brief  有向線分の向きを取得します。
     * @return 有向線分の向き
     */
    KVector direction() const;
};

#endif /* KSEGMENT_H */

