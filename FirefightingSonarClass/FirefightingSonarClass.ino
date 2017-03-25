class Sonar{
	enum Sonar_State_Values {STARTUP_IDLE, SENSOR_IDLE, TRIGGER, TRIGGERING, ECHO_WAITING, ECHO_READING, ECHO_FINISHED}
	Sonar_State_Values Current_State;



	int Count_Trigger;

	long duration, cm;
	int Sonar_ID;
	int Trigger_Pin;
	int Echo_Pin;
	int Echo_Time;
	unsigned long Trigger_Timestamp;
	unsigned long Echo_Timestamp;
	const int TRIGGER_TIME;
	const int SONAR_TIMEOUT;

	public:

	Sonar(int Sonar_Name, Sonar_Trigger_Pin, Sonar_Echo_Pin, Requested_Reading){
		Sonar_ID = Sonar_Name;
		Trigger_Pin = Sonar_Trigger_Pin;
		Echo_Pin = Sonar_Echo_Pin;
		//Requested_Reading = false;
		Current_State = STARTUP_IDLE;   
	}

	int Get_Name()
	{
		return Sonar_ID;
	}

	void Request_Reading() {
		Trigger_Timestamp = micros();
		digitalWrite(Trigger_Pin, HIGH); 
		Current_State = TRIGGERING;
	}


	void Take_Reading(){
		switch(Current_State):

		Case STARTUP_IDLE:
		break;
		Case SENSOR_IDLE:
		break;
		Case TRIGGERING:
			//Waiting for time to finish triggering.
			if(micros()- Trigger_Timestamp >= TRIGGER_TIME)
			{
				digitalWrite(Trigger_Pin, LOW);
				Current_State = ECHO_WAITING;
			}
		break;
		Case ECHO_WAITING:
			//Waiting for sensor to respond
			if (digitalRead(Echo_Pin) == HIGH)
			{

				Echo_Timestamp = micros();
				Current_State = ECHO_READING;
			}
			else
			{
				if(micros()- Trigger_Timestamp >= SONAR_TIMEOUT)
				{
					// Set a timeout error or such.
					Current_State = SENSOR_IDLE;
				}
			}
		break;
		Case ECHO_READING:
			if (digitalRead(Echo_Pin) == LOW)
			{
				// Update the sensor value.
				duration = micros() - Echo_Timestamp;
				cm = ((duration/29)/2);
			}
			else
			{
				if(micros()- Trigger_Timestamp >= SONAR_TIMEOUT)
				{
					// Set a timeout error or such.
				}
			}
		Current_State = SENSOR_IDLE;
		break;
	}

	long getsonarvalue(){
		return cm;
	}

	void Ultrasonic_Trigger(){
		if (Requested_Reading == false){
			Requested_Reading = true;
		}
		else{
			//Some kind of wait period
			//Read current time
			//Compare to previous timestamp. If it is less than TRIGGER_TIME set LOW
		}       
	}
};
