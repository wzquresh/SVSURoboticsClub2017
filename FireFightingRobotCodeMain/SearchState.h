#include <arduino.h>
#include "Debug_Toggles.h"
#include "Pins.h"
#include "CommandLoop.h"
#include "IR.h"
#include "bumpsensor.h"
#include "Sonar.h"
#include "wheel_motors.h"
#include "Fan_Motor_Control.h"


class SearchState:public CommandLoop{
  public:  
  //enum State{MIC_READ, SEARCH, END};
  //State current;
  enum FlameCases{NO_FLAME, ONE_FAR, ONE_CLOSE, BOTH_FAR, BOTH_CLOSE};
  FlameCases flameCase;
  enum BumpCase{FRONT, RIGHT, LEFT, REAR_R, REAR_L, NO_BUMP};
  BumpCase bumpCase;
  enum CollisionCases{GOOD, RIGHT_ENCROACHING, LEFT_ENCROACHING, FRONT_ENCROACHING, REAR_ENCROACHING};
  CollisionCases sonarCase;
  enum SonarState{sPrime, s1, s2, s3, s4, s5, s6};
  SonarState sonarState;

  //Inputs
  //FLOURESCENT LIGHT
  #define FLOURESCENT_LIGHTS
  #ifdef FLOURESCENT_LIGHTS
  const int RIGHT_MIN = 400;
  const int RIGHT_MAX = 780;
  const int LEFT_MIN = 600;
  const int LEFT_MAX = 850;
  #else
  //INCANDECENT LIGHT
  const int RIGHT_MIN = 110;
  const int RIGHT_MAX = 475;
  const int LEFT_MIN = 340;
  const int LEFT_MAX = 600;
  #endif
  
  enum MotorSpeeds{STOP = 0, SLOW = 80, MEDIUM = 90, FAST = 110};

  IR irRight;
  IR irLeft;

  Sonar sonarFront;
  Sonar sonarFrontR;
  Sonar sonarFrontL;
  Sonar sonarRear;
  Sonar sonarRearR;
  Sonar sonarRearL;

  Bump bumpFront;
  Bump bumpFrontR;
  Bump bumpFrontL;
  Bump bumpR;
  Bump bumpL;
  Bump bumpRearR;
  Bump bumpRearL;

  //Outputs
  wheel_motors motorR;
  wheel_motors motorL;
  
  bool fireExtinguished;

  //LED red(RedLED);
  //LED green(GreenLED);

  Fan_Motor_Control fan;


SearchState()
	: 
  irRight(RightIR, RIGHT_MIN, RIGHT_MAX),
  irLeft(LeftIR, LEFT_MIN, LEFT_MAX),

  sonarFront(1, FrontSonarTrigger, FrontSonarEcho),
  sonarFrontR(2, FrontRightSonarTrigger, FrontRightSonarEcho),
  sonarFrontL(3, FrontLeftSonarTrigger, FrontLeftSonarEcho),
  sonarRear(4, RearSonarEcho, RearSonarTrigger),
  sonarRearR(5, RightSonarTrigger, RightSonarEcho),
  sonarRearL(6, LeftSonarTrigger, LeftSonarEcho),

  bumpFront(FrontBump),
  bumpFrontR(FrontRightBump),
  bumpFrontL(FrontLeftBump),
  bumpR(RightBump),
  bumpL(LeftBump),
  bumpRearR(RearRightBump),
  bumpRearL(RearLeftBump),

  //Outputs
  motorR(RightMotor_Speed_Pin, RightMotor_Forward_Pin, RightMotor_Reverse_Pin),
  motorL(LeftMotor_Speed_Pin, LeftMotor_Forward_Pin, LeftMotor_Reverse_Pin),
  
  //LED red(RedLED);
  //LED green(GreenLED);

  fan(FanPWM)
{
    flameCase = NO_FLAME;
    sonarState = sPrime;
    bumpCase = NO_BUMP;
    sonarCase = GOOD;
    
    fireExtinguished = false;
 }
  
  void setup(){
  }

