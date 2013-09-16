#include <Servo.h>

#ifndef __KOKEROMIN_H__
#define __KOKEROMIN_H__

#define KOKE_TIMBRE_NML   7
#define KOKE_TIMBRE_SFT   5
#define KOKE_STYLE_NML    6
#define KOKE_STYLE_SFT    2
#define KOKE_LOW_TONE_NML 7
#define KOKE_LOW_TONE_SFT 5
#define KOKE_RANGE_NML    4
#define KOKE_RANGE_SFT    0
#define KOKE_SCALE_NML    5
#define KOKE_SCALE_SFT    7

#define BTN_HOLD_TIME     500
#define SFT_WAIT_TIME     2000

enum KoKeSound {
  C, D, E, F, G, A, B,
  CS, DS, FS, GS, AS
};

enum KoKeTimbre {
  Tah, Violin, Keroko, Kerooya, Kokeh, Nyah, Won, // normal
  OrganA, OrganB, Sin, GameA, GameB //shift
};

enum KoKeStyle {
  PushLegato, PushRepeat, OpenLegato, OpenRepeat, HandbellLegato, HandbellRepeat,
  PushOneshot, HandbellOneshot
};

//enum KoKeLowTone {
//  C, D, E, F, G, A, B,
//  CS, DS, FS, GS, AS
//};
typedef KoKeSound KoKeLowTone;

enum KoKeRange {
  Octave5, Octave4, Octave3, Octave2
};

enum KoKeScale {
  Portamento, Hacho, Yonanuki, Blues, Ryuukyu,
  Hecho, Tocho, Minyou, Miyakobushi, Arabia, Spain, Hanonkai
};

enum KoKeBtn {
  Pron,
  Shift, Timbre, Scale, Style, LowTone, Range
};

enum KoKeMode {
  Normal, Soramimi, Drum
};

enum KoKeDrum {
  Snare, Buss, Hihat, Tam, Rimshot, CrushCymbal, RideCymbal 
};

//Servo servo;

class KoKeromin {
private:
  KoKeTimbre timbre_mode;
  KoKeStyle style_mode;
  KoKeLowTone low_tone_mode;
  KoKeRange range_mode;
  KoKeScale scale_mode;

  KoKeMode kmode;
  
  unsigned int pron_pin;
  unsigned int shift_pin;
  unsigned int timbre_pin;
  unsigned int style_pin;
  unsigned int low_tone_pin;
  unsigned int range_pin;
  unsigned int scale_pin;
  
  //Servo servo;
  
  void chgConfig(const unsigned int mode, KoKeBtn btn, const unsigned int n_nml, const unsigned int n_sft);
  //void pushBtnLong(const unsigned int btn, const unsigned int stay_time); // push button a few second, and release
  void holddownBtn(const unsigned int btn);
  void releaseBtn(const unsigned int btn);
  void setAngle(const unsigned int deg);

public:
  KoKeromin(
    const unsigned int pron_pin, 
    const unsigned int shift_pin, const unsigned int timbre_pin, const unsigned int style_pin,
    const unsigned int low_tone_pin, const unsigned int range_pin, const unsigned int scale_pin,
    const unsigned int servo_pin
    );
  ~KoKeromin();

  void chgTimbre(KoKeTimbre mode);
  void chgStyle(KoKeStyle mode);
  void chgLowTone(KoKeLowTone mode);
  void chgRange(KoKeRange mode);
  void chgScale(KoKeScale mode);
  
  void chgSoramimiMode();
  void chgDrumMode();
  void returnNmlMode();
  
  void pushBtn(const unsigned int btn, const unsigned int stay_time);  // push button a few second, and release
  int playSound(KoKeSound sound, unsigned int octave);

  void dbg_setAngle(const unsigned int deg);
};
  
#endif
