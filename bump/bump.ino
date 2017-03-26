class Bump{
  private:
  int bumpPin;
  XYCoordinate local_postion;
  
  public:
  Bump(int sensorID, long local_x, long local_y){
    bumpPin = sensorID;
    local_position.x = local_x; 
    local_postion.y = local_y;
  }
  bool getValue(){
    return digitalRead(bumpPin) == HIGH;
  }
  XYCoordinate GetPosition()
{
return local_position;
}
};
