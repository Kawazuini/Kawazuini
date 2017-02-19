/**
 * @file   KMidi.h
 * @brief  KMidi
 * @author Maeda Takumi
 * @note   use lib winmm
 */
#ifndef KMIDI_H
#define KMIDI_H

#include "KMutex.h"
#include "KNonCopy.h"
#include "KThread.h"

/**
 * @brief  \~english  MIDI controller
 * @brief  \~japanese MIDI(Musical Instrument Digital Interface)コントローラ
 * @author \~ Maeda Takumi
 */
class KMidi : private KNonCopy {
public:

    /**
     * @brief \~english  instrument
     * @brief \~japanese 楽器
     */
    enum Instrument {
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
    };

    /**
     * @brief \~english  tone
     * @brief \~japanese 音程
     */
    enum Tone {
        C0, _C0, D0_ = _C0, D0, _D0, E0_ = _D0, E0, F0, _F0, G0_ = _F0, G0, _G0, A0_ = _G0, A0, _A0, B0_ = _A0, B0,
        C1, _C1, D1_ = _C1, D1, _D1, E1_ = _D1, E1, F1, _F1, G1_ = _F1, G1, _G1, A1_ = _G1, A1, _A1, B1_ = _A1, B1,
        C2, _C2, D2_ = _C2, D2, _D2, E2_ = _D2, E2, F2, _F2, G2_ = _F2, G2, _G2, A2_ = _G2, A2, _A2, B2_ = _A2, B2,
        C3, _C3, D3_ = _C3, D3, _D3, E3_ = _D3, E3, F3, _F3, G3_ = _F3, G3, _G3, A3_ = _G3, A3, _A3, B3_ = _A3, B3,
        /* ド4   */ C4,
        /* ド4#  */ _C4,
        /* レ4♭ */ D4_ = _C4,
        /* レ4   */ D4,
        /* レ4#  */ _D4,
        /* ミ4♭ */ E4_ = _D4,
        /* ミ4   */ E4,
        /* ﾌｧ4   */ F4,
        /* ﾌｧ4#  */ _F4,
        /* ソ4♭ */ G4_ = _F4,
        /* ソ4   */ G4,
        /* ソ4#  */ _G4,
        /* ラ4♭ */ A4_ = _G4,
        /* ラ4   */ A4,
        /* ラ4#  */ _A4,
        /* シ4♭ */ B4_ = _A4,
        /* シ4   */ B4,
        C5, _C5, D5_ = _C5, D5, _D5, E5_ = _D5, E5, F5, _F5, G5_ = _F5, G5, _G5, A5_ = _G5, A5, _A5, B5_ = _A5, B5,
        C6, _C6, D6_ = _C6, D6, _D6, E6_ = _D6, E6, F6, _F6, G6_ = _F6, G6, _G6, A6_ = _G6, A6, _A6, B6_ = _A6, B6,
        C7, _C7, D7_ = _C7, D7, _D7, E7_ = _D7, E7, F7, _F7, G7_ = _F7, G7, _G7, A7_ = _G7, A7, _A7, B7_ = _A7, B7,
        C8, _C8, D8_ = _C8, D8, _D8, E8_ = _D8, E8, F8, _F8, G8_ = _F8, G8, _G8, A8_ = _G8, A8, _A8, B8_ = _A8, B8,
        C9, _C9, D9_ = _C9, D9, _D9, E9_ = _D9, E9, F9, _F9, G9_ = _F9, G9, _G9, A9_ = _G9, A9, _A9, B9_ = _A9, B9,
        C10, _C10, D10_ = _C10, D10, _D10, E10_ = _D10, E10, F10, _F10, G10_ = _F10, G10, // G10(127)
    };

    /** @brief 音符 */
    struct Note {
        /** @brief 音程 */ Tone mTone;
        /** @brief 音価 */ int mPhonetic;
        /** @brief 強さ */ int mVelocity;
    };

private:
    /** @brief midi出力デバイス */ HMIDIOUT mMidi;

    KThread mThread;
    KMutex mNoteLock;

    Vector<Vector<Note>> mNotes;

    /** @brief チャンネル数     */ static const int CHANNEL_COUNT;
    /** @brief 再生パラメータ   */ static const int STATE_PLAY;
    /** @brief 変更パラメータ   */ static const int STATE_CHANGE;

    /** @return midiメッセージ */
    static inline unsigned long noteToMsg(const int& aStatus, const int& aChannel, const int& aData1, const int& aData2) {
        return (aStatus << 4) | aChannel | (aData1 << 8) | (aData2 << 16);
    };

    static void* TimeManager(void* aMidi);
public:
    KMidi();
    ~KMidi();

    /**
     * \~english
     * @brief register instrument.
     * @param aChannel    registeration channel
     * @param aInstrument instrument number
     * \~japanese
     * @brief 楽器情報を登録します。
     * @param aChannel    登録チャンネル
     * @param aInstrument 楽器番号
     */
    void set(const int& aChannel, const Instrument& aInstrument) const;
    /** @breif 音を流す   */ void play(const int& aChannel, const Note& aNote);
    /** @brief 音を止める */ void stop(const int& aChannel, const Note& aNote) const;

    /**
     * @brief \~english  stop sound in all channel.
     * @brief \~japanese 全てのチャンネルの音を止めます。
     */
    void stop();
};

#endif /* KMIDI_H */

