/**
 * @file   KCamera.h
 * @brief  KCamera
 * @author Maeda Takumi
 */
#ifndef KCAMERA_H
#define KCAMERA_H

#include "KNonCopy.h"
#include "KUtility.h"
#include "KVector.h"

class KQuaternion;
class KWindow;

/**
 * @brief  \~english  Camera
 * @brief  \~japanese カメラ
 * @author \~ Maeda Takumi
 */
class KCamera : private KNonCopy {
    friend class KFPSCamera;
public:
    /// @brief \~english  vector up to 4 corners of the drawing area 1m ahead from the viewpoint
    /// @brief \~japanese 視点から1m先の描画領域4隅までのベクトル
    using ViewCorner = KVector[4];
    /// @brief \~english  default view angle
    /// @brief \~japanese 初期視野角
    static const float DEFAULT_VIEWANGLE;
private:
    /* 描画対象のウィンドウ */ const KWindow& mWindow;
    /* 描画領域             */ ViewCorner mViewCorner;

    /* カメラ設定 */
    struct CameraOption {
        float mAngle;
        float mAspect;
        float mNearLimit;
        float mFarLimit;
    } mOption;

    /* カメラ情報 */
    struct CameraInformation {
        KVector mPosition;
        KVector mDirection;
        KVector mHeadSlope;
    } mInformation;

    /* 描画領域の横幅の半分 */ KVector mHalfWidth;
    /* 描画領域の縦幅の半分 */ KVector mHalfHeight;
public:
    /**
     * @param \~english  aWindow window for drawing
     * @param \~japanese aWindow 描画を行うウィンドウ
     */
    KCamera(const KWindow& aWindow);
    virtual ~KCamera() = default;

    /**
     * @brief \~english  update view.
     * @brief \~japanese 視点を更新します。
     */
    void set();
    /**
     * \~english
     * @brief translate new camera position.
     * @param aPosition new camera position
     * \~japanese
     * @brief カメラ位置を変更します。
     * @param aPosition 新しいカメラ位置
     */
    void translate(const KVector& aPosition);
    /**
     * \~english
     * @brief rotate the view direction.
     * @param aQuaternion rotation information
     * \~japanese
     * @brief 視点方向を回転させます。
     * @param aQuaternion 回転情報
     */
    void rotate(const KQuaternion& aQuaternion);
    /**
     * \~english
     * @brief change the zoom magnification of the camera
     * @param aScale change magnification
     * \~japanese
     * @brief カメラのズーム倍率を変更します。
     * @param aScale 変更倍率
     */
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
    bool isInCamera(const KVector& aNormal) const;
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
    bool isInCamera(const Vector<KVector>& aVertex) const;

    const KWindow& window() const;
    const ViewCorner& viewCorner() const;
    const KVector& position() const;
    const KVector& direction() const;
    const KVector& headslope() const;    
    const KVector& halfWidth() const;
    const KVector& halfHeight() const;
};

#endif /* KCAMERA_H */

