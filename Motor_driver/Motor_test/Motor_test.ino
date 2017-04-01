#include "wheel_motors.h"

wheel_motors *motorR;
wheel_motors *motorL;
enum speed {halt = 0, low = 75, medium = 85, high = 110};

void turnRightDelay(int ms){
  motorR->motors_action(medium,1);
  motorL->motors_action(medium,0);
  delay(ms);
  motorR->motors_action(halt,1);
  motorL->motors_action(halt,1);
 }
void turnLeftDelay(int ms){
  motorR->motors_action(medium,0);
  motorL->motors_action(medium,1);
  delay(ms);
  motorR->motors_action(halt,1);
  motorL->motors_action(halt,1);
}
 void driveSpeedDelay(speed  speeed, int ms){
  motorR->motors_action(speeed,1);
  motorL->motors_action(speeed,1);
  delay(ms);
  motorR->motors_action(halt,1);
  motorL->motors_action(halt,1);
}
void reverseSpeedDelay(speed  speeed, int ms){
  motorR->motors_action(speeed,0);
  motorL->motors_action(speeed,0);
  delay(ms);
  motorR->motors_action(halt,1);
  motorL->motors_action(halt,1);
 }

void setup() {
  // put your setup code here, to run once:
  motorR = new wheel_motors(2,24,22);
  motorL = new wheel_motors(3,28,26);
}

void loop() {
  // put your main code here, to run repeatedly:
  turnRightDelay(2000);
  delay(2000);
  turnLeftDelay(2000);
  delay(2000);
  driveSpeedDelay(low,2000);
  delay(2000);
  reverseSpeedDelay(low,2000);
  delay(2000);
  driveSpeedDelay(medium,2000);
  delay(2000);
  reverseSpeedDelay(medium,2000);
  delay(2000);
  driveSpeedDelay(high,2000);
  delay(2000);
  reverseSpeedDelay(high,2000);
  while(1);
}
