// Microphone_Sensor
// Written by Michael Gubody on March 25, 2017.
// 
// This microphone class holds an arbitrary reference number (an integer) 
// and the Arduino board pin location to the particular microphone's 
// analog output.  
// The microphone currently being used takes a power voltage, with value 
// specified as VCC, and will return an analog output based on the sound 
// level detected.  The level of output without detectable sound is given 
// as the value of VCC/2, ie. half of the power voltage, with sound 
// vibration above and below this value.  
class Microphone_Sensor
{
		const int ID;
		const int pin;
	
	public:
		Microphone_Sensor(int microphone_ID, int microphone_pin)
		{
			ID = microphone_ID;
			pin = microphone_pin;
		}
		
		// get_id
		// Returns an identifier for the microphone referred to by the particular instance of the object.
		int get_id()
		{
			return ID;
		}
		
		// get_value
		// Returns the analog value read from the microphone sensor.
		int get_value()
		{
			return analogRead(pin);
		}
};
