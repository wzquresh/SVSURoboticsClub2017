#include "wheel_motors.h"

wheel_motors{,int motor_ID, int in1_3, int in2_4){
	speedpin=motor_ID;
	forwardpin=in1_3;
	reversepin=in2_4;
}
	
void wheel_motors::motors_action(int speeed, int direct){
	speed=speeed;
	direction=direct;
	
	if (speed>150){
		speed=150
	}
	if (direction==0){
		digitalWrite(forwardpin, LOW);
		digitalWrite(reversepin, HIGH);
		analogWrite(speedpin, speed);
	}
	if (direction==1){
		digitalWrite(forwardpin, HIGH);
		digitalWrite(reversepin, LOW);
		analogWrite(speedpin, speed);
	}
}