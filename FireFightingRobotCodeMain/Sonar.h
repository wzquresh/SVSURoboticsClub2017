#include <arduino.h>
//#include "XYCoordinate.h"
class Sonar{
  enum Sonar_State_Values {STARTUP_IDLE, SENSOR_IDLE, TRIGGER, TRIGGERING, ECHO_WAITING, ECHO_READING, ECHO_FINISHED};
  Sonar_State_Values Current_State;

  bool Requested_Reading;

  int Count_Trigger;

  long duration, cm;
  int Sonar_ID;
  int Trigger_Pin;
  int Echo_Pin;
  int Echo_Time;
  unsigned long Trigger_Timestamp;
  unsigned long Echo_Timestamp;
  const int TRIGGER_TIME = 10;
  const int SONAR_TIMEOUT = 600000;
  bool readingUpdated;
  //unsigned long Trigger_end;
  //unsigned long Echo_wait_time;
  //unsigned long Echo_end_time;
//XYCoordinate local_postion;
  public:

  Sonar(int Sonar_Name, long local_x, long local_y, int Sonar_Trigger_Pin, int Sonar_Echo_Pin);
  int Get_Name();

  void Request_Reading();

  bool readingAvailable();

  void Take_Reading();

  long getsonarvalue();

  void Ultrasonic_Trigger();

  //unsigned long trigger_time();
  //unsigned long echo_wait_time();
  //unsigned long echo_time();
//XYCoordinate GetPosition();
};
