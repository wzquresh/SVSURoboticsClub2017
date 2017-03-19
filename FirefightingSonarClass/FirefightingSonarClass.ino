class Sonar{
  private:
    enum Sonar_State_Values {SENSOR_IDLE, TRIGGER, TRIGGERING, ECHO_WAITING, ECHO_READING, ECHO_FINISHED}
    Sonar_State_Values Current_State;
    
    
    
    int Count_Trigger;
    
    long duration, cm;
    int Sonar_ID;
    int Trigger_Pin;
    int Echo_Pin;
    int Echo_Time;
    unsigned long Trigger_Timestamp;
    const int TRIGGER_TIME;
    const int SONAR_TIMEOUT;
  public:
   
    Sonar(int Sonar_Name, Sonar_Trigger_Pin, Sonar_Echo_Pin, Requested_Reading){
      Sonar_ID = Sonar_Name;
      Trigger_Pin = Sonar_Trigger_Pin;
      Echo_Pin = Sonar_Echo_Pin;
      //Requested_Reading = false;
      Current_State = SENSOR_IDLE;   
    }
       void Take_Reading(){
    switch(Current_State):
    
    Case SENSOR_IDLE:
      //Something will switch the state
      Current_State = TRIGGER;
      break;
    Case TRIGGER:
     digitalWrite(Trigger_Pin, HIGH); 
      Current_State = TRIGGERING;
      break;
    Case TRIGGERING:
     //Waiting for time out 
    Current_State = ECHO_WAITING;
    break;
    Case ECHO_WAITING:
   //Waiting for time out 
    Current_State = ECHO_READING;
    break;
    Case ECHO_READING:
     duration = digitalWrite(Echo_Pin, HIGH);
      cm = ((duration/29)/2);
      
    Current_State = SENSOR_IDLE;
    break;
    
    }
    
    long getsonarvalue(){
      return cm;
    }
  
    void Ultrasonic_Trigger(){
      if (Requested_Reading == false){
      Trigger_Timestamp = micros();
      digitalWrite (Trigger_Pin, HIGH);
      Requested_Reading = true;
      }
      else{
      //Some kind of wait period
      //Read current time
      //Compare to previous timestamp. If it is less than TRIGGER_TIME set LOW
      if(micros()- Trigger_Timestamp >= TRIGGER_TIME)
        digitalWrite(Trigger_Pin, LOW);
      }       
    }
    
    void Echo_Wait();
    
    void Echo_Read();
    
    int Sonar_Value();
    
}
