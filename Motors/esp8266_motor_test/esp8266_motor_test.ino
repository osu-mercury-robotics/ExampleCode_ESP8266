#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rMotor = AFMS.getMotor(1), *lMotor = AFMS.getMotor(2);

void setup() {
  AFMS.begin();
  rMotor->setSpeed(0);   // 0 (stopped) - 255 (full speed)
  lMotor->setSpeed(0);  

}

void loop() {  
  rMotor->run(FORWARD);
  lMotor->run(FORWARD);
  delay(10);
}
