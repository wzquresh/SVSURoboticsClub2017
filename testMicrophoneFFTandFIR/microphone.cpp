#include "microphone.h"

	Microphone_Sensor::Microphone_Sensor(int microphone_ID, int microphone_pin)
    : ID(microphone_ID), pin(microphone_pin)
	{
		//ID = microphone_ID;
		//pin = microphone_pin;
		pinMode(pin, INPUT);
	}
	int Microphone_Sensor::get_id()
	{
		return ID;
	}
	int Microphone_Sensor::get_value()
	{
		return analogRead(pin);
	}
