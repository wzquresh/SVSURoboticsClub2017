//Authors:
//Brendan Jones
//Waqas Qureshi
//

//Libraries

//Global Variables
enum State{S_IDLE, SENSOR_READ, SEARCH, ROOM, EXTINGUISH, RETURN};
State current;

//Set Pins
int Microphone = 0;
int RightMotor = 0;
int LeftMotor = 0;
int RightWheelEncoder = 0;
int LeftWheelEncoder = 0;

//LED's
int GreenLED = 0;
int RedLED = 0;

//SONAR SENSOR PINS
int FrontSonarEcho = 0;
int FrontSonarTrigger = 0;
int FrontRightSonarEcho = 0;
int FrontRightSonarTrigger = 0;
int FrontLeftSonarEcho = 0;
int FrontLeftSonarTrigger = 0;
int RearSonarEcho = 0;
int RearSonarTrigger = 0;
int RearRightSonarEcho = 0;
int RearRightSonarTrigger = 0;
int RearLeftSonarEcho = 0;
int RearLeftSonarTrigger = 0;

//IR SENSOR PINS
int RightIRADC = 0;
int RightIRToggle = 0;
int LeftIRADC = 0;
int LeftIRToggle = 0;

//BUMMPERS
int FrontRightBumpToggle = 0;
int FrontLeftBumpToggle = 0;
int RearRightBumpToggle = 0;
int RearLeftBumpToggle = 0;

//FAN
int FanPWM = 0;

//MIC
int MicADCFrequency = 0;

//2D arrays to store positions visited
long long visited[64];
long long intersection[64]

void setup() {
  // put your setup code here, to run once:
  //State setup
  current = S_IDLE;
  //Pins setup
  //Wheel and Motor
  pinMode(RightMotor, OUTPUT);
  pinMode(LeftMotor, OUTPUT);
  pinMode(RightWheelEncoder, INPUT);
  pinMode(LeftWheelEncoder, INPUT);
  //Sonar
  pinMode(FrontSonarEcho, INPUT);
  pinMode(FrontSonarTrigger, OUTPUT);
  pinMode(FrontRightSonarEcho, INPUT);
  pinMode(FrontRightSonarTrigger, OUTPUT);
  pinMode(FrontLeftSonarEcho, INPUT);
  pinMode(FrontLeftSonarTrigger, OUTPUT);
  pinMode(RearSonarEcho, INPUT);
  pinMode(RearSonarTrigger, OUTPUT);
  pinMode(RearRightSonarEcho, INPUT);
  pinMode(RearRightSonarTrigger, OUTPUT);
  pinMode(RearLeftSonarEcho, INPUT);
  pinMode(RearLeftSonarTrigger, OUTPUT);
  
  //IR
  pinMode(RightIRADC, INPUT);  //Analog to Digital Conversion
  pinMode(LeftIRADC, INPUT);
  pinMode(RightIRToggle, INPUT);
  pinMode(LeftIRToggle, INPUT);
  
  //BUMPER
  pinMode(FrontRightBumpToggle, INPUT);
  pinMode(FrontLeftBumpToggle, INPUT);
  pinMode(RearRightBumpToggle, INPUT);
  pinMode(RearLeftBumpToggle, INPUT);
  
  //LED's
  pinMode(GreenLED, INPUT);
  pinMode(RedLED, INPUT);

  //FAN
  pinMode(FanPWM, OUTPUT);

  //MIC
  pinMode(MicADCFrequecy, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(current){
    case S_IDLE:
      onUpdateStateIdle();
      break
    case SEARCH:
      onUpdateStateSearch();
      break;
    case ROOM:
      onUpdateStateRoom();
      break;
    case EXTINGUISH:
      onUpdateStateExtinguish();
      break;
    case RETURN:
      onUpdateStateReturn();
      break;
  }
}

void onUpdateStateIdle(){
  //Hear for 3.8kHz w/13% error
  if(digitalRead(Microphone) >= frequencyMin && micSensorPin <= frequencyMax){
    pinMode(GreenLED, HIGH);
    current = SEARCH;
  }
}

bool IsBitSet(long long* arr, int row, int col){
  return arr[row]&(1<<col); // Returns true if bit 'col' is 1.
}
void SetBit(long long* arr, int row, int col){
  arr[row]|=(1<<col);
}
void ClearBit(long long* arr, int row, int col){
  arr[row]&=~(1<<col);
}

void SensorRead(){}

void onUpdateStateSearch(){}
void onUpdateStateRoom(){}
void onUpdateStateExtinguish(){}
void onUpdateStateReturn(){}
