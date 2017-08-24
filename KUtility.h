/**
 * @file   KUtility.h
 * @brief  Header of utility function etc.
 * @author Maeda Takumi
 */
#ifndef KUTILITY_H
#define KUTILITY_H

#include "KVector.h"
#include "KMath.h"

/**
 * \~japanese
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

enum Extension {
    BMP,
    GIF,
    JPG,
    PNG,
};

/**
 * \~english
 * @brief standard output
 * @param aData output data
 * \~japanese
 * @brief 標準出力
 * @param aData 出力データ
 */
template <class Type>
static inline void print(const Type& aData) {
    std::cout << aData << std::flush;
}

/**
 * \~english
 * @brief standard output(new line)
 * @param aData output data
 * \~japanese
 * @brief 標準出力(改行)
 * @param aData 出力データ
 */
template <class Type>
static inline void println(const Type& aData) {
    std::cout << aData << std::endl;
}

/**
 * \~english
 * @brief  standard output(new line)
 * @param  aData output data 
 * @return output data
 * \~japanese
 * @brief  標準出力(改行)
 * @param  aData 出力データ
 * @return 出力データ
 */
template <class Type>
static inline Type printWrap(const Type& aData) {
    std::cout << aData << std::endl;
    return aData;
}

/**
 * \~english
 * @brief  convert numeric value to character string.
 * @param  aSrc numeric value
 * @return character string
 * \~japanese
 * @brief  数値を文字列に変換します。
 * @param  aSrc 数値
 * @return 文字列
 */
template <class Type>
static inline String toString(const Type& aSrc) {
    return std::to_string(aSrc);
}

/**
 * \^english
 * @brief  convert numeric value to character string.
 * @param  aSrc   character string
 * @param  aRadix radix
 * @return numeric value
 * \^japanese
 * @brief  文字列を整数値に変換します。
 * @param  aSrc   文字列
 * @param  aRadix 基数
 * @return 数値
 */
static inline int toInt(const String& aSrc, const int& aRadix = 10) {
    if (aSrc.empty()) return 0;
    return strtol(aSrc.data(), nullptr, aRadix);
}

/**
 * \~english
 * @brief  convert character string to real number.
 * @param  aSrc character string
 * @return real number
 * \~japanese
 * @brief  文字列を実数値に変換します。
 * @param  aSrc 文字列
 * @return 実数値
 */
static inline float toFloat(const String& aSrc) {
    if (aSrc.empty()) return 0;
    return atof(aSrc.data());
}

/**
 * \~english
 * @brief  convert character string to color.
 * @param  aSrc character string
 * @return color
 * \~japanese
 * @brief  文字列を色情報に変換します。
 * @param  aSrc 文字列
 * @return 色情報
 */
static inline color toColor(const String& aSrc) {
    if (aSrc.empty()) return 0x00000000;
    return strtoul(aSrc.data(), nullptr, 16);
}

/**
 * \~english
 * @brief  split character string with specified regex.
 * @param  aSrc   string to split
 * @param  aRegex regex used for splitting
 * @return list of splited strings
 * \~japanese
 * @brief  正規表現で文字列を分割します。
 * @param  aSrc   分割する文字列
 * @param  aRegex 分割に使用する正規表現
 * @return 分割した文字列のリスト
 */
static inline Vector<String> split(const String& aSrc, const Regex& aRegex) {
    std::sregex_token_iterator first(aSrc.begin(), aSrc.end(), aRegex, -1);
    std::sregex_token_iterator last;
    return Vector<String>(first, last);
}

/**
 * \~english
 * @brief  split character string with specified character string.
 * @note   specified character string is not included in the return value.
 * @param  aSrc string to split
 * @param  aSep string used for splitting
 * @return list of splited strings
 * \~japanese
 * @brief  指定文字列で文字列を分割します。
 * @note   指定文字列は返却値に含まれません。
 * @param  aSrc 分割する文字列
 * @param  aSep 分割に使用する文字列
 * @return 分割した文字列のリスト
 */
static inline Vector<String> split(const String& aSrc, const String& aSep) {
    Regex regex(aSep);
    return split(aSrc, regex);
}

