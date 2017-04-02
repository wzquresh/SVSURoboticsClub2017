#include <arduino.h>

class IR{
    
    int pin;
    int MAX_RANGE;
    int MIN_RANGE;
  
  public:
    IR(int pinName, int MIN, int MAX);
    int flameCase();
};
