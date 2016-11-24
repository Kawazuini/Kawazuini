/**
 * @file KMidi.h
 * @brief MIDIコントローラクラス
 */
#ifndef KMIDI_H
#define KMIDI_H

#include "KawazuInclude.h"
#include "KNonCopy.h"

/** @brief MIDI(Musical Instrument Digital Interface)コントローラ */
class KMidi : private KNonCopy {
public:

    /** @brief 楽器 */
    typedef enum {
        /* Piano */
        /** @brief アコースティックピアノ　　　 */ AcousticGrandPiano,
        /** @brief ブライトピアノ　　　　　　　 */ BrightAcousticPiano,
        /** @brief エレクトリックグランドピアノ */ ElectricGrandPiano,
        /** @brief ホンキートンクピアノ　　　　 */ Honky_tonkPiano,
        /** @brief エレクトリックピアノ１　　　 */ ElectricPiano1,
        /** @brief エレクトリックピアノ２　　　 */ ElectricPiano2,
        /** @brief ハープシコード　　　　　　　 */ Harpsichord,
        /** @brief クラビネット　　　　　　　　 */ Clavi,

        /* Chromatic Percussion */
        /** @brief チェレスタ　　　　　 */ Celesta,
        /** @brief グロッケンシュピール */ Glockenspiel,
        /** @brief オルゴール　　　　　 */ MusicBox,
        /** @brief ヴィブラフォン　　　 */ Vibraphone,
        /** @brief マリンバ　　　　　　 */ Marimba,
        /** @brief シロフォン　　　　　 */ Xylophone,
        /** @brief チューブラーベル　　 */ TubularBells,
        /** @brief ダルシマー　　　　　 */ Dulcimer,

        /* Organ */
        /** @brief ドローバーオルガン　 */ DrawbarOrgan,
        /** @brief パーカッシブオルガン */ PercussiveOrgan,
        /** @brief ロックオルガン　　　 */ RockOrgan,
        /** @brief チャーチオルガン　　 */ ChurchOrgan,
        /** @brief リードオルガン　　　 */ ReedOrgan,
        /** @brief アコーディオン　　　 */ Accordion,
        /** @brief ハーモニカ　　　　　 */ Harmonica,
        /** @brief タンゴアコーディオン */ TangoAccordion,

        /** Guitar */
        /** @brief アコースティックギター(ナイロン弦) */ AcousticGuitar_nylon,
        /** @brief アコースティックギター(スチール弦) */ AcousticGuitar_steel,
        /** @brief エレクトリックギター(ジャズ)　　　 */ ElectricGuitar_jazz,
        /** @brief エレクトリックギター(クリーン)　　 */ ElectricGuitar_clean,
        /** @brief エレクトリックギター(ミュート)　　 */ ElectricGuitar_muted,
        /** @brief オーバードライブギター　　　　　　 */ OverdrivenGuitar,
        /** @brief ディストーションギター　　　　　　 */ DistortionGuitar,
        /** @brief ギターハーモニクス　　　　　　　　 */ GuitarHarmonics,

        /* Bass */
        /** @brief アコースティックベース　　　　　 */ AcousticBass,
        /** @brief エレクトリックベース(フィンガー) */ ElectricBass_finger,
        /** @brief エレクトリックベース(ピック)　　 */ ElectricBass_pick,
        /** @brief フレットレスベース　　　　　　　 */ FretlessBass,
        /** @brief スラップベース１　　　　　　　　 */ SlapBass1,
        /** @brief スラップベース２　　　　　　　　 */ SlapBass2,
        /** @brief シンセベース１　　　　　　　　　 */ SynthBass1,
        /** @brief シンセベース２　　　　　　　　　 */ SynthBass2,

        /* Strings */
        /** @brief ヴァイオリン　　　　　　　　 */ Violin,
        /** @brief ヴィオラ　　　　　　　　　　 */ Viola,
        /** @brief チェロ　　　　　　　　　　　 */ Cello,
        /** @brief コントラバス　　　　　　　　 */ ContraBass,
        /** @brief トレモロ・ストリングス　　　 */ TremoloStrings,
        /** @brief ピッツィカート・ストリングス */ PizzicatoStrings,
        /** @brief ハープ　　　　　　　　　　　 */ OrchestralHarp,
        /** @brief ティンパニ　　　　　　　　　 */ Timpani,

        /* Ensemble */
        /** @brief ストリングアンサンブル１ */ StringEnsemble1,
        /** @brief ストリングアンサンブル２ */ StringEnsemble2,
        /** @brief シンセストリングス１　　 */ SynthStrings1,
        /** @brief シンセストリングス２　　 */ SynthStrings2,
        /** @brief 声「アー」　　　　　　　 */ VoiceAahs,
        /** @brief 声「オー」　　　　　　　 */ VoiceOohs,
        /** @brief シンセヴォイ　ス　　　　 */ SynthVoice,
        /** @brief オーケストラヒット　　　 */ OrchestraHit,

        /* Brass */
        /** @brief トランペット　　　　 */ Trumpet,
        /** @brief トロンボーン　　　　 */ Trombone,
        /** @brief チューバ　　　　　　 */ Tuba,
        /** @brief ミュートトランペット */ MutedTrumpet,
        /** @brief フレンチ・ホルン　　 */ FrenchHorn,
        /** @brief ブラスセクション　　 */ BrassSection,
        /** @brief シンセブラス１　　　 */ SynthBrass1,
        /** @brief シンセブラス２　　　 */ SynthBrass2,

        /* Reed */
        /** @brief ソプラノサックス　　 */ SopranoSax,
        /** @brief アルトサックス　　　 */ AltoSax,
        /** @brief テナーサックス　　　 */ TenorSax,
        /** @brief バリトンサックス　　 */ BaritoneSax,
        /** @brief オーボエ　　　　　　 */ Oboe,
        /** @brief イングリッシュホルン */ EnglishHorn,
        /** @brief バスーン　　　　　　 */ Bassoon,
        /** @brief クラリネット　　　　 */ Clarinet,

        /* Pipe */
        /** @brief ピッコロ　　　　　　 */ Piccolo,
        /** @brief フルート　　　　　　 */ Flute,
        /** @brief リコーダー　　　　　 */ Recorder,
        /** @brief パンフルート　　　　 */ PanFlute,
        /** @brief ビンに息を吹き込む音 */ BlownBottle,
        /** @brief 尺八　　　　　　　　 */ Shakuhachi,
        /** @brief 口笛　　　　　　　　 */ Whistle,
        /** @brief オカリナ　　　　　　 */ Ocarina,

        /* Synth Lead */
        /** @brief リード1(矩形波)　　　　　 */ Lead1_square,
        /** @brief リード2(鋸歯状波)　　　　 */ Lead2_sawtooth,
        /** @brief リード3(蒸気オルガン)　　 */ Lead3_calliope,
        /** @brief リード4(チフ)　　　　　　 */ Lead4_chiff,
        /** @brief リード5(チャラング)　　　 */ Lead5_charang,
        /** @brief リード6(声)　　　　　　　 */ Lead6_voice,
        /** @brief リード7(５度)　　　　　　 */ Lead7_fifths,
        /** @brief リード8(ベース ＋ リード) */ Lead8_bass_lead,

        /* Synth Pad */
        /** @brief パッド1(ニューエイジ) */ Pad1_newAge,
        /** @brief パッド2(ウォーム)　　 */ Pad2_warm,
        /** @brief パッド3(ポリシンセ)　 */ Pad3_polysynth,
        /** @brief パッド4(コワイア)　　 */ Pad4_choir,
        /** @brief パッド5(ボウ)　　　　 */ Pad5_bowed,
        /** @brief パッド6(メタリック)　 */ Pad6_metallic,
        /** @brief パッド7(ハロー)　　　 */ Pad7_halo,
        /** @brief パッド8(スウィープ)　 */ Pad8_sweep,

        /* Synth Effects */
        /** @breif エフェクト1(雨)　　　　　　　 */ FX1_rain,
        /** @breif エフェクト2(サウンドトラック) */ FX2_soundtrack,
        /** @breif エフェクト3(クリスタル)　　　 */ FX3_crystal,
        /** @breif エフェクト4(アトモスフィア)　 */ FX4_atmosphere,
        /** @breif エフェクト5(ブライトネス)　　 */ FX5_brightness,
        /** @breif エフェクト6(ゴブリン)　　　　 */ FX6_goblins,
        /** @breif エフェクト7(エコー)　　　　　 */ FX7_echoes,
        /** @breif エフェクト8(SF)　　　　　　　 */ FX8_sci_fi,

        /* Ethnic */
        /** @brief シタール　 */ Sitar,
        /** @brief バンジョー */ Banjo,
        /** @brief 三味線　　 */ Shamisen,
        /** @brief 琴　　　　 */ Koto,
        /** @brief カリンバ　 */ Kalimba,
        /** @brief バグパイプ */ Bagpipe,
        /** @brief フィドル　 */ Fiddle,
        /** @brief シャナイ　 */ Shanai,

        /* Percussive */
        /** @brief ティンクルベル　 */ TinkleBell,
        /** @brief アゴゴ　　　　　 */ Agogo,
        /** @brief スチールドラム　 */ SteelDrums,
        /** @brief ウッドブロック　 */ Woodblock,
        /** @brief 太鼓　　　　　　 */ TaikoDrum,
        /** @brief メロディックタム */ MelodicTom,
        /** @brief シンセドラム　　 */ SynthDrum,
        /** @brief リバースシンバル */ ReverseCymbal,

        /* Sound Effects */
        /** @brief ギターフレットノイズ */ GuitarFretNoise,
        /** @brief ブレスノイズ　　　　 */ BreathNoise,
        /** @brief 海岸　　　　　　　　 */ Seashore,
        /** @brief 鳥のさえずり　　　　 */ BirdTweet,
        /** @brief 電話のベル　　　　　 */ TelephoneRing,
        /** @brief ヘリコプター　　　　 */ Helicopter,
        /** @brief 拍手　　　　　　　　 */ Applause,
        /** @brief 銃声　　　　　　　　 */ Gunshot,
    } Instrument;

    /** @brief 音符 */
    typedef struct {
        /** @brief 高さ */ int mTone;
        /** @brief 音価 */ int mPhonetic;
        /** @brief 強さ */ int mVelocity;
    } Note;
private:
    /** @brief midi出力デバイス */ HMIDIOUT mMidiOut;

    /** @brief 再生パラメータ   */ static const int STATE_PLAY;
    /** @brief 変更パラメータ   */ static const int STATE_CHANGE;

    /** @return midiメッセージ */
    static inline unsigned long noteToMsg(const int& aStatus, const int& aChannel, const int& aData1, const int& aData2) {
        return (aStatus << 4) | aChannel | (aData1 << 8) | (aData2 << 16);
    };
public:
    KMidi();
    virtual ~KMidi();

    /**
     * @brief 楽器情報の登録
     * @param aInstrument 楽器番号
     */
    void set(const int& aChannel, const Instrument& aInstrument) const;
    /** @breif 音を流す   */ void play(const int& aChannel, const Note& aNote) const;
    /** @brief 音を止める */ void stop(const int& aChannel) const;
};

#endif /* KMIDI_H */
