#include "Target_Window_Detector.h"


#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

#define Theta 6.2831 //2*Pi


Target_Window_Detector::Target_Signal_Detector(Microphone_Sensor* pointer_to_microphone, double minimum_target_frequency, double maximum_target_frequency, uint_16t maximum_samples_per_sampling_window)
	: microphone_ptr(pointer_to_microphone), MIN_TARGET_FREQUENCY(minimum_target_frequency), MAX_TARGET_FREQUENCY(maximum_target_frequency), MAX_NUMBER_OF_SAMPLES(maximum_samples_per_sampling_window)
{
	reset_window();
}


void Target_Window_Detector::reset_window()
{
	for (uint8_t i = 0; i < MAX_NUMBER_OF_SAMPLES; i++)
	{
		samples_real[i] = 0;
		samples_imag[i] = 0;
	}
	current_sample_number = 0;
}


void Target_Window_Detector::setup()
{
	Serial.println("Ready");

	for (uint8_t i = 0; i < MAX_NUMBER_OF_SAMPLES; i++)
	{
		samples_real[i] = 0;
		samples_imag[i] = 0;
	}
	current_sample_number = 0;
	sampling_beginning_time = 0;
}


void Target_Window_Detector::loop()
{
	if(current_sample_number == 0)
	{
		sampling_beginning_time = micros();
	}

	if(current_sample_number == MAX_NUMBER_OF_SAMPLES)
	{
		unsigned long sampling_window_time = micros() - sampling_beginning_time;
		samplingFrequency = (1000000 * current_sample_number) / double(sampling_window_time);

		//Serial.println("Data:");
		//PrintVector(samples_real, current_sample_number, SCL_TIME);
		FFT.Windowing(samples_real, current_sample_number, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	// Weigh data 
		/*
		Serial.println("Weighed data:");
		PrintVector(samples_real, current_sample_number, SCL_TIME);
		*/
		FFT.Compute(samples_real, samples_imag, current_sample_number, FFT_FORWARD); // Compute FFT 
		/*
		Serial.println("Computed Real values:");
		PrintVector(samples_real, current_sample_number, SCL_INDEX);
		Serial.println("Computed Imaginary values:");
		PrintVector(samples_imag, current_sample_number, SCL_INDEX);
		*/
		FFT.ComplexToMagnitude(samples_real, samples_imag, current_sample_number); // Compute magnitudes 
		/*
		Serial.println("Computed magnitudes:");
		PrintVector(samples_real, (current_sample_number >> 1), SCL_FREQUENCY);
		double x = FFT.MajorPeak(samples_real, current_sample_number, samplingFrequency);
		Serial.println(x, 6);
		double avg_sampling_time = sampling_window_time / double(current_sample_number);
		Serial.print("Calculated sampling frequency:  ");
		Serial.println(calculated_sampling_frequency);
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


void Target_Window_Detector::OurPrintVector(double *vData, uint8_t bufferSize, uint8_t scaleType)
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
