#include <arduino.h>
#include "CommandLoop.h"
#include "IR.h"
#include "bumpsensor.h"
#include "Sonar.h"
#include "wheel_motors.h"
#include "Fan_Motor_Control.h"
//#include "Pins.h"

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
//Pins
  int Microphone_Pin = 3; //Analog (read, ie "ANALOG IN")

  // Wheel Motor Pins
  int RightMotor_Speed_Pin = 2;
  int RightMotor_Forward_Pin = 24;
  int RightMotor_Reverse_Pin = 22;
  int LeftMotor_Speed_Pin = 3;
  int LeftMotor_Forward_Pin = 28;
  int LeftMotor_Reverse_Pin = 26;

  //LED's
  // NB:  MOVE GreenLED TO APPROPRIATE LOCATION IN CODE

  int GreenLED = 34;
  int RedLED = 36;

  //SONAR SENSOR PINS -- 6 total
  int FrontSonarEcho = 51;
  int FrontSonarTrigger = 50;
  int FrontRightSonarEcho = 49;
  int FrontRightSonarTrigger = 48;
  int FrontLeftSonarEcho = 53;
  int FrontLeftSonarTrigger = 52;
  int RearSonarEcho = 43;
  int RearSonarTrigger = 42;
  int RightSonarEcho = 45;
  int RightSonarTrigger = 44;
  int LeftSonarEcho = 47;
  int LeftSonarTrigger = 46;

  //BUMP SENSOR PINS -- 7 total
  int FrontBump = 41;
  int FrontRightBump = 38;
  int FrontLeftBump = 40;
  int RightBump = 30;
  int LeftBump = 39;
  int RearRightBump = 32;
  int RearLeftBump = 37;

  //IR SENSOR PINS
  int RightIR = 0; //Analog
  int LeftIR = 1;  //Analog

  //FAN PIN
  int FanPWM = 0;

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
 }
  
  void setup(){
    flameCase = NO_FLAME;
    sonarState = sPrime;
    bumpCase = NO_BUMP;
    sonarCase = GOOD;
    
    fireExtinguished = false;
    
    //pinMode(Microphone_Pin, INPUT);
    //pinMode(RightMotor, OUTPUT);
    //pinMode(LeftMotor, OUTPUT);
    
    pinMode(GreenLED, OUTPUT);
    pinMode(RedLED, OUTPUT);
    
    pinMode(FrontSonarEcho, INPUT);
    pinMode(FrontSonarTrigger, OUTPUT);
    pinMode(FrontRightSonarEcho,INPUT);
    pinMode(FrontRightSonarTrigger, OUTPUT);
    pinMode(FrontLeftSonarEcho, INPUT);
    pinMode(FrontLeftSonarTrigger, OUTPUT);
    pinMode(RearSonarEcho, INPUT);
    pinMode(RearSonarTrigger, OUTPUT);
    pinMode(RightSonarEcho, INPUT);
    pinMode(RightSonarTrigger, OUTPUT);
    pinMode(LeftSonarEcho, INPUT);
    pinMode(LeftSonarTrigger, OUTPUT);
    
    
    pinMode(FrontBump, INPUT);
    pinMode(FrontRightBump, INPUT);
    pinMode(FrontLeftBump, INPUT);
    pinMode(RightBump, INPUT);
    pinMode(LeftBump, INPUT);
    pinMode(RearRightBump, INPUT);
    pinMode(RearLeftBump, INPUT);
    
    
    pinMode(RightIR, INPUT);
    pinMode(LeftIR, INPUT);
    
    
    pinMode(FanPWM, OUTPUT);
  }
  int loop(){
    //Serial.print("Searching");
    sonarRun();
    //Serial.print("Checking");
    if(bumpFront.getValue())
      bumpCase = FRONT;
    else if(bumpFrontR.getValue() || bumpR.getValue())
      bumpCase = RIGHT;
    else if(bumpFrontL.getValue() || bumpL.getValue())
      bumpCase = LEFT;
    else if(bumpRearR.getValue())
      bumpCase = REAR_R;
    else if(bumpRearL.getValue())
      bumpCase = REAR_L;
    else
      bumpCase = NO_BUMP;
    //Serial.print("END BUMP CHECK");
    //Proper call for motors: motorL.motors_action(speed, direction)
    //direction 1 forward, 0 backward
    
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

    //Serial.print("END BUMP CASE");
    
    if(sonarFrontR.getsonarvalue() < 7 || sonarRearR.getsonarvalue() < 7)
      sonarCase = RIGHT_ENCROACHING;
    else if(sonarFrontL.getsonarvalue() < 7 || sonarRearL.getsonarvalue() < 7)
      sonarCase = LEFT_ENCROACHING;
    else if(sonarFront.getsonarvalue() < 7)
      sonarCase = FRONT_ENCROACHING;
    else if(sonarRear.getsonarvalue() < 7)
      sonarCase = REAR_ENCROACHING;
    else
      sonarCase = GOOD;
    //Serial.print(sonarCase);

    //Serial.print("END SONAR CHECK");
    
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
        motorR.motors_action(FAST, 1);//Change back to 1 when done checking 
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

    //Serial.print("END SONAR CASE");

    if(irRight.flameCase() == 0 && irLeft.flameCase() ==0)
      flameCase = NO_FLAME;
    if(irRight.flameCase() == 0 && irLeft.flameCase() == 1 || irRight.flameCase() == 1 && irLeft.flameCase() == 0)
      flameCase = ONE_FAR;
    if(irRight.flameCase() == 1 && irLeft.flameCase() == 1)
      flameCase = BOTH_FAR;
    if(irRight.flameCase() == 0 && irLeft.flameCase() == 2 || irRight.flameCase() == 1 && irLeft.flameCase() == 2 || irRight.flameCase() == 2 && irLeft.flameCase() == 0 || irRight.flameCase() == 2 && irLeft.flameCase() == 1)
      flameCase = ONE_CLOSE;
    if(irRight.flameCase() == 2 && irLeft.flameCase() == 2)
      flameCase = BOTH_CLOSE;

    //Serial.print("END FLAME CHECK");
    
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
        //break;
    }
    //Serial.print("END FLAME CASE");
  }
  
  bool FireExtinguished(){
    return fireExtinguished;
  }
  
  void sonarRun(){
    switch(sonarState){
      case sPrime:
        Serial.print("Priming Read");
        sonarFront.Request_Reading();
        sonarState = s1;
        break;
      case s1:
        Serial.print("Sonar Case s1");
        sonarFront.Take_Reading();
        Serial.print("\t");
        Serial.print(sonarFront.getsonarvalue());
        //Serial.print("Sonar Front Available");
        //Serial.println(sonarFront.readingAvailable());
        if(sonarFront.readingAvailable()){
          sonarFrontR.Request_Reading();
          sonarState = s2;
        }
        break;
      case s2:
        Serial.print("Sonar Case s2");
        sonarFrontR.Take_Reading();
        Serial.print("\t");
        Serial.print(sonarFrontR.getsonarvalue());
        if(sonarFrontR.readingAvailable()){
          sonarFrontL.Request_Reading();
          sonarState = s3;
        }
        break;
      case s3:
        Serial.print("Sonar Case s3");
        sonarFrontL.Take_Reading();
        Serial.print("\t");
        Serial.print(sonarFrontL.getsonarvalue());
        if(sonarFrontL.readingAvailable()){
          sonarRearR.Request_Reading();
          sonarState = s4;
        }
        break;
      case s4:
        Serial.print("Sonar Case s4");
        sonarRearR.Take_Reading();
        Serial.print("\t");
        Serial.print(sonarRearR.getsonarvalue());
        if(sonarRearR.readingAvailable()){
          sonarRearL.Request_Reading();
          sonarState = s5;
        }
        break;
      case s5:
        Serial.print("Sonar Case s5");
        sonarRearL.Take_Reading();
        Serial.print("\t");
        Serial.print(sonarRearL.getsonarvalue());
        if(sonarRearL.readingAvailable()){
          sonarRear.Request_Reading();
          sonarState = s6;
        }
        break;
      case s6:
        Serial.print("Sonar Case s6");
        sonarRear.Take_Reading();
        Serial.print("\t");
        Serial.print(sonarRear.getsonarvalue());
        if(sonarRear.readingAvailable()){
          sonarFront.Request_Reading();
          sonarState = s1;
        }
    }
  }
  
  static const int unique_id = 2;
  int id(){return unique_id;}
  
  
};
