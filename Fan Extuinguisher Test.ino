#include "Fan_Motor_Control.h"

Fan_Motor fanMotor1(5);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly: 
  fanMotor1.setValue(true);
  delay(1000);
  fanMotor1.setValue(false);
}