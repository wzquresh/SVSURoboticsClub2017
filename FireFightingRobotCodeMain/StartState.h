#include "CommandLoop.h"
#include "Target_Signal_Detector.h"

class StartState::public CommandLoop{
  const uint16_t TARGET_FREQUENCY(3800);
  const uint16_t MIN_WINDOW_FREQUENCY(0.87 * TARGET_FREQUENCY);
  const uint16_t MAX_WINDOW_FREQUENCY(1.13 * TARGET_FREQUENCY);
 
  Microphone_Sensor microphone1(1, 1);
  Target_Signal_Detector frequency_detector1(&microphone1, MIN_WINDOW_FREQUENCY, MAX_WINDOW_FREQUENCY);

  Target_Signal_Detector* frequency_detector(&frequency_detector1);
  static const int unique_id = 1;
  bool ReceivedTargetSound(){}
  int id(){return unique_id;}
  void setup(){}
  void loop(){	frequency_detector->loop();}
};