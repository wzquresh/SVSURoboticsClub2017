#include "wheel_motors.h"

//
wheel_motors::wheel_motors(int motor_ID, int in1_4, int in2_3){
	speedpin=motor_ID;
	forwardpin=in1_4;
	reversepin=in2_3;
	pinMode(speedpin,OUTPUT);
	pinMode(forwardpin,OUTPUT);
	pinMode(reversepin,OUTPUT);
		
}

//direct 1= forwards, 0= backwards	
void wheel_motors::motors_action(int speeed, int direct){
	speed=speeed;
	direction=direct;
	
	if (speed>150){
		speed=150;
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