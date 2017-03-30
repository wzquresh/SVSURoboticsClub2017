#include <arduino.h>

class wheel_motors{
	private:
		// motor pins
		int speedpin;
		int forwardpin;
		int reversepin;
		int direction; // 1=forwards 0=backwards
		int speed;

	public:
		wheel_motors( int motor_ID, int in1_4, int in2_3);
		void motors_action(int speeed, int direct);
	

};