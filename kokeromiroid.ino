#include "kokeromin.h"

KoKeromin koke(2,3,4,5,6,7,8,9);
#define LEN 500
int onkai[] = {108, 102, 97, 95, 85, 81, 75, 72};
int gakufu[][2] =
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
  {2, LEN*2},
  
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
  {0, LEN*2}
};
Servo servo;

void setup()
{
  Serial.begin(9600);
  servo.attach(9);
}

int deg;
int cnt;

void loop()
{
  koke.dbg_setAngle(onkai[gakufu[cnt][0]]);
  delay(100);
  koke.pushBtn(2, gakufu[cnt][1]);
  
  cnt = (cnt+1)%29;
}

void loop3()
{
  deg = onkai[cnt];
  Serial.println(deg);
  koke.dbg_setAngle(deg);
  delay(500);
  koke.pushBtn(2, 500);
  
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
  koke.dbg_setAngle(deg);
  delay(1000);
  koke.pushBtn(2, 500);
  //delay(1000);
}
