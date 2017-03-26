#include <SoftwareSerial.h>

#define DIGITAL_OUT 49

int sensorValue = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(DIGITAL_OUT, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Flame: ");
  sensorValue = digitalRead(DIGITAL_OUT);
  Serial.print(sensorValue);
}
