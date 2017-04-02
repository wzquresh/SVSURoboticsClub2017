#include "CommandLoop.h"
#include "StartState.h"
#include "SearchState.h"
//#include "Pins.h"

CommandLoop *command;

int Microphone_Pin = 35; //Digital

const uint16_t TARGET_FREQUENCY(3800);
const uint16_t MIN_WINDOW_FREQUENCY(0.87 * TARGET_FREQUENCY);
const uint16_t MAX_WINDOW_FREQUENCY(1.13 * TARGET_FREQUENCY);


void setup(){
  command = new StartState(1, Microphone_Pin, TARGET_FREQUENCY, MIN_WINDOW_FREQUENCY, MAX_WINDOW_FREQUENCY);
}

void loop(){
  switch(command -> loop()){
    case StartState::unique_id:
	{
		StartState* startstate_ptr = static_cast<StartState*>(command);
		if(startstate_ptr->ReceivedTargetSound()){
			delete command;  // NB:  startstate_ptr is the same as command, do NOT delete it!
			command = new SearchState();
		}
	}
    case SearchState::unique_id:
	{
		SearchState* searchstate_ptr(static_cast<SearchState*>(command));
		if(searchstate_ptr->FireExtinguished()){
			//end of robot commands
			//delete command;  // NB:  startstate_ptr is the same as command, do NOT delete it!
		}
		while(1){}
	}
  }
}
