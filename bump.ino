class Bump{
  private:
  int bumpPin;
  
  public:
  Bump(int sensorID){
    bumpPin = sensorID;
  }
  bool getValue(){
    return digitalRead(bumpPin) == HIGH;
  }
}
