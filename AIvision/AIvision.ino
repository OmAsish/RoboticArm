#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define numOfValsRec 5
#define digitsPerValRec 1
int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1; //$00000
int counter = 0;
bool counterStart = false;
String recievedSring;
#define SERVOMIN  90 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  630 // this is the 'maximum' pulse length count (out of 4096)

const int thumbServo = 0;
const int indexServo = 1;
const int middleServo = 2;
const int ringServo = 3;
const int littleServo = 4;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  for( int i=0; i<7; i++){
    pwm.setPWM(i, 0,angleToPulse(180));
}
}

void receieveData() {
  while (Serial.available())
  {
    char c = Serial.read();
    if (c == '$') {
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength) {
        recievedSring = String(recievedSring + c);
        counter++;
      }
      if (counter >= stringLength) {
        //$00000
        for (int i = 0; i < numOfValsRec; i++)
        {
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = recievedSring.substring(num, num + digitsPerValRec).toInt();
        }
        recievedSring = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {
  receieveData();
  if (valsRec [0] == 1) {
    pwm.setPWM(thumbServo, 0,angleToPulse(0));
  } else {
    pwm.setPWM(thumbServo, 0,angleToPulse(105));
  }
  if (valsRec [1] == 1) {
    pwm.setPWM(indexServo, 0,angleToPulse(0));
  } else {
    pwm.setPWM(indexServo, 0,angleToPulse(105));
  }
  if (valsRec [2] == 1) {
    pwm.setPWM(middleServo, 0,angleToPulse(0));
  } else {
    pwm.setPWM(middleServo, 0,angleToPulse(105));
  }
  if (valsRec [3] == 1) {
    pwm.setPWM(ringServo, 0,angleToPulse(0));
  } else {
    pwm.setPWM(ringServo, 0,angleToPulse(105));
  }
  if (valsRec [4] == 1) {
    pwm.setPWM(littleServo, 0,angleToPulse(0));
  } else {
    pwm.setPWM(littleServo, 0,angleToPulse(105));
  }
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
//   Serial.print("Angle: ");Serial.print(ang);
//   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}
