/**
 * @file   KSwitch.h
 * @brief  KSwitch
 * @author Maeda Takumi
 */
#ifndef KSWITCH_H
#define KSWITCH_H

/**
 * @brief \~english  switch
 * @brief \~japanese スイッチ
 * @author \~ Maeda Takumi
 */
class KSwitch {
private:
    /** @brief ON / OFF      */ bool mSwitch;
    /** @brief ONフレーム数  */ int mOnFrame;
    /** @brief OFFフレーム数 */ int mOffFrame;
public:
    KSwitch();
    KSwitch(const KSwitch& orig) = default;
    virtual ~KSwitch() = default;

    /** @brief ON状態に遷移   */ void ON();
    /** @brief OFF状態に遷移  */ void OFF();
    /** @brief 時間をカウント */ void pass();

    /** @return ON状態開始からのフレーム数  */ int onFrame() const;
    /** @return OFF状態開始からのフレーム数 */ int offFrame() const;
    /**
     * @return 押されているか
     * @note ON開始時一度のみ
     */
    bool isTouch() const;
};

#endif /* KSWITCH_H */
