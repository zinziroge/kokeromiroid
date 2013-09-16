#include "kokeromin.h"

KoKeromin koke(2,3,4,5,6,7,8,9);
#define LEN 400
int onkai[] = {108, 102, 97, 95, 85, 81, 75, 72};
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
  Serial.begin(9600);
  servo.attach(9);
}

int deg;
int cnt;
int pre_oto;

void loop()
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
