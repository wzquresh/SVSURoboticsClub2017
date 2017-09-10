#ifndef PINS_H_DEFINED
#define PINS_H_DEFINED

// 1st Pins to Arduino.
// 2nd Wiring connections.
// 3rd Pin modes to the Arduino.

//Pins to the Arduino Mega 2560.
  // Microphone
  int Microphone_Pin = 2; //Analog In:  A2

  // Drive Motors
  int RightMotor_Speed_Pin = 3; // PWM/Digital
  int RightMotor_Forward_Pin = 24;
  int RightMotor_Reverse_Pin = 22;
  int LeftMotor_Speed_Pin = 4; // PWM/Digital
  int LeftMotor_Forward_Pin = 25;
  int LeftMotor_Reverse_Pin = 23;

  //LED's
  int GreenLED = 27;
  int RedLED = 29;

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
  int FrontBump = 26;
  int FrontRightBump = 28;
  int FrontLeftBump = 38;
  int RightBump = 30;
  int LeftBump = 36;
  int RearRightBump = 32;
  int RearLeftBump = 34;

  //IR SENSOR PINS
  int RightIR = 0; //Analog In:  A0
  int LeftIR = 1;  //Analog In:  A1

  //FAN PIN

  int FanPWM = 5;  // PWM/Digital

