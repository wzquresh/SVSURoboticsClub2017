#include <arduino.h>
#include "Fan_Motor_Control.h"

int fan_pin = 11;

Fan_Motor_Control fanMotor1(fan_pin);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Ready");
	Serial.print("Pin is ");
	Serial.println(fan_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Turning the fan on.");
  fanMotor1.Set_Value(true);
  delay(1000);
  Serial.println("Turning the fan off.");
  fanMotor1.Set_Value(false);
  while(1);
}
