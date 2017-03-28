#include <arduino.h>
#include "Fan_Motor_Control.h"

Fan_Motor_Control::Fan_Motor_Control(int PWM_Pin)
{
	Pwm_Pin = PWM_Pin;
	//pinMode(Pwm_Pin, OUTPUT);
}

void Fan_Motor_Control::Set_Value(bool setValue){
	if(setValue == true)
		analogWrite(Pwm_Pin, 255);
	else
		analogWrite(Pwm_Pin, 0);
}
