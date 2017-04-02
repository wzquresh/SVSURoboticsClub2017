#include "CommandLoop.h"
#include "Target_Signal_Detector.h"

class StartState::public CommandLoop{
  
 
  Microphone_Sensor microphone1;
  Target_Signal_Detector frequency_detector1;//(&microphone1, MIN_WINDOW_FREQUENCY, MAX_WINDOW_FREQUENCY);
  bool receivedSound;
  static const int unique_id = 1;
  
  //Target_Signal_Detector* frequency_detector;//(&frequency_detector1);
  
  StartState(int mic_id, int mic_pin, uint16_t target_freqency, uint16_t min_window_frequency, uint16_t max_window_frequency)
    : microphone1(mic_id, mic_pin), frequency_detector1(&microphone1, min_window_frequency, max_window_frequency)
  {
    receivedSound = false;
  }

  bool ReceivedTargetSound(){return receivedSound;}
  int id(){return unique_id;}
  void setup(){}
  void loop(){
    receivedSound = frequency_detector1.loop();
  }
};