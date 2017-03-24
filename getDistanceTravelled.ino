/*
 * GetDistanceTravelled
 *
 * ????? UNTESTED CODE : NEEDS VERIFICATION ???????
 *
 * The code shall return a single value to whereever it is called. The value returned will be
 * the distance travelled by the wheel.
 * 
 * everytime the function loop() returns an int value, the number of pulses is set back to zero. 
 * 
 * This function returns a positive value regardless of the direction of the rotation of the 
 * encoder. To determine whether the robot is travelling forward or backward, wherever this 
 * function is called the direction of motor rotation have to be considered to calculate the 
 * actual distance travelled. 
 * 
 * Code Help from: myscratchbooks Project#11 Infrared Speed Sensor module
*/

int encoder_pin = 51; //whatever the interrupt pin number is going to be we shall enter it here

unsigned int distance; //takes in RPM reading 
volatile byte pulses; //takes in number of pulses
unsigned long timeold;

//the number of pulses per revolution depends on the index disc
unsigned int pulsesPerTurn = 20;

//this function increments the counter, that's all it does

void counter()
{
  //update count
  pulses++;
}

// we shall setup stuff now
void setup()
{
  Serial.begin(9600);

  //we use statusPin to flash along with interrupts
  pinMode(encoder_pin, INPUT);

  // Interrupt 0 is a digital pin 51, so that is where the IR detector is connected
  // Triggers on falling (change from HIGH to LOW)
  attachInterrupt(0, counter, FALLING);

  //initialize
  pulses = 0;
  distance = 0;
  timeold = 0; 
}

//this is another function here
// diameter of the wheel is roughly is 6.98 cm!
int loop()
{
  if (millis() - timeold >= 1000) //update every one second, this will be equal to reading frequency
  {
    //do not process interrupts during calculations when a value is necessary
    detachInterrupt(0);

    //here the encoder stops counting, takes the total value of the pulses until this point and calculates the distance travelled
    //the distance returned is in centimeters
    distance = ((3.14 * 6.98) / 20) * pulses;
    timeold = millis();
    pulses = 0;

    return distance;

    //restart recounting the pulses for returning the next distance travelled
    attachInterrupt(0, counter, FALLING);
  }
}