//  WIRING CONNECTIONS
//Sectional definitions:
//Front Lid - wires dirrectly attached to the components on the front section.
//Back Lid - wires directly attached to the components on the back section.
//Side Body - wires to the sides of the body, on the main chassis.
//Handle - wires attached to the handle components (power and sensors).
//Main Chassis Tray - wires attached to the components on the removable tray.
//Arduino - wires attached to the Arduino on the Main Chassis Tray.
//Motor Shield - wires attached to the motor shield in middle of Main Chassis Tray.
//Main Harness - wires attached between individual sections, itself removeable.
//
//
//Back Chassis 25 pin Dsub
//Male plug on Back Lid.
//Pin  1  Rear Right Sonar PWR  (Red wire)
//Pin  2  Rear Right Sonar Trigger  (Yellow wire)
//Pin  3  Rear Right Sonar Echo  (Orange wire)
//Pin  4  Rear Right Sonar GND  (Black wire)
//Pin  5  Rear Center Sonar PWR  (Red wire)
//Pin  6  Rear Center Sonar Trigger  (Yellow wire)
//Pin  7  Rear Center Sonar Echo  (Orange wire)
//Pin  8  Rear Center Sonar GND  (Black wire)
//Pin  9  Rear Left Sonar PWR  (Red wire)
//Pin 10  Rear Left Sonar Trigger  (Yellow wire)
//Pin 11  Rear Left Sonar Echo  (Orange wire)
//Pin 12  Rear Left Sonar GND  (Black wire)
//Pin 13  Rear Right Bump Sense  (Blue wire)
//Pin 14  Rear Right Bump GND  (Black wire)
//Pin 15  Rear Left Bump Sense  (Blue wire)
//Pin 16  Rear Left Bump GND  (Black wire)
//Pin 17  No Connection
//Pin 18  No Connection
//Pin 19  No Connection
//Pin 20  No Connection
//Pin 21  No Connection
//Pin 22  No Connection
//Pin 23  No Connection
//Pin 24  No Connection
//Pin 25  No Connection
//Female plug on Main Harness Back.
//
//Front Chassis 25 pin Dsub
//Male plug on Front Lid.
//Pin  1  Front Left Sonar PWR  (Red wire)
//Pin  2  Front Left Sonar Trigger  (Yellow wire)
//Pin  3  Front Left Sonar Echo  (Orange wire)
//Pin  4  Front Left Sonar GND  (Black wire)
//Pin  5  Front Center Sonar PWR  (Red wire)
//Pin  6  Front Center Sonar Trigger  (Yellow wire)
//Pin  7  Front Center Sonar Echo  (Orange wire)
//Pin  8  Front Center Sonar GND  (Black wire)
//Pin  9  Front Right Sonar PWR  (Red wire)
//Pin 10  Front Right Sonar Trigger  (Yellow wire)
//Pin 11  Front Right Sonar Echo  (Orange wire)
//Pin 12  Front Right Sonar GND  (Black wire)
//Pin 13  Front Left Bump Sense  (Blue wire)
//Pin 14  Front Left Bump GND  (Black wire)
//Pin 15  Front Center Bump Sense  (Blue wire)
//Pin 16 	Front Center Bump GND  (Black wire)
//Pin 17  Front Right Bump Sense  (Blue wire)
//Pin 18  Front Right Bump GND  (Black wire)
//Pin 19  Left IR PWR  (Red wire)
//Pin 20  Left IR Sense  (Purple wire)
//Pin 21  Left IR GND  (Black wire)
//Pin 22  Right IR PWR  (Red wire)
//Pin 23  Right IR Sense  (Purple wire)
//Pin 24  Right IR GND  (Black wire)
//Pin 25  No Connection
//Female plug on Main Harness Front.
//
//Arduino 25 pin Dsub
//Male plug on Main Chassis Tray Arduino.
//Pin  1  Front Left Sonar Trigger  (Yellow wire)
//Pin  2  Front Left Sonar Echo  (Orange wire)
//Pin  3  Front Center Sonar Trigger  (Yellow wire)
//Pin  4  Front Center Sonar Echo  (Orange wire)
//Pin  5  Front Right Sonar Trigger  (Yellow wire)
//Pin  6  Front Right Sonar Echo  (Orange wire)
//Pin  7  Rear Right Sonar Trigger  (Yellow wire)
//Pin  8  Rear Right Sonar Echo  (Orange wire)
//Pin  9  Rear Center Sonar Trigger  (Yellow wire)
//Pin 10  Rear Center Sonar Echo  (Orange wire)
//Pin 11  Rear Left Sonar Trigger  (Yellow wire)
//Pin 12  Rear Left Sonar Echo  (Orange wire)
//Pin 13  Front Left Bump Sense  (Blue wire)
//Pin 14  No Connection
//Pin 15  Microphone Aout  (Green wire)
//Pin 16  Green LED Enable  (White wire)
//Pin 17  Red LED Enable  (Grey wire)
//Pin 18  Right IR Sense  (Purple wire)
//Pin 19  Left IR Sense  (Purple wire)
//Pin 20  Rear Left Bump Sense  (Blue wire)
//Pin 21  Rear Right Bump Sense  (Blue wire)
//Pin 22  Right Side Bump Sense  (Blue wire)
//Pin 23  Left Side Bump Sense  (Blue wire)
//Pin 24  Front Right Bump Sense  (Blue wire)
//Pin 25  Front Center Bump Sense  (Blue wire)
//Female plug on Main Harness Right.
//
//Motor Shield
//Only direct wiring on Main Chassis Tray, no direct buses.
//ENA to LeftMotor_Speed_Pin  (Green wire)
//IN1 to LeftMotor_Forward_Pin  (Yellow wire)
//IN2 to LeftMotor_Backward_Pin  (Blue wire)
//IN3 to RightMotor_Backward_Pin  (Blue wire)
//IN4 to RightMotor_Forward_Pin  (Yellow wire)
//ENB to RightMotor_Speed_Pin  (Green wire)
//ENB_GND to Arduino Power GND  (Black wire)
//OUT1 to Left Motor ??
//OUT2 to Left Motor ??
//OUT3 to Right Motor ??
//OUT4 to Right Motor ??
//+5V to Low-Power Bus  (Red wire)
//GND to Ground Bus  (Black wire)
//GND also to Handle Power Pin 2
//+12V to Handle Power Pin 1
//
//Fan
//Only direct wiring, no direct buses.
//MOSFET Gate to FANPWM  (Yellow wire)
//
//Side Body 9 pin Dsub
//Male plug on Main Chassis Left
//Pin  1  Left Side Bump Sense  (Blue wire)
//Pin  2  Left Side Bump GND  (Black wire)
//Pin  3  Right Side Bump Sense  (Blue wire)
//Pin  4  Right Side Bump GND  (Black wire)
//Pin  5  No Connection
//Pin  6  No Connection
//Pin  7  No Connection
//Pin  8  No Connection
//Pin  9  No Connection
//Female plug on Main Harness Left
//
//Ground Bus 25 pin Dsub
//Male plug on Main Harness Ground
//Pin  1  Rear Right Sonar GND  (Black wire)
//Pin  2  Rear Center Sonar GND  (Black wire)
//Pin  3  Rear Left Sonar GND  (Black wire)
//Pin  4  Rear Right Bump GND  (Black wire)
//Pin  5  Rear Left Bump GND  (Black wire)
//Pin  6  Right Side Bump GND  (Black wire)
//Pin  7  Left Side Bump GND  (Black wire)
//Pin  8  Handle Microphone GND  (Black wire)
//Pin  9  Front Left Sonar GND  (Black wire)
//Pin 10  Front Center Sonar GND  (Black wire)
//Pin 11  Front Right Sonar GND  (Black wire)
//Pin 12  Front Left Bump GND  (Black wire)
//Pin 13  Front Center Bump GND  (Black wire)
//Pin 14  Front Right Bump GND  (Black wire)
//Pin 15  Left IR GND  (Black wire)
//Pin 16  Right IR GND  (Black wire)
//Pin 17  No Connection
//Pin 18  No Connection
//Pin 19  No Connection
//Pin 20  No Connection
//Pin 21  No Connection
//Pin 22  No Connection
//Pin 23  No Connection
//Pin 24  Arduino GND  (Black wire)
//Pin 25  Motor Shield Main GND Feed  (Black wire)  (ie. source)
//Female plug on Main Chassis Tray
//
//Power Bus 25 pin Dsub
//Male plug on Main Chassis Tray
//Pin  1  Rear Left Sonar PWR  (Red wire)
//Pin  2  Rear Center Sonar PWR  (Red wire)
//Pin  3  Rear Right Sonar PWR  (Red wire)
//Pin  4  Red LED PWR  (Red wire)
//Pin  5  Green LED PWR  (Red wire)
//Pin  6  Microphone PWR  (Red wire)
//Pin  7  Front Left Sonar PWR  (Red wire)
//Pin  8  Front Center Sonar PWR  (Red wire)
//Pin  9  Front Right Sonar PWR  (Red wire)
//Pin 10  Left IR PWR  (Red wire)
//Pin 11  Right IR PWR  (Red wire)
//Pin 12  No Connection
//Pin 13  No Connection
//Pin 14  No Connection
//Pin 15  No Connection
//Pin 16  No Connection
//Pin 17  No Connection
//Pin 18  No Connection
//Pin 19  No Connection
//Pin 20  No Connection
//Pin 21  No Connection
//Pin 22  No Connection
//Pin 23  No Connection
//Pin 24  Arduino +5V Pin  (Red wire)
//Pin 25  Motor Shield +5V Regulator Output  (Red wire) (ie. source)
//Female plug on Main Harness Low Power
//
//Handle Sensors 9 pin Dsub
//Male plug on Handle
//Pin 1  	Red LED PWR  (Red wire)
//Pin 2  	Red LED Enable  (Grey wire)
//Pin 3  	Green LED PWR  (Red wire)
//Pin 4  	Green LED Enable  (White wire)
//Pin 5  	Microphone PWR  (Red wire)
//Pin 6  	Microphone Aout  (Green wire)
//Pin 7  	Microphone GND  (Black wire)
//Pin 8   No Connection
//Pin 9   No Connection
//Female plug on Main Harness Center
//
//Handle Power 9 pin Dsub
//Male plug on Main Harness Center
//Pin 1  14V Power bus Power Switch High
//Pin 2  GND Bus KillSwitch GND
//Pin 3  Battery KillSwitch 14V PWR
//Pin 4  Battery GND Bus GND
//Pin 5  No Connection
//Pin 6  No Connection
//Pin 7  No Connection
//Pin 8  No Connection
//Pin 9  No Connection
//Female plug on Handle


// Pin modes to the Arduino.

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
    
    
    pinMode(FrontBump, INPUT_PULLUP);
    pinMode(FrontRightBump, INPUT_PULLUP);
    pinMode(FrontLeftBump, INPUT_PULLUP);
    pinMode(RightBump, INPUT_PULLUP);
    pinMode(LeftBump, INPUT_PULLUP);
    pinMode(RearRightBump, INPUT_PULLUP);
    pinMode(RearLeftBump, INPUT_PULLUP);
    
    
    pinMode(RightIR, INPUT);
    pinMode(LeftIR, INPUT);
    
    
    pinMode(FanPWM, OUTPUT);
}
#endif
