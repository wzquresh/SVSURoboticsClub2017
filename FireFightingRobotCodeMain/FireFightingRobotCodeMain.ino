//Include:
#include "IR.h"
#include "bumpsensor.h"
#include "Sonar.h"

enum State{MIC_READ, SEARCH, END};
State current;
enum FlameCases{NO_FLAME, ONE_FAR, ONE_CLOSE, BOTH_FAR, BOTH_CLOSE};
FlameCases flameCase;
enum BumpCase{FRONT, RIGHT, LEFT, REAR_R, REAR_L, NO_BUMP};
BumpCase bumpCase;
enum CollisionCases{GOOD, RIGHT_ENCROACHING, LEFT_ENCROACHING, FRONT_ENCROACHING, REAR_ENCROACHING};
CollisionCases sonarCase;
enum SonarState{sPrime, s1, s2, s3, s4, s5};
SonarState sonarState;

//Pins
int Microphone = 0;
int RightMotor = 0;
int LeftMotor = 0;

//LED's
int GreenLED = 0;
int RedLED = 0;

//SONAR SENSOR PINS -- 6 total
int FrontSonarEcho = 0;
int FrontSonarTrigger = 0;
int FrontRightSonarEcho = 0;
int FrontRightSonarTrigger = 0;
int FrontLeftSonarEcho = 0;
int FrontLeftSonarTrigger = 0;
int RearSonarEcho = 0;
int RearSonarTrigger = 0;
int RightSonarEcho = 0;
int RightSonarTrigger = 0;
int LeftSonarEcho = 0;
int LeftSonarTrigger = 0;

//BUMP SENSOR PINS -- 7 total
int FrontBump = 0;
int FrontRightBump = 0;
int FrontLeftBump = 0;
int RightBump = 0;
int LeftBump = 0;
int RearRightBump = 0;
int RearLeftBump = 0;

//IR SENSOR PINS
int RightIR = 0;
int LeftIR = 0;

//FAN PIN
int FanPWM = 0;

//Inputs
//FLOURESCENT LIGHT
const int RIGHT_MIN = 400;
const int RIGHT_MAX = 780;
const int LEFT_MIN = 600
const int LEFT_MAX = 850;
//INCANDECENT LIGHT
//const int RIGHT_MIN = 110;
//const int RIGHT_MAX = 475;
//const int LEFT_MIN = 340
//const int LEFT_MAX = 600;

IR irRight(RightIR, RIGHT_MIN, RIGHT_MAX);
IR irLeft(LeftIR, LEFT_MIN, LEFT_MAX);

Sonar sonarFront(1, FrontSonarTrigger, FrontSonarEcho);
Sonar sonarFrontR(2, FrontRightSonarTrigger, FrontRightSonarEcho);
Sonar sonarFrontL(3, FrontLeftSonarTrigger, FrontLeftSonarEcho);
Sonar sonarRear(4, RearSonarEcho, RearSonarTrigger);
Sonar sonarRearR(5, RightSonarTrigger, RightSonarEcho);
Sonar sonarRearL(6, LeftSonarTrigger, LeftSonarEcho);

Bump bumpFront(FrontBump);
Bump bumpFrontR(FrontRightBump);
Bump bumpFrontL(FrontLeftBump);
Bump bumpR(RightBump);
Bump bumpL(LeftBump);
Bump bumpRearR(RearRightBump);
Bump bumpRearL(RearLeftBump);

//Outputs
Motor motorR(RightMotor);
Motor motorL(LeftMotor);

LED red(RedLED);
LED green(GreenLED);

Fan_Motor_Control fan(FanPWM);

setup(){
  current = MIC_READ;
  flameCase = NO_FLAME;
  sonarState = sPrime;
  bumpCase = NO_BUMP;
  sonarCase = GOOD;
  
  pinMode(Microphone, INPUT);
  pinMode(RightMotor, OUTPUT);
  pinMode(LeftMotor, OUTPUT);
  
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  
  pinMode(FrontSonarEcho, INPUT);
  pinMode(FrontSonarTrigger, OUTPUT);
  pinMode(FrontRightSonarEcho,INPUT;
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
  pinMode(LeftIR, INPUT;
  
  
  pinMode(FanPWM, OUTPUT);
  
}

loop(){
  sonarRun();
  
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
  
  //Proper call for motors: motorL.motors_action(speed, direction)
  //direction 1 forward, 0 backward
  
  switch(bumpCase){
    case FRONT:
      motorL.motors_action(SLOW, 0);
      motorR.motors_action(SLOW, 0);
      delay(50);
      if(sonarCase == GO_RIGHT){
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
      
      motorR.motors_action(SLOW, 1)
      delay(42);
      motorL.motors_action(SLOW, 1);
      break;
    default:
      break;    
  }
  
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
    
  switch(flameCase){
    case NO_FLAME:
      break;
    case ONE_FAR:
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
      motorR.motors_action(SLOW, 1);
      motorL.motors_action(SLOW, 1);
      break;
    case ONE_CLOSE:
      if(irRight.flameCase() == 2){
        motorR.motors_action(SLOW, 0);
        motorL.motors_action(SLOW, 1);
      }else{
        motorL.motors_action(SLOW, 0);
        motorR.motors_action(SLOW, 1);
      }
      break;
    case BOTH_CLOSE:
      motorL.motors_action(STOP, 1);
      motorR.motors_action(STOP, 1);
      fan.Set_Value(1);
      //end robot
      break;
  }
  
  
}


void sonarRun(){
  switch(sonarState){
    case sPrime:
      sonarFront.Request_Reading();
      sonarState = s1;
      break;
    case s1:
      sonarFront.Take_Reading();
      //Serial.print("Sonar Front Available");
      //Serial.println(sonarFront.readingAvailable());
      if(sonarFront.readingAvailable()){
        sonarFrontR.Request_Reading();
        sonarState = s2;
      }
      break;
    case s2:
      sonarFrontR.Take_Reading();
      if(sonarFrontR.readingAvailable()){
        sonarFrontL.Request_Reading();
        sonarState = s3;
      }
      break;
    case s3:
      sonarFrontL.Take_Reading();
      if(sonarFrontL.readingAvailable()){
        sonarRearR.Request_Reading();
        sonarState = s4;
      }
      break;
    case s4:
      sonarRearR.Take_Reading();
      if(sonarRearR.readingAvailable()){
        sonarRearL.Request_Reading();
        sonarState = s5;
      }
      break;
    case s5:
      sonarRearL.Take_Reading();
      if(sonarRearL.readingAvailable()){
        sonarRear.Request_Reading();
        sonarState = s6;
      }
      break;
    case s6:
      sonarRear.Take_Reading();
      if(sonarRear.readingAvailable()){
        sonarFront.Request_Reading();
        sonarState = s1;
      }
  }
}
