#include <defs.h>
#include <types.h>
#include <arduinoFFT.h>


/*
   Example of use of the FFT libray
   Copyright (C) 2014 Enrique Condes
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "microphone.h"

const int MICROPHONE1_PIN(1);

Microphone_Sensor microphone1(1, MICROPHONE1_PIN);


arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
/*
   These values can be changed in order to evaluate the functions
 */
const uint16_t MAX_NUMBER_OF_SAMPLES = 128; //This value MUST ALWAYS be a power of 2
double signalFrequency = 3800; //was 1000
double samplingFrequency = 7600; //was 5000  // We _HOPE_ it's at least 7.6kHz!!!!!
uint8_t amplitude = 100;
/*
   These are the input and output vectors
   Input vectors receive computed results from FFT
 */
double samples_real[MAX_NUMBER_OF_SAMPLES];
double samples_imag[MAX_NUMBER_OF_SAMPLES];
uint16_t current_sample_number = 0;

const uint16_t max_current_sample_group = 10;
uint16_t current_sample_group = 0;

double avg_total = 0;
unsigned long sampling_beginning_time;

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

#define Theta 6.2831 //2*Pi

void reset_window()
{
	for (uint8_t i = 0; i < MAX_NUMBER_OF_SAMPLES; i++)
	{
		samples_real[i] = 0;
		samples_imag[i] = 0;
	}
	current_sample_number = 0;
}

void setup()
{

	Serial.begin(19200);
	Serial.println("Ready");

	for (uint8_t i = 0; i < MAX_NUMBER_OF_SAMPLES; i++)
	{
		samples_real[i] = 0;
		samples_imag[i] = 0;
	}
// Serial.println("got to this point");
	current_sample_number = 0;
	sampling_beginning_time = 0;
}


void loop()
{
	if(current_sample_number == 0)
	{
		sampling_beginning_time = micros();
	}

	if(current_sample_number == MAX_NUMBER_OF_SAMPLES)
	{
		unsigned long sampling_window_time = micros() - sampling_beginning_time;
		samplingFrequency = (1000000 * current_sample_number) / double(sampling_window_time);

		//Build raw data 
		//double cycles = (((current_sample_number-1) * signalFrequency) / samplingFrequency); //Number of signal cycles that the sampling will read
		//for (uint8_t i = 0; i < current_sample_number; i++)
		//{
		//samples_real[i] = int8_t((amplitude * (sin((i * (Theta * cycles)) / current_sample_number))) / 2.0);// Build data with positive and negative values
		//samples_real[i] = uint8_t((amplitude * (sin((i * (6.2831 * cycles)) / current_sample_number) + 1.0)) / 2.0);//Build data displaced on the Y axis to include only positive values
		//}
		//Serial.println("Data:");
		//PrintVector(samples_real, current_sample_number, SCL_TIME);
		FFT.Windowing(samples_real, current_sample_number, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	// Weigh data 
		//Serial.println("Weighed data:");
		//PrintVector(samples_real, current_sample_number, SCL_TIME);
		FFT.Compute(samples_real, samples_imag, current_sample_number, FFT_FORWARD); // Compute FFT 
		//Serial.println("Computed Real values:");
		//PrintVector(samples_real, current_sample_number, SCL_INDEX);
		//Serial.println("Computed Imaginary values:");
		//PrintVector(samples_imag, current_sample_number, SCL_INDEX);
		FFT.ComplexToMagnitude(samples_real, samples_imag, current_sample_number); // Compute magnitudes 
		//Serial.println("Computed magnitudes:");
		//PrintVector(samples_real, (current_sample_number >> 1), SCL_FREQUENCY);
		//double x = FFT.MajorPeak(samples_real, current_sample_number, samplingFrequency);
		//Serial.println(x, 6);
		//double avg_sampling_time = sampling_window_time / double(current_sample_number);
		//Serial.print("Calculated sampling frequency:  ");
		//Serial.println(calculated_sampling_frequency);
		/*
		if(current_sample_group < max_current_sample_group)
		{
			OurPrintVector(samples_real, (current_sample_number >> 1), SCL_FREQUENCY);
			++current_sample_group;
			current_sample_number = 0;
		}
		else
			while(1); // Run Once 
		*/
			OurPrintVector(samples_real, (current_sample_number >> 1), SCL_FREQUENCY);
			reset_window();
    
    /*
    for(int i = 0; i < MAX_NUMBER_OF_SAMPLES; i++) {
      Serial.println(samples_real[i]);
    }*/
    //while(1);
	}
	else
	{
		//delayMicroseconds(20);
		samples_real[current_sample_number++] = microphone1.get_value();
	}
}

void PrintVector(double *vData, uint8_t bufferSize, uint8_t scaleType)
{
	for (uint16_t i = 0; i < bufferSize; i++)
	{
		double abscissa;
		/* Print abscissa value */
		switch (scaleType)
		{
			case SCL_INDEX:
				abscissa = (i * 1.0);
				break;
			case SCL_TIME:
				abscissa = ((i * 1.0) / samplingFrequency);
				break;
			case SCL_FREQUENCY:
				abscissa = ((i * 1.0 * samplingFrequency) / MAX_NUMBER_OF_SAMPLES);
				break;
		}
		Serial.print(abscissa, 6);
		Serial.print(" ");
		Serial.print(vData[i], 4);
		Serial.println();
	}
	Serial.println();
}

void OurPrintVector(double *vData, uint8_t bufferSize, uint8_t scaleType)
{
	avg_total = 0;
	for(uint16_t i = 0; i < bufferSize; ++i)
		avg_total += vData[i];
	for (uint16_t i = 0; i < bufferSize; i++)
	{
		double abscissa;
		/* Print abscissa value */
		switch (scaleType)
		{
			case SCL_INDEX:
				abscissa = (i * 1.0);
				break;
			case SCL_TIME:
				abscissa = ((i * 1.0) / samplingFrequency);
				break;
			case SCL_FREQUENCY:
				abscissa = ((i * 1.0 * samplingFrequency) / MAX_NUMBER_OF_SAMPLES);
				break;
		}
		if(i > bufferSize - 11){
			Serial.print(abscissa, 0);
			Serial.print("\t");
			Serial.print((vData[i] * 100)/ avg_total, 4);
			Serial.print("\t");
		}
	}
	Serial.print("\t");
	Serial.print(avg_total/bufferSize,4);
	Serial.println();
}
