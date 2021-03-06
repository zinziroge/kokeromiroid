#include <Servo.h>
#include <SD.h>

#include "kokeromin.h"

//Servo servo;

KoKeromin::KoKeromin(
    const unsigned int _pron_pin, 
    const unsigned int _shift_pin, const unsigned int _timbre_pin, const unsigned int _style_pin,
    const unsigned int _low_tone_pin, const unsigned int _range_pin, const unsigned int _scale_pin,
    const unsigned int _servo_pin
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
  
  //servo.attach(_servo_pin);
  
  whole_note_len = 4000;
}

KoKeromin::~KoKeromin()
{
}

unsigned int KoKeromin::btn2pin(KoKeBtn btn)
{
  switch(btn) {
    case Pron:  return pron_pin;
    case Timbre: return timbre_pin;
    case Style: return style_pin;
    case LowTone: return low_tone_pin;
    case Range: return range_pin;
    case Scale: return scale_pin;
    default: return pron_pin;
  }
}

void KoKeromin::pushBtn(KoKeBtn btn, const unsigned int stay_time)
{
  digitalWrite(btn2pin(btn), 1);
  delay(stay_time);
  digitalWrite(btn2pin(btn), 0);
  delay(100);
}

void KoKeromin::holddownBtn(KoKeBtn btn)
{
  digitalWrite(btn2pin(btn), 1);
}

void KoKeromin::releaseBtn(KoKeBtn btn)
{
  digitalWrite(btn2pin(btn), 0);
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
  holddownBtn(Pron);
  delay(SFT_WAIT_TIME);
  pushBtn(Timbre, BTN_HOLD_TIME);
  releaseBtn(Pron);
}

void KoKeromin::chgDrumMode() 
{
  holddownBtn(Pron);
  delay(SFT_WAIT_TIME);
  pushBtn(Range, BTN_HOLD_TIME);
  releaseBtn(Pron);
}

void KoKeromin::returnNmlMode() 
{
  holddownBtn(Style);
  delay(SFT_WAIT_TIME);
  pushBtn(Range, BTN_HOLD_TIME);
  releaseBtn(Style);
}

int KoKeromin::readAngleAin()
{
  unsigned long v=0;
  unsigned int n = 1000;
  int i;
  int max_val = 0;
  int min_val = 1023;
  int max_sum = 0;
  int min_sum = 0;
  int ain;
  
  for(i=0; i<n; i++) { // 100ms
    ain = analogRead(1);
    v += ain;
    if( min_val > ain ) {
      min_val = ain;
    }
    if( max_val < ain ) {
      max_val = ain;
    }
    if( i%200 == 199 ) {
      max_sum += max_val;
      min_sum += min_val;
      max_val = 0;
      min_val = 1023;
    }
    //delay(1);
  }
    Serial.print(min_val);
    Serial.print(",");
    Serial.print(max_val);
    Serial.print(",");
    Serial.print(max_val-min_val);
    Serial.print(",");
    Serial.print(v/(i+1));
    Serial.print(",");
    Serial.print(max_sum/5);
    Serial.print(",");    
    Serial.print(min_sum/5);
    Serial.print(",");
    Serial.println();
  
  //return v/n;
  //return (max_val - min_val); 
  return (max_sum - min_sum)/5; 
}

void KoKeromin::setAngle(const unsigned int interval)
{
  int deg = onkai[interval];
  int ain_tgt = onkai_ain[interval];
  //int ain_tgt = onkai_amp[interval];
  int ain_read;
  int ain_diff;
  int i;
  
  /*
  Serial.print("angle=");
  Serial.println(deg);
  Serial.print("ain_tgt=");
  Serial.println(ain_tgt);  
  for(i=0; i<4; i++) {
    servo.write(deg);
    delay(100);
    ain_read = readAngleAin();
    Serial.print("ain_read=");
    Serial.println(ain_read);   
    ain_diff = ain_read - ain_tgt;
    if( abs(ain_diff) <=8 ) {
      break;
    } else if( ain_diff < 0 ) {
      deg -= 2; // dc
      Serial.println("ain up, deg down, mouse open");
      //deg += 2; // amp
      //Serial.println("ain down, deg up, mouse close");
    } else {
      deg += 2; // dc
      Serial.println("ain down, deg up, mouse close");
      //deg -= 2; //amp
      //Serial.println("ain up, deg down, mouse open");
    }
  }
  */
  servo.write(deg);
  Serial.println();
}

void KoKeromin::calibAngle()
{
  int interval[] = {
    //12,14,16,17,19,21,23
    9, 11,
    12,14,16,17,19,21,23,
    24, 26
  };
  
  int deg;
  int ain_tgt;
  int ain_read;
  int ain_diff;
  int i;
  int j;
  
  Serial.println("calibrate kokeromin.");
  for(j=0; j<11; j++) {
    deg = onkai[interval[j]];
    ain_tgt = onkai_ain[interval[j]];
    //ain_tgt = onkai_amp[interval[j]];
    Serial.print("ain_tgt=");
    Serial.println(ain_tgt);  
  
    for(i=0; i<8; i++) {
    servo.write(60);
    //delay(1000);
    servo.write(deg);
    delay(1000);
    ain_read = readAngleAin();
    ain_diff = ain_read - ain_tgt;
    Serial.print("ain_read=");
    Serial.println(ain_read);   
    if( abs(ain_diff) <=4 ) {
      onkai[interval[j]] = deg;
      Serial.println(interval[j]);   
      Serial.println(deg);   
      delay(5000);
      break;
    } else if( ain_diff < 0 ) {
      deg -= ain_diff/5+1; //dc
      Serial.println("ain up, deg down, mouse open");
      //deg += 4; // amp
      //Serial.println("ain down, deg up, mouse close");
    } else {
      deg += ain_diff/5+1; // dc
      Serial.println("ain down, deg up, mouse close");
      //deg -= 4; // amp
      //Serial.println("ain up, deg down, mouse open");
    }
  }
    Serial.println();
  }
  Serial.println("calibration finish.");
}

