/**
 * @file   KTimer.h
 * @brief  KTimer
 * @author Maeda Takumi
 */
#include "KTimer.h"

#include "KUtility.h"

const int KTimer::TIME_DIFF = 9; // グリニッジ標準時から日本の時差
const int KTimer::mDays[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
const int KTimer::mSumDays[2][12] = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
    {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
};

int KTimer::totalDays(const Date& aDate) {
    int year = aDate.mYear - 1;
    int day = year * 365 + year / 4 - year / 100 + year / 400;

    day += mSumDays[leap(aDate.mYear)][aDate.mMonth - 1];
    return day + aDate.mDay;
}

KTimer::Date KTimer::totalToDate(const int& aTotal) {
    int year, month, day;
    // 閏年は366日
    int y_400 = (aTotal - 1) / (365 * 400 + 97); // 400年に97回の閏年
    int tmp = (aTotal - 1) % (365 * 400 + 97);
    if (tmp == 365 * 400 + 96) { // 400年目の閏年12/31
        year = (y_400 + 1) * 400;
        day = 365;
    } else {
        int y_100 = tmp / (365 * 100 + 24); // 100年に24回の閏年
        tmp = tmp % (365 * 100 + 24);
        int y_4 = tmp / (365 * 4 + 1); // 4年に1回の閏年
        tmp = tmp % (365 * 4 + 1);
        int y_1 = tmp / 365; // 閏年じゃない年
        if (y_1 > 3) {// 4年目の閏年12/31
            y_1 = 3;
            day = 365;
        } else day = tmp % 365;
        year = y_400 * 400 + y_100 * 100 + y_4 * 4 + y_1 + 1;
    }

    tmp = leap(year);
    month = 12;
    for (int i = 1; i < month; ++i)
        if (day < mSumDays[tmp][i]) month = i;
    day -= mSumDays[tmp][month - 1] + 1;

    return Date({year, month, day});
}

KTimer::Time KTimer::now() {
    using namespace std::chrono;
    return duration_cast<milliseconds> (system_clock::now().time_since_epoch()).count();
}

String KTimer::nowMinutes() {
    Time milli = now();
    int minutes = (milli / (60 * 1000)) % 60;
    int hours = ((milli / (60 * 60 * 1000)) + TIME_DIFF) % 24;

    std::stringstream stream;
    stream << std::setfill(_T('0')) << std::setw(2) << hours << _T(":") << std::setfill('0') << std::setw(2) << minutes;

    return stream.str();
}

String KTimer::nowDate() {
    using namespace std;

    Date date = {1970, 1, 1}; // 1970/01/01が基準
    int diff = ((now() / (60 * 60 * 1000)) + TIME_DIFF) / 24; // 1970/01/01からの経過日数
    int total = totalDays(date) + diff; // 0001/01/01からの経過日数
    date = totalToDate(total); // 経過に数から日付に変換

    String week;
    switch (total % 7) { // 7で割った余りが曜日(0:sun)
        case 0: week = _T("日");
            break;
        case 1: week = _T("月");
            break;
        case 2: week = _T("火");
            break;
        case 3: week = _T("水");
            break;
        case 4: week = _T("木");
            break;
        case 5: week = _T("金");
            break;
        case 6: week = _T("土");
            break;
    }

    std::stringstream stream;
    stream << setfill('0') << setw(2) << date.mYear % 100
            << _T("/") << setfill(_T('0')) << setw(2) << date.mMonth
            << _T("/") << setfill(_T('0')) << setw(2) << date.mDay
            << _T("(") << week << _T(")");

    return stream.str();
}
