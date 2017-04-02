#include "IR.h"

IR::IR(int pinName, int MIN, int MAX){
  pin = pinName;
  MAX_RANGE = MAX;
  MIN_RANGE = MIN;
}

int IR::flameCase(){
  int reading = analogRead(pin);
  //No Fire Case
  if(reading > MAX_RANGE){
    return 0;
  }
  //Fire Detected at Distance
  if(reading <= MAX_RANGE && MIN_RANGE < reading){
    return 1;
  }
  //FIRE HERE NOW
  if(reading <= MIN_RANGE){
    return 2;
  }
}