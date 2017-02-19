/**
 * @file   KMidi.h
 * @brief  KMidi
 * @author Maeda Takumi
 */
#ifndef KMIDI_H
#define KMIDI_H

#include "KawazuInclude.h"
#include "KNonCopy.h"

/**
 * @brief  \~english  MIDI controller
 * @brief  \~japanese MIDI(Musical Instrument Digital Interface)コントローラ
 * @author \~ Maeda Takumi
 */
class KMidi : private KNonCopy {
public:

    /** @brief 楽器 */
    typedef enum {
        /* Piano */
        /** アコースティックピアノ　　　 */ AcousticGrandPiano,
        /** ブライトピアノ　　　　　　　 */ BrightAcousticPiano,
        /** エレクトリックグランドピアノ */ ElectricGrandPiano,
        /** ホンキートンクピアノ　　　　 */ Honky_tonkPiano,
        /** エレクトリックピアノ１　　　 */ ElectricPiano1,
        /** エレクトリックピアノ２　　　 */ ElectricPiano2,
        /** ハープシコード　　　　　　　 */ Harpsichord,
        /** クラビネット　　　　　　　　 */ Clavi,

        /* Chromatic Percussion */
        /** チェレスタ　　　　　 */ Celesta,
        /** グロッケンシュピール */ Glockenspiel,
        /** オルゴール　　　　　 */ MusicBox,
        /** ヴィブラフォン　　　 */ Vibraphone,
        /** マリンバ　　　　　　 */ Marimba,
        /** シロフォン　　　　　 */ Xylophone,
        /** チューブラーベル　　 */ TubularBells,
        /** ダルシマー　　　　　 */ Dulcimer,

        /* Organ */
        /** ドローバーオルガン　 */ DrawbarOrgan,
        /** パーカッシブオルガン */ PercussiveOrgan,
        /** ロックオルガン　　　 */ RockOrgan,
        /** チャーチオルガン　　 */ ChurchOrgan,
        /** リードオルガン　　　 */ ReedOrgan,
        /** アコーディオン　　　 */ Accordion,
        /** ハーモニカ　　　　　 */ Harmonica,
        /** タンゴアコーディオン */ TangoAccordion,

        /* Guitar */
        /** アコースティックギター(ナイロン弦) */ AcousticGuitar_nylon,
        /** アコースティックギター(スチール弦) */ AcousticGuitar_steel,
        /** エレクトリックギター(ジャズ)　　　 */ ElectricGuitar_jazz,
        /** エレクトリックギター(クリーン)　　 */ ElectricGuitar_clean,
        /** エレクトリックギター(ミュート)　　 */ ElectricGuitar_muted,
        /** オーバードライブギター　　　　　　 */ OverdrivenGuitar,
        /** ディストーションギター　　　　　　 */ DistortionGuitar,
        /** ギターハーモニクス　　　　　　　　 */ GuitarHarmonics,

        /* Bass */
        /** アコースティックベース　　　　　 */ AcousticBass,
        /** エレクトリックベース(フィンガー) */ ElectricBass_finger,
        /** エレクトリックベース(ピック)　　 */ ElectricBass_pick,
        /** フレットレスベース　　　　　　　 */ FretlessBass,
        /** スラップベース１　　　　　　　　 */ SlapBass1,
        /** スラップベース２　　　　　　　　 */ SlapBass2,
        /** シンセベース１　　　　　　　　　 */ SynthBass1,
        /** シンセベース２　　　　　　　　　 */ SynthBass2,

        /* Strings */
        /** ヴァイオリン　　　　　　　　 */ Violin,
        /** ヴィオラ　　　　　　　　　　 */ Viola,
        /** チェロ　　　　　　　　　　　 */ Cello,
        /** コントラバス　　　　　　　　 */ ContraBass,
        /** トレモロ・ストリングス　　　 */ TremoloStrings,
        /** ピッツィカート・ストリングス */ PizzicatoStrings,
        /** ハープ　　　　　　　　　　　 */ OrchestralHarp,
        /** ティンパニ　　　　　　　　　 */ Timpani,

        /* Ensemble */
        /** ストリングアンサンブル１ */ StringEnsemble1,
        /** ストリングアンサンブル２ */ StringEnsemble2,
        /** シンセストリングス１　　 */ SynthStrings1,
        /** シンセストリングス２　　 */ SynthStrings2,
        /** 声「アー」　　　　　　　 */ VoiceAahs,
        /** 声「オー」　　　　　　　 */ VoiceOohs,
        /** シンセヴォイ　ス　　　　 */ SynthVoice,
        /** オーケストラヒット　　　 */ OrchestraHit,

        /* Brass */
        /** トランペット　　　　 */ Trumpet,
        /** トロンボーン　　　　 */ Trombone,
        /** チューバ　　　　　　 */ Tuba,
        /** ミュートトランペット */ MutedTrumpet,
        /** フレンチ・ホルン　　 */ FrenchHorn,
        /** ブラスセクション　　 */ BrassSection,
        /** シンセブラス１　　　 */ SynthBrass1,
        /** シンセブラス２　　　 */ SynthBrass2,

        /* Reed */
        /** ソプラノサックス　　 */ SopranoSax,
        /** アルトサックス　　　 */ AltoSax,
        /** テナーサックス　　　 */ TenorSax,
        /** バリトンサックス　　 */ BaritoneSax,
        /** オーボエ　　　　　　 */ Oboe,
        /** イングリッシュホルン */ EnglishHorn,
        /** バスーン　　　　　　 */ Bassoon,
        /** クラリネット　　　　 */ Clarinet,

        /* Pipe */
        /** ピッコロ　　　　　　 */ Piccolo,
        /** フルート　　　　　　 */ Flute,
        /** リコーダー　　　　　 */ Recorder,
        /** パンフルート　　　　 */ PanFlute,
        /** ビンに息を吹き込む音 */ BlownBottle,
        /** 尺八　　　　　　　　 */ Shakuhachi,
        /** 口笛　　　　　　　　 */ Whistle,
        /** オカリナ　　　　　　 */ Ocarina,

        /* Synth Lead */
        /** リード1(矩形波)　　　　　 */ Lead1_square,
        /** リード2(鋸歯状波)　　　　 */ Lead2_sawtooth,
        /** リード3(蒸気オルガン)　　 */ Lead3_calliope,
        /** リード4(チフ)　　　　　　 */ Lead4_chiff,
        /** リード5(チャラング)　　　 */ Lead5_charang,
        /** リード6(声)　　　　　　　 */ Lead6_voice,
        /** リード7(５度)　　　　　　 */ Lead7_fifths,
        /** リード8(ベース ＋ リード) */ Lead8_bass_lead,

        /* Synth Pad */
        /** パッド1(ニューエイジ) */ Pad1_newAge,
        /** パッド2(ウォーム)　　 */ Pad2_warm,
        /** パッド3(ポリシンセ)　 */ Pad3_polysynth,
        /** パッド4(コワイア)　　 */ Pad4_choir,
        /** パッド5(ボウ)　　　　 */ Pad5_bowed,
        /** パッド6(メタリック)　 */ Pad6_metallic,
        /** パッド7(ハロー)　　　 */ Pad7_halo,
        /** パッド8(スウィープ)　 */ Pad8_sweep,

        /* Synth Effects */
        /** エフェクト1(雨)　　　　　　　 */ FX1_rain,
        /** エフェクト2(サウンドトラック) */ FX2_soundtrack,
        /** エフェクト3(クリスタル)　　　 */ FX3_crystal,
        /** エフェクト4(アトモスフィア)　 */ FX4_atmosphere,
        /** エフェクト5(ブライトネス)　　 */ FX5_brightness,
        /** エフェクト6(ゴブリン)　　　　 */ FX6_goblins,
        /** エフェクト7(エコー)　　　　　 */ FX7_echoes,
        /** エフェクト8(SF)　　　　　　　 */ FX8_sci_fi,

        /* Ethnic */
        /** シタール　 */ Sitar,
        /** バンジョー */ Banjo,
        /** 三味線　　 */ Shamisen,
        /** 琴　　　　 */ Koto,
        /** カリンバ　 */ Kalimba,
        /** バグパイプ */ Bagpipe,
        /** フィドル　 */ Fiddle,
        /** シャナイ　 */ Shanai,

        /* Percussive */
        /** ティンクルベル　 */ TinkleBell,
        /** アゴゴ　　　　　 */ Agogo,
        /** スチールドラム　 */ SteelDrums,
        /** ウッドブロック　 */ Woodblock,
        /** 太鼓　　　　　　 */ TaikoDrum,
        /** メロディックタム */ MelodicTom,
        /** シンセドラム　　 */ SynthDrum,
        /** リバースシンバル */ ReverseCymbal,

        /* Sound Effects */
        /** ギターフレットノイズ */ GuitarFretNoise,
        /** ブレスノイズ　　　　 */ BreathNoise,
        /** 海岸　　　　　　　　 */ Seashore,
        /** 鳥のさえずり　　　　 */ BirdTweet,
        /** 電話のベル　　　　　 */ TelephoneRing,
        /** ヘリコプター　　　　 */ Helicopter,
        /** 拍手　　　　　　　　 */ Applause,
        /** 銃声　　　　　　　　 */ Gunshot,
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
