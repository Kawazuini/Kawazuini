/**
 * @file KPolygon.h
 * @author Maeda Takumi
 */
#ifndef KPOLYGON_H
#define KPOLYGON_H

#include "KUtility.h"

#include "KVector.h"

class KSegment;

class KPolygon {
public:
    List<KVector> mVertex; /// 頂点リスト
    KVector mNormal; ///< 法線ベクトル

    KPolygon() = default;
    KPolygon(const List<KVector>& aVertex);
    KPolygon(const KPolygon& orig) = default;
    virtual ~KPolygon() = default;
    
    /**
     * @brief 線分との衝突判定を計算する。
     * @param aSegment 対象線分
     * @return 衝突結果
     */
    bool operator*(const KSegment& aSegment);
    
    /**
     * @brief 線分との交差点を計算する。(ポリゴン上にあるとは限りません。)
     * @param aSegment 対象線分
     * @return 交差点
     * @note operator*()で衝突判定を確認してください。
     */
    KVector hitPoint(const KSegment& aSegment);
};

#endif /* KPOLYGON_H */
