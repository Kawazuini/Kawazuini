/**
 * @file   KCamera.h
 * @brief  KCamera
 * @author Maeda Takumi
 */
#ifndef KCAMERA_H
#define KCAMERA_H

#include "KUtility.h"
#include "KVector.h"
#include "KWindow.h"

/**
 * @brief  \~english  Camera
 * @brief  \~japanese カメラ
 * @author \~ Maeda Takumi
 */
class KCamera {
    friend class KFPSCamera;
public:
    /**
     * @brief \~english  vector up to 4 corners of the drawing area 1m ahead from the viewpoint
     * @brief \~japanese 視点から1m先の描画領域4隅までのベクトル
     */
    using ViewCorner = KVector[4];
    /**
     * @brief \~english  default view angle
     * @brief \~japanese 初期視野角
     */
    static const float DEFAULT_VIEWANGLE;
private:
    const KWindow& mWindow;

    /* 描画視点位置 */ static KVector sPosition;
    /* 描画視野方向 */ static KVector sDirection;
    /* 描画視野角   */ static float sAngle;
    /* 描画領域     */ static ViewCorner sViewCorner;

    struct CameraOption {
        float mAngle;
        float mAspect;
        float mNearLimit;
        float mFarLimit;
    } mOption;

    struct CameraInformation {
        KVector mPosition;
        KVector mDirection;
        KVector mHeadSlope;
    } mInformation;

    KVector mWidth;
    KVector mHeight;
public:
    KCamera(const KWindow& aWindow);
    virtual ~KCamera() = default;

    /**
     * @brief \~english  update view
     * @brief \~japanese 視点の更新
     */
    void set();

    void translate(const KVector& aPosition);
    void zoom(const float& aScale);

    /**
     * \~english
     * @brief  determine the necessity of drawing from normal.
     * @param  aNormal normal of target polygon
     * @return necessity of drawing
     * \~japanese
     * @brief  法線から描画の必要性を判定します。
     * @param  aNormal 対象ポリゴンの法線
     * @return 描画の必要性
     */
    static bool isInCamera(const KVector& aNormal);
    /**
     * \~english
     * @brief  determine the necessity of drawing from vertex.
     * @param  aVertex vertex of target polygon
     * @return necessity of drawing
     * \~japanese
     * @brief  頂点から描画の必要性を判定します。
     * @param  aVertex 対象ポリゴンの頂点
     * @return 描画の必要性
     */
    static bool isInCamera(const Vector<KVector>& aVertex);

    /**
     * \~english
     * @brief  get four corners of the drawing area.
     * @return four corners of the drawing area
     * \~japanese
     * @brief  描画領域の4隅を取得します。
     * @return 描画領域の4隅
     */
    static const ViewCorner& viewCorner();

    const KWindow& window() const;

    const KVector& position() const;
    const KVector& direction() const;

    const KVector& width() const;
    const KVector& height() const;

    static const KVector& Position();
    static const KVector& Direction();
};

#endif /* KCAMERA_H */