/**
 * \~english
 * @brief  split character string with length of string.
 * @param  aSrc    string to split
 * @param  aLength Length of string to split
 * @return list of splited strings
 * \~japanese
 * @brief  文字数で文字列を分割します。
 * @param  aSrc    分割する文字列
 * @param  aLength 分割する文字数
 * @return 分割した文字列のリスト
 */
static inline Vector<String> split(const String& aSrc, const int& aLength) {
    Vector<String> list;
    for (int i = 0, i_e(aSrc.size()); i < i_e; i += aLength) {
        list.push_back(aSrc.substr(i, aLength));
    }
    return list;
}

/**
 * \~english
 * @brief copy string.
 * @param aDist copy destination character array
 * @param aSrc  string to copy from
 * @param aSize copied size
 * \~japanese
 * @brief 文字列をコピーします。
 * @param aDist コピー先の文字配列
 * @param aSrc  コピー元の文字列
 * @param aSize コピーするサイズ
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

/**
 * \~english
 * @brief  convert encoding from UTF8 to ShiftJIS.
 * @param  aSrc UTF8 string
 * @return ShiftJIS string
 * \~japanese
 * @brief  UTF8 から ShiftJIS へエンコーディングを変換します。
 * @param  aSrc UTF8文字列
 * @return ShiftJIS文字列
 */
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

/**
 * \~english
 * @brief  convert encoding from ShiftJIS to UTF8.
 * @param  aSrc ShiftJIS string
 * @return UTF8 string
 * \~japanese
 * @brief  ShiftJIS から UTF8 へエンコーディングを変換します。
 * @param  aSrc ShiftJIS文字列
 * @return UTF8文字列
 */
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

/**
 * \~english
 * @brief  get current time in milliseconds.
 * @return current time
 * \~japanese
 * @brief  現在時刻をミリ秒単位で取得します。
 * @return 現在時刻
 */
static inline Time now() {
    using namespace std::chrono;
    return duration_cast<milliseconds> (system_clock::now().time_since_epoch()).count();
}

/**
 * \~english
 * @brief  get the current date as string.
 * @return current date as string.
 * \~japanese
 * @brief  現在の日付を文字列で取得します。
 * @return 文字列表現での現在の日付
 */
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

/**
 * \~english
 * @brief  get the current time as string.
 * @return current time as string.
 * \~japanese
 * @brief  現在の時刻を文字列で取得します。
 * @return 文字列表現での現在の時刻
 */
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
 * \~english
 * @brief  generate a random number.
 * @param  aMax max of random number
 * @return random number
 * \~japanese
 * @brief  乱数を生成します。
 * @param  aMax 乱数上限
 * @return 乱数
 */
static inline int random(const int& aMax) {
    using namespace std;
    /* 疑似乱数生成機   */ static mt19937 engine(now());
    /* 乱数フォーマット */ static uniform_int_distribution<> dist(0, 0xfffffff);

    return dist(engine) % aMax;
}

/**
 * \~english
 * @brief  generate a random vector.
 * @return random vector
 * \~japanese
 * @brief  ランダムなベクトルを生成します。
 * @return ランダムなベクトル
 */
static inline KVector randVec() {
    // 長さの最大値 : 1
    return KVector(random(30000) - 15000, random(30000) - 15000, random(30000) - 15000) / 15000;
};

/**
 * \~english
 * @brief  load string from resource.
 * @param  aId resource ID
 * @return loaded string
 * \~japanese
 * @brief  リソースから文字列を読み込みます。
 * @param  aId リソースID
 * @return 読み込んだ文字列(UTF8に変換済み)
 * @note   リソースはShiftJISでしか読み込めない(検証済み(環境によるかも?))
 * @note   最大で1024文字しか読み込めない
 */
static inline String loadString(const int& aId) {
    static const int LOAD_SIZE(1024);
    TCHAR str[LOAD_SIZE];
    LoadString(GetModuleHandle(nullptr), aId, str, LOAD_SIZE);
    return P(str);
}

/**
 * \~english
 * @brief  load multiple strings from resource
 * @param  aId  rsource ID
 * @param  aNum number of load string
 * @return list of loaded string
 * \~japanese
 * @brief  リソースから文字列を複数読み込みます。
 * @param  aId  リソースID
 * @param  aNum 読み込むリソース数
 * @return 読み込んだ文字列のリスト
 */
