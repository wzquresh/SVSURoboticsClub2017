#include <arduino.h>
//Michael this shoould print to the serial:
//...............
class CommandLoop{
  public:
  virtual void setup()=0;
  virtual int loop()=0;
  virtual int id()=0;
  virtual ~CommandLoop(){}
};

class BeepState:public CommandLoop{
  public:
  void setup(){};
  int loop(){Serial.println("Found Beep"); return 1;};
  static const int unique_id = 1;
  int id(){return unique_id;};
 };
class RunState:public CommandLoop{
  public:
  void setup(){};
  int loop(){Serial.print(".");return 0;};
  static const int unique_id = 2;
  int id(){return unique_id;};
  };
CommandLoop *command;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  command = new BeepState();
}

void loop() {
  // put your main code here, to run repeatedly:
switch (command->loop())
{
  case 0:
    //Still working
  break;
  case 1:
    if(command->id()==BeepState::unique_id){
      //found Beep!
      delete command;
      command = new RunState();
    }
    if(command->id()==RunState::unique_id){
      //found Fire!
      delete command;
      while(1);
      }
  break;
  default:
    //Umm...
    break;
  }
}
