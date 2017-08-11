/**
 * @file   KUtility.h
 * @brief  Header of Utility
 * @author Maeda Takumi
 */
#ifndef KUTILITY_H
#define KUTILITY_H

#include "KVector.h"
#include "KMath.h"

/**
 * @brief 32bitで表される色情報(ARGB)。
 * @note  先頭の8bitから順にアルファ、赤、緑、青の値を持つ。
 * @note  "Color"は<gdipluscolor.h>のColorクラスと被る。
 */
using color = unsigned long;
using Error = std::runtime_error;
using Regex = std::regex;
using String = std::string;
using StringStream = std::stringstream;
using Time = long long;
using TypeID = std::type_info;
template <class KeyType, class Type> using HashMap = std::unordered_map<KeyType, Type>;
template <class Type> using List = std::list<Type>;
template <class Type> using Queue = std::queue<Type>;
template <class Type> using Stack = std::stack<Type>;
template <class Type> using Vector = std::vector<Type>;

/** @brief 標準出力 */
template <class Type>
static inline void print(const Type& aData) {
    std::cout << aData << std::flush;
}

/** @brief 標準出力(改行) */
template <class Type>
static inline void println(const Type& aData) {
    std::cout << aData << std::endl;
}

/** @brief 標準出力(改行) ※引数を返す */
template <class Type>
static inline Type printWrap(const Type& aData) {
    std::cout << aData << std::endl;
    return aData;
}

/** @brief 数値を文字列に変換 */
template <class Type>
static inline String toString(const Type& aSrc) {
    return std::to_string(aSrc);
}

/**
 * @brief 文字列を整数値に変換する
 * @param aBase 基数(def = 10)
 */
static inline int toInt(const String& aSrc, const int& aBase = 10) {
    if (aSrc.empty()) return 0;
    return strtol(aSrc.data(), nullptr, aBase);
}

static inline color toColor(const String& aSrc) {
    if (aSrc.empty()) return 0;
    return strtoul(aSrc.data(), nullptr, 16);
}

/** @brief 文字列を実数値に変換する */
static inline float toFloat(const String& aSrc) {
    if (aSrc.empty()) return 0;
    return atof(aSrc.data());
}

static inline Vector<String> split(const String& aSrc, const Regex& aRegex) {
    std::sregex_token_iterator first(aSrc.begin(), aSrc.end(), aRegex, -1);
    std::sregex_token_iterator last;
    return Vector<String>(first, last);
}

/**
 * @brief  指定文字列で文字列を分割(指定文字列は含まれない)
 * @param  aSrc 分割する文字列
 * @param  aSep 分割に使用する文字列
 * @return 分割した文字列のリスト
 */
static inline Vector<String> split(const String& aSrc, const String& aSep) {
    Regex regex(aSep);
    return split(aSrc, regex);
}

static inline Vector<String> split(const String& aSrc, const int& aLength) {
    Vector<String> list;
    for (int i = 0, i_e(aSrc.size()); i < i_e; i += aLength) {
        list.push_back(aSrc.substr(i, aLength));
    }
    return list;
}

/** 
 * @brief 文字列のコピー 
 * @note  strlcopyの自作(MinGWでは使えないため)
 */
static inline void stringCopy(char* aDist, const char* aSrc, const int& aSize) {
    char* d(aDist);
    const char* s(aSrc);

    int i(0);
    for (; i < aSize; ++i, ++d) {
        if (*s) *d = *s++;
        else {
            *d = 0;
            break;
        }
    }
    *(aDist + i) = '\0'; // 最終文字をNULLに
};

/** @brief エンコーディングの変換 : UTF8 -> ShiftJIS */
static inline String W(const String& aSrc) {
    int size(aSrc.size());
    const char* data(aSrc.data());
    int lengthUnicode(MultiByteToWideChar(CP_UTF8, 0, data, size + 1, nullptr, 0)); // Unicodeへ変換後の文字列長を得る
    wchar_t* bufUnicode(new wchar_t[lengthUnicode]); // 必要な分だけUnicode文字列のバッファを確保
    MultiByteToWideChar(CP_UTF8, 0, data, size + 1, bufUnicode, lengthUnicode); // UTF8からUnicodeへ変換

    int lengthSJis(WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, nullptr, 0, nullptr, nullptr)); // ShiftJISへ変換後の文字列長を得る
    char* bufShiftJis(new char[lengthSJis]); // 必要な分だけShiftJIS文字列のバッファを確保
    WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lengthUnicode + 1, bufShiftJis, lengthSJis, nullptr, nullptr); // UnicodeからShiftJISへ変換

    String strSJis(bufShiftJis);

    delete[] bufUnicode;
    delete[] bufShiftJis;

    return strSJis;
}

/** @brief エンコーディングの変換 : ShiftJIS -> UTF8 */
static inline String P(const String& aSrc) {
    int size(aSrc.size());
    const char* data(aSrc.data());

    int lengthUnicode(MultiByteToWideChar(CP_THREAD_ACP, 0, data, size + 1, nullptr, 0)); // Unicodeへ変換後の文字列長を得る
    wchar_t* bufUnicode(new wchar_t[lengthUnicode]); // 必要な分だけUnicode文字列のバッファを確保
    MultiByteToWideChar(CP_THREAD_ACP, 0, data, size + 1, bufUnicode, lengthUnicode); // ShiftJISからUnicodeへ変換

    int lengthUTF8(WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, nullptr, 0, nullptr, nullptr)); // UTF8へ変換後の文字列長を得る
    char* bufUTF8(new char[lengthUTF8]); // 必要な分だけUTF8文字列のバッファを確保
    WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lengthUnicode + 1, bufUTF8, lengthUTF8, nullptr, nullptr); // UnicodeからUTF8へ変換

    String strUTF8(bufUTF8);

    delete[] bufUnicode;
    delete[] bufUTF8;
    return strUTF8;
}