static inline Vector<String> loadStrings(const int& aId, const int& aNum) {
    Vector<String> list;
    for (int i = aId, i_e(aId + aNum); i < i_e; ++i) {
        list.push_back(loadString(i));
    }
    return list;
}

/**
 * \~english
 * @brief  generate colors from elements of arguments.
 * @param  A alpha
 * @param  R red
 * @param  G green
 * @param  B blue
 * @return color
 * \~japanese
 * @brief  引数の要素から色を生成します。
 * @param  A α
 * @param  R 赤
 * @param  G 緑
 * @param  B 青
 * @return 色
 */
static inline color ARGB(
        const byte& A,
        const byte& R,
        const byte& G,
        const byte& B
        ) {
    return A << 24 | R << 16 | G << 8 | B << 0;
}

/**
 * \~english
 * @brief  decomposes color information of argument into four elements.
 * @param  aColor color information to decompose
 * @return four elements constituting color
 * \~japanese
 * @brief  引数の色情報を4要素に分解します。
 * @param  aColor 分解する色情報
 * @return 色を構成する4要素
 */
static inline Vector<byte> ARGB(const color& aColor) {
    Vector<byte> elem(4);
    elem[0] = (aColor & 0xff000000) >> 24; // A
    elem[1] = (aColor & 0x00ff0000) >> 16; // R
    elem[2] = (aColor & 0x0000ff00) >> 8; // G
    elem[3] = (aColor & 0x000000ff) >> 0; // B

    return elem;
}

/**
 * \~english
 * @brief  generate a random color.
 * @return random color
 * \~japanese
 * @brief  ランダムな色を生成します。
 * @return ランダムな色
 */
static inline color randColor() {
    return ARGB(
            0xff * ((double) (random(30000) - 15000) / 15000.0),
            0xff * ((double) (random(30000) - 15000) / 15000.0),
            0xff * ((double) (random(30000) - 15000) / 15000.0),
            0xff * ((double) (random(30000) - 15000) / 15000.0)
            );
};

/**
 * \~english
 * @brief send color information to OpenGL.
 * @param aColor color information to be transmitted
 * \~japanese
 * @brief 色情報をOpenGLに送信します。
 * @param aColor 送信する色情報
 */
static inline void glColor(const color& aColor) {
    glColor4ub(
            (aColor & 0x00ff0000) >> 16, // R
            (aColor & 0x0000ff00) >> 8, // G
            (aColor & 0x000000ff) >> 0, // B            
            (aColor & 0xff000000) >> 24 // A
            );
}

/**
 * \~english
 * @brief send vertex to OpenGL.
 * @param aVertex vertex to be transmitted
 * \~japanese
 * @brief 頂点をOpenGLに送信します。
 * @param aVertex 送信する頂点
 */
static inline void glVertex(const KVector& aVertex) {
    glVertex3f(DEPLOY_VEC(aVertex));
}

/**
 * \~english
 * @brief send normal to OpenGL.
 * @param aNormal normal to be transmitted
 * \~japanese
 * @brief 法線をOpenGLに送信します。
 * @param aNormal 送信する法線
 */
static inline void glNormal(const KVector& aNormal) {
    glNormal3f(DEPLOY_VEC(aNormal));
}

/**
 * \~english
 * @brief  mix two colors.
 * @param  aColor1 base color
 * @param  aColor2 color to mix
 * @return mixed color
 * \~japanese
 * @brief  2色を混合します。
 * @param  aColor1 基本色
 * @param  aColor2 重ねる色
 * @return 混合した色
 */
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

/**
 * \~english
 * @brief  calculate the gradation color between two colors
 * @param  aFromColor base color
 * @param  aToColor   target color
 * @param  aRate      rate
 * @return gradation color
 * \~japanese
 * @brief  2色の間のグラデーション色を計算します。
 * @param  aFromColor 基本色
 * @param  aToColor   目標色
 * @param  aRate      倍率
 * @return グラデーション色
 */
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

/**
 * \~english
 * @brief  calculate the gradation color between multiple colors
 * @param  aColors color list
 * @param  aRate   rate
 * @return gradation color
 * \~japanese
 * @brief  複数色の間のグラデーション色を計算します。
 * @param  aColors 色のリスト
 * @param  aRate   倍率
 * @return グラデーション色
 */
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

