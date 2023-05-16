#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  90 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  630 // this is the 'maximum' pulse length count (out of 4096)
uint8_t servonum = 0;
String text;
void setup() {

  Serial.begin(9600);// put your setup code here, to run once:

  pwm.begin();

  pwm.setPWMFreq(60);
}

void loop() {
  while (Serial.available())
  {
    delay(10);
    char c = Serial.read();
    text += c;
  }
  delay(1000);
  Serial.println(text);
  if (text.length() > 0)
  {
    if (text == "open")
    {
      for ( int i = 0; i < 7; i++) {
        pwm.setPWM(i, 0, angleToPulse(0));
        delay(10);
      }
    }
    if (text == "close")
    {
      for ( int i = 0; i < 7; i++) {
        pwm.setPWM(i, 0, angleToPulse(100));
        delay(10);
      }
    }
    if (text == "one")
    {
      pwm.setPWM(0, 0, angleToPulse(100));
      pwm.setPWM(1, 0, angleToPulse(0));
      pwm.setPWM(2, 0, angleToPulse(100));
      pwm.setPWM(3, 0, angleToPulse(100));
      pwm.setPWM(4, 0, angleToPulse(100));
    }
    if (text == "two")
    {
      pwm.setPWM(0, 0, angleToPulse(100));
      pwm.setPWM(1, 0, angleToPulse(0));
      pwm.setPWM(2, 0, angleToPulse(0));
      pwm.setPWM(3, 0, angleToPulse(100));
      pwm.setPWM(4, 0, angleToPulse(100));
    }
    if (text == "three")
    {
      pwm.setPWM(0, 0, angleToPulse(100));
      pwm.setPWM(1, 0, angleToPulse(0));
      pwm.setPWM(2, 0, angleToPulse(0));
      pwm.setPWM(3, 0, angleToPulse(0));
      pwm.setPWM(4, 0, angleToPulse(100));
    }
    if (text == "four")
    {
      pwm.setPWM(0, 0, angleToPulse(100));
      pwm.setPWM(1, 0, angleToPulse(0));
      pwm.setPWM(2, 0, angleToPulse(0));
      pwm.setPWM(3, 0, angleToPulse(0));
      pwm.setPWM(4, 0, angleToPulse(0));
    }
    if (text == "five")
    {
      for ( int i = 0; i < 7; i++) {
        pwm.setPWM(i, 0, angleToPulse(0));
        delay(10);
      }
      if (text == "thumbs up")
      {
        pwm.setPWM(0, 0, angleToPulse(0));
        pwm.setPWM(1, 0, angleToPulse(100));
        pwm.setPWM(2, 0, angleToPulse(100));
        pwm.setPWM(3, 0, angleToPulse(100));
        pwm.setPWM(4, 0, angleToPulse(100));
      }
      if (text == "good")
      {
        pwm.setPWM(0, 0, angleToPulse(100));
        pwm.setPWM(1, 0, angleToPulse(100));
        pwm.setPWM(2, 0, angleToPulse(0));
        pwm.setPWM(3, 0, angleToPulse(0));
        pwm.setPWM(4, 0, angleToPulse(0));
      }
      if (text == "call of nature")
      {
        pwm.setPWM(0, 0, angleToPulse(100));
        pwm.setPWM(1, 0, angleToPulse(100));
        pwm.setPWM(2, 0, angleToPulse(100));
        pwm.setPWM(3, 0, angleToPulse(100));
        pwm.setPWM(4, 0, angleToPulse(0));
      }
      if (text == "rotate")
      {
        pwm.setPWM(7, 0, angleToPulse(40));

      }
      if (text == "back")
      {
        pwm.setPWM(7, 0, angleToPulse(0));

      }
      text = "";
    }

  }
}
int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
  //   Serial.print("Angle: ");Serial.print(ang);
  //   Serial.print(" pulse: ");Serial.println(pulse);
  return pulse;
}