static inline Time now() {
    using namespace std::chrono;
    return duration_cast<milliseconds> (system_clock::now().time_since_epoch()).count();
}

static inline String dateString() {
    time_t t(time(nullptr));
    const tm * lt(localtime(&t));

    StringStream ss;
    ss << std::put_time(lt, "%Y") << "/";
    ss << std::put_time(lt, "%m") << "/";
    ss << std::put_time(lt, "%d");
    ss << "(" << std::put_time(lt, "%a") << ")";
    return ss.str();
}

static inline String timeString() {
    time_t t(time(nullptr));
    const tm * lt(localtime(&t));

    StringStream ss;
    ss << std::put_time(lt, "%H") << ":";
    ss << std::put_time(lt, "%M") << ":";
    ss << std::put_time(lt, "%S");
    return ss.str();
}

/**
 * @brief 乱数の生成
 * @param aMax 乱数の上限
 * @return 0_[aMax - 1]の整数
 */
static inline int random(const int& aMax) {
    using namespace std;
    /* 疑似乱数生成機   */ static mt19937 engine(now());
    /* 乱数フォーマット */ static uniform_int_distribution<> dist(0, 0xfffffff);

    return dist(engine) % aMax;
}

/**
 * \~english
 * @brief 
 * @param aId
 * @return 
 * \~japanese
 * @brief  リソースから文字列を読み込みます。
 * @param  aId リソースID
 * @return 読み込んだ文字列(UTF8に変換済み)
 * @note   リソースはShiftJISでしか読み込めない(検証済み(環境によるかも?))
 * @note    最大で1024文字しか読み込めない
 */
static inline String loadString(const int& aId) {
    static const int LOAD_SIZE(1024);
    TCHAR str[LOAD_SIZE];
    LoadString(GetModuleHandle(nullptr), aId, str, LOAD_SIZE);
    return P(str);
}

/**
 * @brief リソースIDから連続して文字列を読み込む
 * @param aNum 読み込む文字列の数
 */
static inline Vector<String> loadStrings(const int& aId, const int& aNum) {
    Vector<String> list;
    for (int i = aId, i_e(aId + aNum); i < i_e; ++i) {
        list.push_back(loadString(i));
    }
    return list;
}

static inline color ARGB(
        const byte& A,
        const byte& R,
        const byte& G,
        const byte& B
        ) {
    return A << 24 | R << 16 | G << 8 | B << 0;
}

static inline Vector<byte> ARGB(const color& aColor) {
    Vector<byte> elem(4);
    elem[0] = (aColor & 0xff000000) >> 24; // A
    elem[1] = (aColor & 0x00ff0000) >> 16; // R
    elem[2] = (aColor & 0x0000ff00) >> 8; // G
    elem[3] = (aColor & 0x000000ff) >> 0; // B

    return elem;
}

static inline void glColor(const color& aColor) {
    glColor4ub(
            (aColor & 0x00ff0000) >> 16, // R
            (aColor & 0x0000ff00) >> 8, // G
            (aColor & 0x000000ff) >> 0, // B            
            (aColor & 0xff000000) >> 24 // A
            );
}

static inline void glVertex(const KVector& aVertex) {
    glVertex3f(DEPLOY_VEC(aVertex));
}

static inline void glNormal(const KVector& aNormal) {
    glNormal3f(DEPLOY_VEC(aNormal));
}

static inline color mix(
        const color& aColor1,
        const color& aColor2
        ) {
    Vector<byte> color1(ARGB(aColor1));
    Vector<byte> color2(ARGB(aColor2));

    byte alpha(color2[0]), disAlpha(0xff ^ alpha);
    if (alpha) {
        byte alphaTmp(disAlpha * color1[0] / 0xff);
        byte alphaResult(alpha + alphaTmp);
        color1[0] = alphaResult;
        color1[1] = (color2[1] * alpha + color1[1] * alphaTmp) / alphaResult;
        color1[2] = (color2[2] * alpha + color1[2] * alphaTmp) / alphaResult;
        color1[3] = (color2[3] * alpha + color1[3] * alphaTmp) / alphaResult;
    }
    return ARGB(color1[0], color1[1], color1[2], color1[3]);
}

static inline color gradation(
        const color& aFromColor,
        const color& aToColor,
        const double& aRate
        ) {
    Vector<byte> fromColor(ARGB(aFromColor));
    Vector<byte> toColor(ARGB(aToColor));

    byte r((toColor[1] - fromColor[1]) * aRate + fromColor[1]);
    byte g((toColor[2] - fromColor[2]) * aRate + fromColor[2]);
    byte b((toColor[3] - fromColor[3]) * aRate + fromColor[3]);

    return ARGB(0xff, r, g, b);
}

static inline color gradation(
        const Vector<color>& aColors,
        const double& aRate
        ) {
    if (aColors.empty()) return 0x0;
    const int size(aColors.size() - 1);
    if (!size) return aColors[0];

    const double sep(1.0 / size);
    const int index(Math::min(aRate / sep, size - 1.0));

    return gradation(aColors[index], aColors[index + 1], (aRate - index * sep) * size);
}

static inline KVector operator*(
        const float& aTime,
        const KVector& aVec
        ) {
    return aVec * aTime;
}

#endif /* KUTILITY_H */

