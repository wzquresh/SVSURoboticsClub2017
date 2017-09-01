//#include "Pins.h"
#include "StartState.h"
#include "SearchState.h"

CommandLoop *command;

const uint16_t TARGET_FREQUENCY(3800);
const uint16_t MIN_WINDOW_FREQUENCY(0.87 * TARGET_FREQUENCY);
const uint16_t MAX_WINDOW_FREQUENCY(1.13 * TARGET_FREQUENCY);


void setup(){
#ifdef DEBUG_PRINTING
    Serial.begin(19200);
#endif
  setup_pins();

  command = new StartState(1, Microphone_Pin, TARGET_FREQUENCY, MIN_WINDOW_FREQUENCY, MAX_WINDOW_FREQUENCY);
      command->setup();
}

void loop(){
#ifdef PRINT_CURRENT_CONMAND_STATE_DEBUG
  Serial.print("Current State: ");
  Serial.print(command->id());
  Serial.print("\t");
#endif
  command->loop();
  switch(command -> id()){
    case StartState::unique_id:
	{
		StartState* startstate_ptr = static_cast<StartState*>(command);
		if(startstate_ptr->ReceivedTargetSound()){
			delete command;  // NB:  startstate_ptr is the same as command, do NOT delete it!
			command = new SearchState();
      command->setup();
      digitalWrite(GreenLED, LOW);
      //Serial.print("Start State Ending");
		}
	}
    case SearchState::unique_id:
    //Serial.print("Search State Starting");
	{
		SearchState* searchstate_ptr(static_cast<SearchState*>(command));
   //Serial.print("Search State Starting");
     //searchstate_ptr->loop();
		if(searchstate_ptr->FireExtinguished()){
      //Serial.print("Search State Starting");
			//end of robot commands
			//delete command;  // NB:  startstate_ptr is the same as command, do NOT delete it!
		while(1){}
		}
	}
  }
#ifdef DEBUG_PRINTING
  Serial.println();
#endif
}
