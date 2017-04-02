#include "bumpsensor.h"

XYCoordinate Bump::GetPosition();
Bump(int sensorID, long local_x, long local_y){
	bumpPin = sensorID;
	local_position.x = local_x; 
	local_postion.y = local_y;
}

bool Bump::getValue(){
	return digitalRead(bumpPin) == LOW;
}

XYCoordinate Bump::GetPosition()
{
	return local_position;
}
