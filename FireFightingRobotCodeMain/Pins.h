#ifndef PINS_H_DEFINED
#define PINS_H_DEFINED

//Pins
  // Microphone
  int Microphone_Pin = 2; //Analog In:  A2

  // Drive Motors
  int RightMotor_Speed_Pin = 2; // PWM/Digital
  int RightMotor_Forward_Pin = 24;
  int RightMotor_Reverse_Pin = 22;
  int LeftMotor_Speed_Pin = 3; // PWM/Digital
  int LeftMotor_Forward_Pin = 28;
  int LeftMotor_Reverse_Pin = 26;

  //LED's
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
  int RightIR = 0; //Analog In:  A0
  int LeftIR = 1;  //Analog In:  A1

  //FAN PIN

  int FanPWM = 0;  // PWM/Digital

void setup_pins(){
    //pinMode(Microphone_Pin, INPUT);  // Already within microphone.cpp code.
    
    
    //pinMode(RightMotor, OUTPUT);  // Already within wheel_motors.cpp code.
    //pinMode(LeftMotor, OUTPUT);  // Already within wheel_motors.cpp code.
    
    
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
#endif
