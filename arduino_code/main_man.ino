// declaration of constants and variables along with assigning pin numbers
#include <Wire.h>

//pin definitions
const int a1 = 2; //throttle input pin
const int a2 = 3; //steering input pin
const int sw = 4; //switch for autonomous mode
const int kill_sw = 9; //kill switch

//use pwm pins for steering and throttle which are different from pin 5 and 6
//pins 5 and 6 have a higher frequency and hence lower duty cycles
const int thr = 10; //throttle output pin
const int str = 11; //steering output pin

//variable definition
int val1 = 0; //pwm value for throttle
int val2 = 0; //pwm value for steering
int tr = 0; //manual mode throttle values
int st; //manual mode steering values
int aut = 0; //pwm value of switch for comparison between logic levels
int kill = 1800;
int flag = 0; //autonomy flag
int x[2]; //variable to receive from I2C Master
int tr1 = 0; //autonomous mode throttle values
int st1 = 0; //autonomous mode steering values

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(1);
  pinMode(a1, INPUT);
  pinMode(a2, INPUT);
  pinMode(thr, OUTPUT);
  pinMode(str, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(kill_sw, INPUT);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  analogWrite(thr, 193);
}
void requestEvent() {
  Wire.write(flag);
}
void receiveEvent(int howMany) {
  for (howMany; howMany > 0; howMany--) {
    x[howMany - 1] = Wire.read();
  }
  tr1 = x[1];
  st1 = x[0];
}
void loop() {
  // put your main code here, to run repeatedly
  val1 = pulseIn(a1, HIGH);
  val2 = pulseIn(a2, HIGH);
  aut = pulseIn(sw, HIGH);
  kill = pulseIn(kill_sw, HIGH);

  if (kill < 1500) {
    if (aut < 1500) {
      //manual mode
      flag = 0;
      if (val1 > 1483) {
        tr = map(val1, 1483, 1890, 193, 197);
      }
      else {
        tr = map(val1, 1483, 1090, 193, 174);
      }
      st = map(val2, 1090, 1890, 127.5, 255);
      analogWrite(thr, tr);
      analogWrite(str, st);
    }

    else {
      //autonomous mode
      flag = 1;
      analogWrite(thr, tr1);
      analogWrite(str, st1);
    }
  }
  else {
    analogWrite(thr, 193);
    analogWrite(str, 127.5);
  }
}
