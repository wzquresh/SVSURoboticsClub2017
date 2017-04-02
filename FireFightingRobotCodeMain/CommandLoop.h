#include <arduino.h>
#ifndef COMMAND_LOOP_H
#define COMMAND_LOOP_H
class CommandLoop{
  public:
  virtual void setup()=0;
  virtual int loop()=0;
  virtual int id()=0;
  virtual ~CommandLoop(){}
};
#endif