  int loop(){
#ifdef SEARCH_STATE_SONAR_CHECK_DEBUG
    Serial.print("Sonar Checking: ");
#endif
    sonarRun();
#ifdef SEARCH_STATE_SONAR_CHECK_DEBUG
    Serial.print("Sonar Done");
    Serial.print("\t");
#endif

#ifdef SEARCH_STATE_SONAR_SUMMARY_DEBUG
    Serial.print("Sonar Summary: ");
    Serial.print(sonarFront.getsonarvalue());
    Serial.print(" ");
    Serial.print(sonarFrontR.getsonarvalue());
    Serial.print(" ");
    Serial.print(sonarRearR.getsonarvalue());
    Serial.print(" ");
    Serial.print(sonarRear.getsonarvalue());
    Serial.print(" ");
    Serial.print(sonarRearL.getsonarvalue());
    Serial.print(" ");
    Serial.print(sonarFrontL.getsonarvalue());
    Serial.print("\t");
#endif

#ifdef SEARCH_STATE_BUMP_SUMMARY_DEBUG
    Serial.print("Bump Summary: ");
    Serial.print(bumpFront.getValue());
    Serial.print(" ");
    Serial.print(bumpFrontR.getValue());
    Serial.print(" ");
    Serial.print(bumpR.getValue());
    Serial.print(" ");
    Serial.print(bumpRearR.getValue());
    Serial.print(" ");
    Serial.print(bumpRearL.getValue());
    Serial.print(" ");
    Serial.print(bumpL.getValue());
    Serial.print(" ");
    Serial.print(bumpFrontL.getValue());
    Serial.print("\t");
#endif

#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    Serial.print("Bump Checking: ");
#endif
    if(bumpFront.getValue())
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    {
#endif
      bumpCase = FRONT;
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    	Serial.print("Bumped Front ");
    }
#endif
    else if(bumpFrontR.getValue() || bumpR.getValue())
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    {
#endif
      bumpCase = RIGHT;
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    	Serial.print("Bumped Front Right OR Right ");
    }
#endif
    else if(bumpFrontL.getValue() || bumpL.getValue())
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    {
#endif
      bumpCase = LEFT;
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    	Serial.print("Bumped Front Left OR Left ");
    }
#endif
    else if(bumpRearR.getValue())
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    {
#endif
      bumpCase = REAR_R;
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    	Serial.print("Bumped Rear Right ");
    }
#endif
    else if(bumpRearL.getValue())
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    {
#endif
      bumpCase = REAR_L;
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    	Serial.print("Bumped Rear Left ");
    }
#endif
    else
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    {
#endif
      bumpCase = NO_BUMP;
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    	Serial.print("No Bump ");
    }
#endif
#ifdef SEARCH_STATE_BUMP_CHECKING_DEBUG
    Serial.print("\t");
#endif


    //Proper call for motors: motorL.motors_action(speed, direction)
    //direction 1 forward, 0 backward
    
#ifdef SEARCH_STATE_BUMP_REACTION_DEBUG
    Serial.print("Bump Reaction ");
#endif
    switch(bumpCase){
      case FRONT:
        motorL.motors_action(SLOW, 0);
        motorR.motors_action(SLOW, 0);
        delay(50);
        if(sonarCase == LEFT_ENCROACHING){
          motorR.motors_action(SLOW, 0);
          motorL.motors_action(MEDIUM, 1);
          delay(40);
        //turn right for 40 ms then go
        }else{
          motorL.motors_action(SLOW, 0);
          motorR.motors_action(MEDIUM, 1);
          delay(30);
        }
        //turn left for 30 ms then go
        break;
      case RIGHT:
        motorL.motors_action(STOP, 1);
        motorR.motors_action(STOP, 1);
        motorL.motors_action(SLOW, 0);
        delay(38);
        motorR.motors_action(MEDIUM, 1);
        motorL.motors_action(MEDIUM, 1);
        break;
      case LEFT:
        motorL.motors_action(STOP, 1);
        motorR.motors_action(STOP, 1);
        motorR.motors_action(SLOW, 0);
        delay(24);
        motorL.motors_action(MEDIUM, 1);
        motorR.motors_action(MEDIUM, 1);
        break;
      case REAR_R:
        motorL.motors_action(STOP, 1);
        motorR.motors_action(STOP, 1);
        motorL.motors_action(SLOW, 1);
        delay(33);
        motorR.motors_action(SLOW, 1);
        break;
      case REAR_L:
        motorR.motors_action(STOP, 1);
        motorL.motors_action(STOP, 1);
        
        motorR.motors_action(SLOW, 1);
        delay(42);
        motorL.motors_action(SLOW, 1);
        break;
      default:
        break;    
    }

#ifdef SEARCH_STATE_BUMP_REACTION_DEBUG
    Serial.print("End Bump Reaction");
    Serial.print("\t");
#endif
    

#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
    Serial.print("Sonar Encroachment Check ");
#endif
    if(sonarFrontR.getsonarvalue() < 7 || sonarRearR.getsonarvalue() < 7)
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
  {
#endif
      sonarCase = RIGHT_ENCROACHING;
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
    Serial.print("Right Sonar ");
  }
#endif
    else if(sonarFrontL.getsonarvalue() < 7 || sonarRearL.getsonarvalue() < 7)
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
  {
#endif
      sonarCase = LEFT_ENCROACHING;
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
    Serial.print("Left Sonar ");
  }
#endif
    else if(sonarFront.getsonarvalue() < 7)
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
  {
#endif
      sonarCase = FRONT_ENCROACHING;
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
    Serial.print("Front Sonar ");
  }
#endif
    else if(sonarRear.getsonarvalue() < 7)
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
  {
#endif
      sonarCase = REAR_ENCROACHING;
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
    Serial.print("Rear Sonar ");
  }
#endif
    else
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
  {
#endif
      sonarCase = GOOD;
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
    Serial.print("None ");
  }
#endif

#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_CHECKING_DEBUG
    Serial.print("End Sonar Encroachment Check");
    Serial.print("\t");
#endif
    
#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_REACTION_DEBUG
    Serial.print("Sonar Encroachment Reaction ");
#endif
    switch(sonarCase){
      case GOOD:
        motorR.motors_action(MEDIUM, 1);
        motorL.motors_action(MEDIUM, 1);
        break;
      case FRONT_ENCROACHING:
        if(sonarFrontR.getsonarvalue() > 10){
          motorR.motors_action(SLOW, 0);
          motorL.motors_action(MEDIUM, 1);
        }
        else{
          motorL.motors_action(SLOW, 0);
          motorR.motors_action(MEDIUM, 1);
        }//else try back
        break;
      case RIGHT_ENCROACHING:
        //Go until opposite wall is <12 away
        motorR.motors_action(FAST, 1);      
        break;
      case LEFT_ENCROACHING:
        motorL.motors_action(FAST, 1);
        break;
      case REAR_ENCROACHING:
        if(sonarRearR.getsonarvalue() > 10){
          motorR.motors_action(FAST, 0);
        }else if(sonarRearL.getsonarvalue() > 10){
          motorL.motors_action(FAST, 0);
        }else{
          motorL.motors_action(SLOW, 1);
          motorR.motors_action(SLOW, 1);
        }
        break;
    }

#ifdef SEARCH_STATE_SONAR_ENCROACHMENT_REACTION_DEBUG
    Serial.print("End Sonar Encroachment Reaction");
    Serial.print("\t");
#endif

#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    Serial.print("Flame Check ");
#endif
    if(irRight.flameCase() == 0 && irLeft.flameCase() ==0)
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    {
#endif
      flameCase = NO_FLAME;
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    Serial.print("Not detected ");
    }
#endif
    if(irRight.flameCase() == 0 && irLeft.flameCase() == 1 || irRight.flameCase() == 1 && irLeft.flameCase() == 0)
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    {
#endif
      flameCase = ONE_FAR;
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    Serial.print("One far ");
    }
#endif
    if(irRight.flameCase() == 1 && irLeft.flameCase() == 1)
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    {
#endif
      flameCase = BOTH_FAR;
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    Serial.print("Both far ");
    }
#endif
    if(irRight.flameCase() == 0 && irLeft.flameCase() == 2 || irRight.flameCase() == 1 && irLeft.flameCase() == 2 || irRight.flameCase() == 2 && irLeft.flameCase() == 0 || irRight.flameCase() == 2 && irLeft.flameCase() == 1)
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    {
#endif
      flameCase = ONE_CLOSE;
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    Serial.print("One close ");
    }
#endif
    if(irRight.flameCase() == 2 && irLeft.flameCase() == 2)
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    {
#endif
      flameCase = BOTH_CLOSE;
#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    Serial.print("Both close ");
    }
#endif

#ifdef SEARCH_STATE_FLAME_DETECTION_DEBUG
    Serial.print("End Flame Check");
#endif
    
#ifdef SEARCH_STATE_FLAME_SUMMARY_DEBUG
    Serial.print("Flame Summary: ");
    Serial.print(irLeft.flameCase());
    Serial.print(" ");
    Serial.print(irRight.flameCase());
    Serial.print("\t");
#endif

#ifdef SEARCH_STATE_FLAME_REACTION_DEBUG
    Serial.print("Flame Reaction ");
#endif
    switch(flameCase){
      case NO_FLAME:
        digitalWrite(RedLED, LOW);//red.setValue(1);
        break;
      case ONE_FAR:
        digitalWrite(RedLED, HIGH);//red.setValue(1);
        motorR.motors_action(STOP, 1);
        motorL.motors_action(STOP, 1);
        if(irRight.flameCase() == 1){
          motorL.motors_action(SLOW, 1);
          motorR.motors_action(SLOW, 0);
        }
        else{
          motorR.motors_action(SLOW, 1);
          motorL.motors_action(SLOW, 0);
        }
        break;
      case BOTH_FAR:
        digitalWrite(RedLED, HIGH);//red.setValue(1);
        motorR.motors_action(SLOW, 1);
        motorL.motors_action(SLOW, 1);
        break;
      case ONE_CLOSE:
        digitalWrite(RedLED, HIGH);//red.setValue(1);
        if(irRight.flameCase() == 2){
          motorR.motors_action(SLOW, 0);
          motorL.motors_action(SLOW, 1);
        }else{
          motorL.motors_action(SLOW, 0);
          motorR.motors_action(SLOW, 1);
        }
        break;
      case BOTH_CLOSE:
        digitalWrite(RedLED, HIGH);//red.setValue(1);
        motorL.motors_action(STOP, 1);
        motorR.motors_action(STOP, 1);
        fan.Set_Value(1);
        delay(1000);
        fan.Set_Value(0);
        digitalWrite(GreenLED, LOW);
        digitalWrite(RedLED, LOW);
        delay(40);
        digitalWrite(RedLED, HIGH);
        delay(60);
        digitalWrite(RedLED, LOW);
        delay(50);
        digitalWrite(RedLED, HIGH);
        delay(25);
        digitalWrite(RedLED, LOW);
        fireExtinguished = true;
        //end robot
        break;
    }
#ifdef SEARCH_STATE_FLAME_REACTION_DEBUG
    Serial.print("End Flame Reaction");
    Serial.print("\t");
#endif
  }
  
