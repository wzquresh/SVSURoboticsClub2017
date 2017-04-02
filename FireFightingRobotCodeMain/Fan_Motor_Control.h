class Fan_Motor_Control {
	int Pwm_Pin;

public:
	Fan_Motor_Control(int PWM_Pin);
	void Set_Value(bool setValue);
};
