#include "Sonar.h" 
 Sonar::Sonar(int Sonar_Name, long local_x, long local_y, int Sonar_Trigger_Pin, int Sonar_Echo_Pin){
    Sonar_ID = Sonar_Name;
    Trigger_Pin = Sonar_Trigger_Pin;
    Echo_Pin = Sonar_Echo_Pin;
    Requested_Reading = false;
    Current_State = STARTUP_IDLE;
    readingUpdated = false;

    //Trigger_end = 0;
    //Echo_wait_time = 0;
    //Echo_end_time = 0;
	local_position.x = local_x; 
	local_postion.y = local_y;
  }

  int Sonar::Get_Name()
  {
    return Sonar_ID;
  }

  void Sonar::Request_Reading() {
    Trigger_Timestamp = micros();
    //digitalWrite(Trigger_Pin, HIGH); 
    Current_State = TRIGGERING;
    readingUpdated = false;
  }

  bool Sonar::readingAvailable(){
    return readingUpdated;
  }

  void Sonar::Take_Reading(){
    switch(Current_State){
      case STARTUP_IDLE:
        break;
      case SENSOR_IDLE:
        break;
      case TRIGGERING:
	    digitalWrite(Trigger_Pin, HIGH); 
	    delayMicroseconds(10);
	    digitalWrite(Trigger_Pin, LOW);
	    Current_State = ECHO_READING;
        //Waiting for time to finish triggering.
	//Trigger_end = micros();
        //if(micros()- Trigger_Timestamp >= TRIGGER_TIME)
        //{
          //digitalWrite(Trigger_Pin, LOW);
          //Current_State = ECHO_WAITING;
        //}
        //break;
      case ECHO_WAITING:
	//Echo_wait_time = micros();
        //Waiting for sensor to respond
        //if (digitalRead(Echo_Pin) == HIGH)
        //{
//
          //Echo_Timestamp = micros();
          //Current_State = ECHO_READING;
        //}
        //else
        //{
          //if(micros()- Trigger_Timestamp >= SONAR_TIMEOUT)
          //{
            //// Set a timeout error or such.
            //Current_State = SENSOR_IDLE;
          //}
        //}
        //break;
      case ECHO_READING:
          duration = pulseIn(Echo_Pin, HIGH);
          cm = ((duration/29)/2);
          readingUpdated = true;
	//Echo_end_time = micros();
        //if (digitalRead(Echo_Pin) == LOW)
        //{
          //// Update the sensor value.
          //duration = micros() - Echo_Timestamp;
          //cm = ((duration/29)/2);
          //readingUpdated = true;
        //}
        //else
        //{
          //if(micros()- Trigger_Timestamp >= SONAR_TIMEOUT)
          //{
            //// Set a timeout error or such.
          //}
        //}
      
      Current_State = SENSOR_IDLE;
        break;
    }
  }

  long Sonar::getsonarvalue(){
    return cm;
  }

  void Sonar::Ultrasonic_Trigger(){
    if (Requested_Reading == false){
      Requested_Reading = true;
    }
    else{
      //Some kind of wait period
      //Read current time
      //Compare to previous timestamp. If it is less than TRIGGER_TIME set LOW
    }       
  }

  XYCoordinate Sonar::GetPosition()
{
ruturn local_position;
}

	
  //unsigned long Sonar::trigger_time()
//{
	//return (Trigger_end - Trigger_Timestamp);
//}
  //unsigned long Sonar::echo_wait_time()
//{
	//return (Echo_wait_time - Trigger_end);
//}
  //unsigned long Sonar::echo_time()
//{
	//return (Echo_end_time - Echo_wait_time);
//}
