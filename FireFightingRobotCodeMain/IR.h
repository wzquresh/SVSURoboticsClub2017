#include <arduino.h>

class IR{
  public:
    
    int pin;
    int MAX_RANGE;
    int MIN_RANGE;
  
  private:
    
    IR(int pinName, int MIN, int MAX);
    int flameCase();
};