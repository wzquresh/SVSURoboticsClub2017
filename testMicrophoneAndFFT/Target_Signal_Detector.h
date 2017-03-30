#include <defs.h>
#include <types.h>
#include <arduinoFFT.h>
#include "microphone.h"

class Target_Signal_Detector
{
	const Microphone_Sensor* microphone_ptr;
	const double MIN_TARGET_FREQUENCY, MAX_TARGET_FREQUENCY;
	const uint16_t MAX_NUMBER_OF_SAMPLES;

	arduinoFFT FFT; /* Create FFT object */

	double samples_real[MAX_NUMBER_OF_SAMPLES];
	double samples_imag[MAX_NUMBER_OF_SAMPLES];

	uint16_t current_sample_number;
	const uint16_t max_current_sample_group = 10;
	uint16_t current_sample_group;

	unsigned long sampling_beginning_time;
	double samplingFrequency;

	double avg_total;


	void reset_window();
	void setup();
	void loop();
public:  // Note to Mark:  publicly for now, private later.
	void OurPrintVector(double *vData, uint8_t bufferSize, uint8_t scaleType);

	public:
		Target_Signal_Detector(Microphone_Sensor* pointer_to_microphone, double minimum_target_frequency, double maximum_target_frequency, uint_16t maximum_samples_per_sampling_window); 
};
