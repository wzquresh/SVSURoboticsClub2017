#include <Sonar.h>

enum SonarState{sPrime, s1, s2, s3, s4, s5};
SonarState sonarState;

//SONAR SENSOR PINS
//These will be referenced more often
int FrontSonarEcho = 53;
int FrontSonarTrigger = 52;
int FrontRightSonarEcho = 51;
int FrontRightSonarTrigger = 50;
int FrontLeftSonarEcho = 49;
int FrontLeftSonarTrigger = 48;
//Rear Sonar may not be used
//int RearSonarEcho = 0;
//int RearSonarTrigger = 0;
//These will be referenced less often
int RearRightSonarEcho = 47;
int RearRightSonarTrigger = 46;
int RearLeftSonarEcho = 45;
int RearLeftSonarTrigger = 44;

//unsigned int TestNumber;

Sonar sonarFront(1, 0,0, FrontSonarTrigger, FrontSonarEcho);
Sonar sonarFrontR(2, 0,0, FrontRightSonarTrigger, FrontRightSonarEcho);
Sonar sonarFrontL(3, 0,0, FrontLeftSonarTrigger, FrontLeftSonarEcho);
Sonar sonarRearR(4, 0,0, RearRightSonarTrigger, RearRightSonarEcho);
Sonar sonarRearL(5, 0,0, RearLeftSonarTrigger, RearLeftSonarEcho);

unsigned long startTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(FrontSonarEcho, INPUT);
  pinMode(FrontSonarTrigger, OUTPUT);
  pinMode(FrontRightSonarEcho, INPUT);
  pinMode(FrontRightSonarTrigger, OUTPUT);
  pinMode(FrontLeftSonarEcho, INPUT);
  pinMode(FrontLeftSonarTrigger, OUTPUT);
//  pinMode(RearSonarEcho, INPUT);
//  pinMode(RearSonarTrigger, OUTPUT);
  pinMode(RearRightSonarEcho, INPUT);
  pinMode(RearRightSonarTrigger, OUTPUT);
  pinMode(RearLeftSonarEcho, INPUT);
  pinMode(RearLeftSonarTrigger, OUTPUT);

  sonarState = sPrime;
  startTime = micros();
  //TestNumber = 0;
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sonarTest();
}

void sonarTest(){
	//switch(sonarState)
	//{
		//case sPrime:
			//TestNumber++;
			//sonarFront.Request_Reading();
			//sonarState = s1;
			//break;
		//case s1:
			//sonarFront.Take_Reading();
			//if(sonarFront.readingAvailable())
				//sonarState = s2;
			//break;
		//default:
			//sonarState = sPrime;
			//break;
	//}
	//Serial.print(TestNumber);
	//Serial.print("   ");
	//Serial.print(sonarFront.readingAvailable());
	//Serial.print("   ");
	//Serial.print(sonarFront.getsonarvalue());
	//Serial.println("");
  switch(sonarState){
    case sPrime:
      sonarFront.Request_Reading();
        sonarState = s1;
      break;
    case s1:
      sonarFront.Take_Reading();
	Serial.print("Sonar Front Available");
        Serial.println(sonarFront.readingAvailable());
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
        sonarFront.Request_Reading();
        sonarState = s1;
      }
      break;
  }
  Serial.print(micros());
  Serial.print(" Sonar Data --- Front: ");
  Serial.print(sonarFront.getsonarvalue());
  Serial.print(" Front Right: ");
  Serial.print(sonarFrontR.getsonarvalue());
  Serial.print(" Front Left: ");
  Serial.print(sonarFrontL.getsonarvalue());
  Serial.print(" Rear Right: ");
  Serial.print(sonarRearR.getsonarvalue());
  Serial.print(" Rear Left: ");
  Serial.print(sonarRearL.getsonarvalue());
  Serial.println("");
}
