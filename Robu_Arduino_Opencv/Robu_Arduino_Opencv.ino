#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("16 channel Servo test!");

  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'a') {
   pwm.setPWM(11, 11, angleToPulse(90));
  pwm.setPWM(12, 12, angleToPulse(60));
  pwm.setPWM(13, 13, angleToPulse(80));      
  pwm.setPWM(14, 14, angleToPulse(170));
  pwm.setPWM(15, 15, angleToPulse(90));
    } else if (command == 'b') {
  pwm.setPWM(11, 11, angleToPulse(90));
  pwm.setPWM(12, 12, angleToPulse(70));
  pwm.setPWM(13, 13, angleToPulse(10));
  pwm.setPWM(14, 14, angleToPulse(110)); 
  pwm.setPWM(15, 15, angleToPulse(90));
    }
    else if (command == 'c') {
  pwm.setPWM(11, 11, angleToPulse(0));
  pwm.setPWM(12, 12, angleToPulse(70));
  pwm.setPWM(13, 13, angleToPulse(20));
  pwm.setPWM(14, 14, angleToPulse(95)); 
  pwm.setPWM(15, 15, angleToPulse(90));
    }
    else if (command == 'd') {
  pwm.setPWM(11, 11, angleToPulse(0));
  pwm.setPWM(12, 12, angleToPulse(70));
  pwm.setPWM(13, 13, angleToPulse(100));
  pwm.setPWM(14, 14, angleToPulse(80)); 
  pwm.setPWM(15, 15, angleToPulse(90));
  


    }
  }
}

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

int getCurrentAngle(int servo) {
  uint16_t pulse = pwm.getPWM(servo);
  int angle = map(pulse, SERVOMIN, SERVOMAX, 0, 180);
  return angle;
}
