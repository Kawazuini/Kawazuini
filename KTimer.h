/**
 * @file   KTimer.h
 * @brief  KTimer
 * @author Maeda Takumi
 */
#ifndef KTIMER_H
#define KTIMER_H

#include "KawazuInclude.h"

#include "KNonCopy.h"

/**
 * @brief  \~english  Timer
 * @brief  \~japanese 時計
 * @author \~ Maeda Takumi
 */
class KTimer : private KNonCopy {
public:
    /** @brief 時間 */ typedef long long Time;
private:

    /** @brief 日付 */
    typedef struct {
        /** @brief 年 */ int mYear;
        /** @brief 月 */ int mMonth;
        /** @brief 日 */ int mDay;
    } Date;

    /** @brief 時差     */ static const int TIME_DIFF;
    /** @brief 月別日数 */ static const int mDays[2][12];
    /** @brief 累積日数 */ static const int mSumDays[2][12];

    KTimer() = default;
    virtual ~KTimer() = default;

    /** @return 閏年かどうか */
    static inline bool leap(int aYear) {
        return aYear % 4 == 0 && (aYear % 100 != 0 || aYear % 400 == 0);
    }

    /** @return 西暦1年1月1日からの累計日数 */ static int totalDays(const Date& aDate);
    /** @return 累計日数から日付を求める    */ static Date totalToDate(const int& aTotal);
public:
    /** @return 現在時刻(ミリ秒)     */ static Time now();
    /** @return 時間(分まで) ※xx:yy */ static std::string nowMinutes();
    /** @return 日付 ※xx/yy/zz(d)   */ static std::string nowDate();
};

#endif /* KTIMER_H */
