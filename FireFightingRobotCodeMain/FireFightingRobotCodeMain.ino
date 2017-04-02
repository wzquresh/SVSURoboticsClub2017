#include "CommandLoop.h"
#include "StartState.h"
#include "SearchState.h"


CommandLoop *command;

void setup(){
  command = new StartState();
}

void loop(){
  switch(command -> loop()){
    case 0:
    case 1:
      if(StartState::ReceivedTargetSound()){
        delete command;
        command = new SearchState();
      }
    case 2:
      if(SearchState::FireExtinguished()){
        while(1);
        //end of robot commands
      }
  }
}
