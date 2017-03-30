#include "wheel_motors.h"

wheel_motors *motorR;
wheel_motors *motorL;


void setup() {
  // put your setup code here, to run once:
  motorR = new wheel_motors(2,24,22);
  motorL = new wheel_motors(3,28,26);

}

void loop() {
  // put your main code here, to run repeatedly:

motorL->motors_action(55,1);
delay(1000);
motorL->motors_action(0,1);
delay(2000);
motorR->motors_action(55,1);
delay(1000);
motorR->motors_action(0,1);
delay(2000);

for(int i = 0; i< 150;++i){
motorR->motors_action(i,1);
motorL->motors_action(i,1);
delay(100);
}
for(int i = 0; i< 150;++i){
motorR->motors_action(i,0);
motorL->motors_action(i,0);
delay(100);
}
motorR->motors_action(0,1);
motorL->motors_action(0,1);
while(1);

}