  bool FireExtinguished(){
    return fireExtinguished;
  }
  
  void sonarRun(){
    switch(sonarState){
      case sPrime:
#ifdef SEARCH_STATE_SONAR_READING_DEBUG
        Serial.print("Priming Read");
#endif
        sonarFront.Request_Reading();
        sonarState = s1;
        break;
      case s1:
#ifdef SEARCH_STATE_SONAR_READING_DEBUG
        Serial.print("Sonar Case s1");
#endif
        sonarFront.Take_Reading();
        if(sonarFront.readingAvailable()){
          sonarFrontR.Request_Reading();
          sonarState = s2;
        }
        break;
      case s2:
#ifdef SEARCH_STATE_SONAR_READING_DEBUG
        Serial.print("Sonar Case s2");
#endif
        sonarFrontR.Take_Reading();
        if(sonarFrontR.readingAvailable()){
          sonarFrontL.Request_Reading();
          sonarState = s3;
        }
        break;
      case s3:
#ifdef SEARCH_STATE_SONAR_READING_DEBUG
        Serial.print("Sonar Case s3");
#endif
        sonarFrontL.Take_Reading();
        if(sonarFrontL.readingAvailable()){
          sonarRearR.Request_Reading();
          sonarState = s4;
        }
        break;
      case s4:
#ifdef SEARCH_STATE_SONAR_READING_DEBUG
        Serial.print("Sonar Case s4");
#endif
        sonarRearR.Take_Reading();
        if(sonarRearR.readingAvailable()){
          sonarRearL.Request_Reading();
          sonarState = s5;
        }
        break;
      case s5:
#ifdef SEARCH_STATE_SONAR_READING_DEBUG
        Serial.print("Sonar Case s5");
#endif
        sonarRearL.Take_Reading();
        if(sonarRearL.readingAvailable()){
          sonarRear.Request_Reading();
          sonarState = s6;
        }
        break;
      case s6:
#ifdef SEARCH_STATE_SONAR_READING_DEBUG
        Serial.print("Sonar Case s6");
#endif
        sonarRear.Take_Reading();
        if(sonarRear.readingAvailable()){
          sonarFront.Request_Reading();
          sonarState = s1;
        }
    }
  }
  
  static const int unique_id = 2;
  int id(){return unique_id;}
};
