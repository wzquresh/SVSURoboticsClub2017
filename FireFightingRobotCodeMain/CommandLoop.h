#include <arduino.h>
class CommandLoop{
  public:
  virtual void setup()=0;
  virtual int loop()=0;
  virtual int id()=0;
  virtual ~CommandLoop(){}
};