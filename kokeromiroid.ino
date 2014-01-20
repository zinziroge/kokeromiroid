#include <SD.h>
#include "kokeromin.h"

//KoKeromin koke(2,3,4,5,6,7,8,1);
KoKeromin koke(2,4,4,5,6,7,8,3);
#define LEN 400

/*
int onkai[] = {
  150, 150, 150, 150, 150, 150, 150
};
*/
//  108, 108, 102, 102,  97,  95,  95,  85,  85,  81,  81,  75,
int onkai[] = { // deg
  //C. C#,  D,   D#,  E,   F,   F#,  G,   G#,  A,   A#,  B
  150, 142, 139, 136, 133, 130, 127, 124, 121, 113, 115, 105,
  102, 108, 95, 102,  89,  85,  95,  81,  85,  76,  81,  71,
   68,  64,  68,  69,  60,  54,  54,  54,  54,  54,  54,  54
};
int onkai_ain[] = { // ain dc
  //C, C#,  D,   D#,  E,   F,   F#,  G,   G#,  A,   A#,  B
  355, 355, 388, 388, 400, 419, 419, 434, 435, 450, 453, 464,
  474, 474, 484, 484, 493, 501, 501, 509, 509, 519, 519, 529,
  536, 536, 544, 544, 554, 560, 560, 572, 572, 577, 577, 587
};
/*
int onkai_amp[] = { // ain amp
  //C, C#,  D,   D#,  E,   F,   F#,  G,   G#,  A,   A#,  B
  410, 410, 388, 388, 345, 327, 327, 298, 298, 271, 271, 259, 
  240, 240, 220, 220, 205, 196, 196, 186, 298, 165, 165, 148, 
  136, 136, 121, 121, 111, 99,  99,  84,  298, 69,  69,  52
};
*/

int score[][2] =
{
  {0, LEN},
  {1, LEN},
  {2, LEN},
  {3, LEN},
  
  {2, LEN},
  {1, LEN},
  {0, LEN*2},
  
  {2, LEN},
  {3, LEN},
  {4, LEN},
  {5, LEN},
  
  {4, LEN},
  {3, LEN},
  {2, LEN},
  {-1, LEN},
  
  {0, LEN*2},
  {0, LEN*2},
  
  {0, LEN*2},
  {0, LEN*2},
  
  {0, LEN*.5},
  {0, LEN*.5},
  {1, LEN*.5},
  {1, LEN*.5},
  
  {2, LEN*.5},
  {2, LEN*.5},
  {3, LEN*.5},
  {3, LEN*.5},
  
  {2, LEN},
  {1, LEN},
  {0, LEN},
  {-1, LEN}
};
Servo servo;

void setup()
{
  int i;
  
  Serial.begin(9600);
  servo.attach(3);

  // init SD
  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println(F("Card failed, or not present"));
    // do nothing
    while(1);
  }
  Serial.println(F("ok."));
  

  //koke.calibAngle();

}

int deg;
int cnt;
int pre_oto;

void loop()
{
  int i;
  int min_val=1023, max_val=0;
  int ain;
  unsigned long v=0;
  
  for(i=60; i < 125; i++) {
    servo.write(i);
    delay(500);
    koke.pushBtn(Pron,500);
    for(i=0; i<100; i++) {
      ain = analogRead(1);
      v += ain;
      if( min_val > ain ) {
        min_val = ain;
      }
      if( max_val < ain ) {
        max_val = ain;
      }
      delayMicroseconds(100);
    }
    Serial.print(i);
    Serial.print(",");
    Serial.print(min_val);
    Serial.print(",");
    Serial.print(max_val);
    Serial.print(",");
    Serial.print(max_val-min_val);
    Serial.print(",");
    Serial.print(v/i);
    Serial.println();  
  }
}

void loop5()
{
  int i;
  /*int interval[] = {
    //12,14,16,17,19,21,23
    11, 9,
    12,16,19,23,14,17,21,
    26, 24
  };*/
  int interval[] = {
    //12,14,16,17,19,21,23
    9, 11,
    12,14,16,17,19,21,23,
    24, 26
  };
  int min_val=1023, max_val=0;
  int ain;
  unsigned long v=0;
  
  /*
  for(i=125; i > 60; i--) {
    //servo.write(i);
    //Serial.print(koke.readAngleAin());
    Serial.print(",");
    Serial.println(i);
    //delay(1000);
  }
  */
  /*
  for(i=60; i < 125; i++) {
    //servo.write(60);
    delay(500);
    servo.write(i);
    Serial.print(koke.readAngleAin());
    Serial.print(",");
    Serial.print(i);
    Serial.println();
    koke.pushBtn(Pron,500);
    delay(500);
  }
  */
  //for(i=0; i<11; i++) {
  //  koke.playSound(1, interval[i], 32);
  //}
  //koke.readMusicFile("music.txt");
  //delay(3000);
  //int deg = analogRead(0)/(double)1024*180*2;
  //koke.setAngle(deg);
  //servo.write(deg);
  //Serial.println(deg);
  //unsigned long v=0;

  //ain = analogRead(1);
  //for(i=0;i<ain/100;i++) {
  //  Serial.print('*');
  //}
  //delay(1);
  //Serial.print(ain);
  //if(Serial.available() > 0) {
  //  Serial.write((ain>>8)&0x3);
  //  Serial.write(ain&0xFF);
  //  Serial.read();
  //}
  
  
  for(i=0; i<100; i++) {
    ain = analogRead(1);
    v += ain;
    if( min_val > ain ) {
      min_val = ain;
    }
    if( max_val < ain ) {
      max_val = ain;
    }
    delayMicroseconds(100);
  }
  Serial.print(min_val);
  Serial.print(",");
  Serial.print(max_val);
  Serial.print(",");
  Serial.print(max_val-min_val);
  Serial.print(",");
  Serial.print(v/i);
  
  
  Serial.println();
  //Serial.print(' ');
  

}

void loop4()
{
  int hosei;
  
  if( (onkai[score[cnt][0]] - pre_oto) >= -4 && 0 > (onkai[score[cnt][0]] - pre_oto) ) {
    hosei = -2;
  } else if( (onkai[score[cnt][0]] - pre_oto) <= 4 && 0 < (onkai[score[cnt][0]] - pre_oto) ) {
    hosei = 2;
  } else {
    hosei = 0;
  }
  pre_oto = onkai[score[cnt][0]];
  
  if( score[cnt][0] >= 0 ) {
    koke.setAngle(onkai[score[cnt][0]]+hosei);
    delay(50);
    koke.pushBtn(Pron, score[cnt][1]);
  } else {
    delay(50+score[cnt][1]);
  }
  
  cnt = (cnt+1)%30;
}

void loop3()
{
  deg = onkai[cnt];
  Serial.println(deg);
  koke.setAngle(deg);
  delay(500);
  koke.pushBtn(Pron, 500);
  
  cnt = (cnt+1)%8;
}

void loop2()
{
  //int v = analogRead(0);
  //koke.dbg_setAngle(v/(double)1024*180);
  //servo2.write(v/(double)1024*180);
  deg = (deg - 3);
  if( deg < 40 ) {
    deg = 121;
  } else if( deg > 121 ) {
    deg = 40;
  }
  //servo2.write(deg);
  Serial.println(deg);
  koke.setAngle(deg);
  delay(1000);
  koke.pushBtn(Pron, 500);
  //delay(1000);
}
