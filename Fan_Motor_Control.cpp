 Fan_Motor::Fan_Motor(int PWM_Pin)
  {
    Pwm_Pin = PWM_Pin;
    pinMode(Pwm_Pin, OUTPUT);
  }
  void Fan_Motor::Set_Value(bool setValue){
   if(setValue == true)
     analogWrite(Pwm_Pin, 255);
   else
     analogWrite(Pwm_Pin, 0);
   }