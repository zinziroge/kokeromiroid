#include <Servo.h>
#include "kokeromin.h"

//Servo servo;

KoKeromin::KoKeromin(
    const unsigned int _pron_pin, 
    const unsigned int _shift_pin, const unsigned int _timbre_pin, const unsigned int _style_pin,
    const unsigned int _low_tone_pin, const unsigned int _range_pin, const unsigned int _scale_pin,
    const unsigned int servo_pin
)
{
  pinMode(_pron_pin, OUTPUT);
  pinMode(_shift_pin, OUTPUT);
  pinMode(_timbre_pin, OUTPUT);
  pinMode(_style_pin, OUTPUT);
  pinMode(_low_tone_pin, OUTPUT);
  pinMode(_range_pin, OUTPUT);
  pinMode(_scale_pin, OUTPUT);
  
  pron_pin = _pron_pin;
  shift_pin = _shift_pin;
  timbre_pin = _timbre_pin;
  style_pin = _style_pin;
  low_tone_pin = _low_tone_pin;
  range_pin = _range_pin;
  scale_pin = _scale_pin;
  
  //servo.attach(servo_pin);
}

KoKeromin::~KoKeromin()
{
}

void KoKeromin::pushBtn(const unsigned int btn, const unsigned int stay_time)
{
  digitalWrite(btn, 1);
  delay(stay_time);
  digitalWrite(btn, 0);
  delay(100);
}

void KoKeromin::holddownBtn(const unsigned int btn)
{
  digitalWrite(btn, 1);
}

void KoKeromin::releaseBtn(const unsigned int btn)
{
  digitalWrite(btn, 0);
}

void KoKeromin::chgConfig(
  const unsigned int set_mode,
  KoKeBtn btn,
  const unsigned int n_nml, 
  const unsigned int n_sft
  )
{
  unsigned int cur_mode;
  //unsigned int n = n_nml + n_sft;
  int cnt;
  int i;
  
  switch( btn ) {
  case Timbre:
    cur_mode = timbre_mode;
    break;
  case Style:
    cur_mode = style_mode;
    break;
  case LowTone:
    cur_mode = low_tone_mode;
    break;
  case Range:
    cur_mode = range_mode;
    break;
  case Scale:
    cur_mode = scale_mode;
    break;
  default:
    break;
  }
  
  pushBtn(btn, SFT_WAIT_TIME);

  if( set_mode < n_nml ) { // set mode is normal.
    if( cur_mode < n_nml ) { // current mode is normal.
      cnt = (set_mode + n_nml ) % n_nml;
      for(i=0; i < cnt; i++) {
        pushBtn(btn, BTN_HOLD_TIME);
      }
      cur_mode = (cur_mode+cnt) % n_nml;
    } else { // current mode is shift.
      pushBtn(btn, BTN_HOLD_TIME);
      cur_mode = 0;
      for(i=0; i < set_mode; i++) {
        pushBtn(btn, BTN_HOLD_TIME);
      }
      cur_mode = (cur_mode+cnt) % n_nml;
    }
  } else { // set mode is shift.
    holddownBtn(btn);
    
    if( cur_mode < n_nml ) { // current mode is normal.
      pushBtn(btn, BTN_HOLD_TIME);
      cur_mode = n_nml;
      cnt = (set_mode - cur_mode + n_sft) % n_sft;
      for(i=0; i < cnt; i++) {
        pushBtn(btn, BTN_HOLD_TIME);
      }
      cur_mode = (cur_mode+cnt) % n_sft + n_nml;
    } else { // current mode is shift.
      cnt = (set_mode - cur_mode + n_sft) % n_sft;
      for(i=0; i < cnt; i++) {
        pushBtn(btn, BTN_HOLD_TIME);
      }
      cur_mode = (cur_mode+cnt) % n_sft + n_nml;
    }
    
    releaseBtn(btn);
  }
  
  switch( btn ) {
  case Timbre:
    timbre_mode = (KoKeTimbre)cur_mode;
    break;
  case Style:
    style_mode = (KoKeStyle)cur_mode;
    break;
  case LowTone:
    low_tone_mode = (KoKeLowTone)cur_mode;
    break;
  case Range:
    range_mode = (KoKeRange)cur_mode;
    break;
  case Scale:
    scale_mode = (KoKeScale)cur_mode;
    break;
  default:
    break;
  }
}

void KoKeromin::chgTimbre(KoKeTimbre mode)
{ 
  KoKeBtn btn = Timbre;

  chgConfig((unsigned int)mode, btn, KOKE_TIMBRE_NML, KOKE_TIMBRE_SFT);  
}

void KoKeromin::chgStyle(KoKeStyle mode)
{
  KoKeBtn btn = Style;

  chgConfig((unsigned int)mode, btn, KOKE_STYLE_NML, KOKE_STYLE_SFT);  
}

void KoKeromin::chgLowTone(KoKeLowTone mode)
{
  KoKeBtn btn = LowTone;

  chgConfig((unsigned int)mode, btn, KOKE_LOW_TONE_NML, KOKE_LOW_TONE_SFT);  
}

void KoKeromin::chgRange(KoKeRange mode)
{
  KoKeBtn btn = Range;

  chgConfig((unsigned int)mode, btn, KOKE_RANGE_NML, KOKE_RANGE_SFT);  
}

void KoKeromin::chgScale(KoKeScale mode)
{
  KoKeBtn btn = Scale;

  chgConfig((unsigned int)mode, btn, KOKE_SCALE_NML, KOKE_SCALE_SFT);  
}

void KoKeromin::chgSoramimiMode ()
{
  holddownBtn(pron_pin);
  delay(SFT_WAIT_TIME);
  pushBtn(timbre_pin, BTN_HOLD_TIME);
  releaseBtn(pron_pin);
}

void KoKeromin::chgDrumMode() 
{
  holddownBtn(pron_pin);
  delay(SFT_WAIT_TIME);
  pushBtn(range_pin, BTN_HOLD_TIME);
  releaseBtn(pron_pin);
}

void KoKeromin::returnNmlMode() 
{
  holddownBtn(style_pin);
  delay(SFT_WAIT_TIME);
  pushBtn(range_pin, BTN_HOLD_TIME);
  releaseBtn(style_pin);
}

void KoKeromin::setAngle(const unsigned int deg)
{
  Serial.println(deg);
  servo.write(deg);
}

int KoKeromin::playSound(KoKeSound sound, unsigned int octave)
{
}

void KoKeromin::dbg_setAngle(const unsigned int deg)
{
  setAngle(deg);
}


