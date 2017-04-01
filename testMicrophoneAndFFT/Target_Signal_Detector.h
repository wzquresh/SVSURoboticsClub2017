#include <defs.h>
#include <types.h>
#include <arduinoFFT.h>
#include "microphone.h"

class Target_Signal_Detector
{
	const Microphone_Sensor* microphone_ptr;
	const double MIN_TARGET_FREQUENCY, MAX_TARGET_FREQUENCY;
	static const uint16_t MAX_NUMBER_OF_SAMPLES = 128;
	const uint16_t max_current_sample_group = 10;

	arduinoFFT FFT; /* Create FFT object */

	double samples_real[MAX_NUMBER_OF_SAMPLES];
	double samples_imag[MAX_NUMBER_OF_SAMPLES];
	//double* samples_real;
	//double* samples_imag;

	uint16_t current_sample_number;
	uint16_t current_sample_group;

	unsigned long sampling_beginning_time;
	double samplingFrequency;

	double avg_total;
	double target_avg_total;
	int target_avg_count;

	static const uint16_t MAX_FIR_SAMPLE_SIZE = 10;
	static const double FIR_FILTER_THRESHOLD = 0.05;

	double FIR_Samples[MAX_FIR_SAMPLE_SIZE];
	int FIR_Sample_Head;

	void reset_window();
	void setup();
	void OurPrintVector(double *vData, uint8_t bufferSize, uint8_t scaleType);

	void FIR_Samples_Insert(double in);
	void FIR_Samples_reset();
	double FIR_Samples_Calculate_Result();

public:  // Note:  publicly for now, private later.
	void loop();

	public:
		Target_Signal_Detector(Microphone_Sensor* pointer_to_microphone, double minimum_target_frequency, double maximum_target_frequency);//, uint16_t maximum_samples_per_sampling_window, uint16_t max_sampling_window_grouping); 
};