void KoKeromin::readAngleFile(const char* angle_file_name)
{
}

/*
int readLine(File* dataFile, byte* buffer, const int len)
{
  int cnt = 0;
  
      while( dataFile.available() && cnt < len ) {
        char c = dataFile.read();
        if( c == '\n' ) {
          break;
        } else {
          buffer[cnt++] = c;
        }
      }
}
*/

int split(const byte* buf, const int buf_len, int* vals, int val_len, const char sc)
{
  int i;
  int val_i=0;
  int tmp=0;
  int cnt=0;
  
  for(i=0; i<buf_len; i++) {
    if( buf[i] == sc ) {
      vals[val_i++] = tmp;
      tmp = 0;
      cnt = 0;
    } else if( 0 <= buf[i] - '0' && buf[i] - '0' <= 9 ) {
      tmp = tmp*10 + buf[i] - '0';
      cnt++;
    }
    //Serial.println(tmp);
  }
  
  if( cnt > 0 ) { // if not end at 'sc'
    vals[val_i] = tmp;
  } else {
    val_i--;
  }

  return val_i;
}

void KoKeromin::readMusicFile(const char* music_file_name)
{


  // open file
  File dataFile = SD.open(music_file_name, FILE_READ);
  
  if (dataFile) {
    byte buffer[16]; // line buffer
    int vals[3]; // split vals
    
    //Serial.println("----");
    while (dataFile.available()) {
      int length = dataFile.available();
      int buf_len;
      
       //Serial.println(dataFile.available());

      if(length > 16){
        length = 16;
      }

      // read line
      //buf_len = readLine(dataFile, buffer, 16);
      buf_len = 0;
      while( dataFile.available() && buf_len < 16 ) {
        char c = dataFile.read();
        Serial.write(c);
        if( c == '\n' ) {
          break;
        } else if( c == '\r' ) {
          // do nothing
        } else {
          buffer[buf_len++] = c;
        }
      }
      //Serial.println(buf_len);
      //Serial.println("-");
      
      split(buffer, buf_len, vals, 3, ',');
      //Serial.println("--");
      //dataFile.read(buffer, length);
      //Serial.println(vals[0]);
      //Serial.println(vals[1]);
      //Serial.println(vals[2]);
      //Serial.println("---");
      
      switch( vals[0] ) {
        case INST_PUSH_PRON:
        case INST_PUSH_SFT:
        case INST_PUSH_TIMBRE:
        case INST_PUSH_SCALE:
        case INST_PUSH_STYLE:
        case INST_PUSH_LOW_TONE:
        case INST_PUSH_RANGE:
          playSound(vals[0], vals[1], vals[2]); // button, interval, note
          break;
        case INST_CHG_MODE:
          switch(vals[1]) {
            case Normal:
              returnNmlMode();
              break;
            case Soramimi:
              chgSoramimiMode();
              break;
            case Drum:
              chgDrumMode();
              break;
            default: 
              break;
          }
          break;
        case INST_CHG_TIMBRE:
          chgTimbre((KoKeTimbre)vals[1]);
          break;
        case INST_CHG_SCALE:
          chgScale((KoKeScale)vals[1]);
          break;
        case INST_CHG_STYLE:
          chgStyle((KoKeStyle)vals[1]);
          break;
        case INST_CHG_LOW_TONE:
          chgLowTone((KoKeLowTone)vals[1]);
          break;
        case INST_CHG_RANGE:
          chgRange((KoKeRange)vals[1]);
          break;
        case INST_TEMPO:
          whole_note_len = vals[1] * 10;
          whole_note_len = 2000;
          break;
        default:
          break;
      }
    }
    
    dataFile.close();
  }
  else {
    Serial.println(F("error opening datalog.txt"));
  }
}

void KoKeromin::playSound(const unsigned int btn, const unsigned int interval, const unsigned int note)
{
  //int deg;
  //int deg_correction = 0;
  static int pre_interval;
  
  //if( (deg - pre_deg) < 4 && 0 < (deg - pre_deg) ) {
  // deg_correction = 2;
  //} else if( (deg - pre_deg) > -4 && 0 > (deg - pre_deg) ) {
  //  deg_correction = -2;
  //}
  //deg_correction = 0;
  //deg_correction = 3;
  
  if( interval == 255 ) {
    setAngle(pre_interval);
  } else {
    //deg = onkai[interval];
    setAngle(interval);
    pushBtn((KoKeBtn)btn, whole_note_len /128 * note);
  }
  
  pre_interval = interval;
}

int KoKeromin::getDeg(const unsigned int interval)
{
}

