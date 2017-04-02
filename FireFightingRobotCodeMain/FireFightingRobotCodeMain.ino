#include "CommandLoop.h"
#include "StartState.h"
#include "SearchState.h"
#include "Pins.h"

CommandLoop *command;
const uint16_t TARGET_FREQUENCY(3800);
const uint16_t MIN_WINDOW_FREQUENCY(0.87 * TARGET_FREQUENCY);
const uint16_t MAX_WINDOW_FREQUENCY(1.13 * TARGET_FREQUENCY);


void setup(){
  command = new StartState(1, Microphone_Pin, TARGET_FREQUENCY, MIN_WINDOW_FREQUENCY, MAX_WINDOW_FREQUENCY);
}

void loop(){
  switch(command -> loop()){
    case StartState::unique_id:
      if(command->ReceivedTargetSound()){
        delete command;
        command = new SearchState();
      }
    case SearchState::unique_id:
      if(command->FireExtinguished()){
        while(1){}
        //end of robot commands
      }
  }
}
