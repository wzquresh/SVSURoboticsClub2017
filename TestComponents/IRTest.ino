int DigitalIR_Pin = 52;
//int AnalogIR_Pin = 53;

void setup() {
  // put your setup code here, to run once:
  pinMode(DigitalIR_Pin, INPUT);
  //pinMode(AnalogIR_Pin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Digital IR Pin Data: ");
  Serial.print(digitalRead(DigitalIR_Pin));
  Serial.print(" Analog IR Pin Data: ");
  Serial.print(analogRead(0));
  Serial.println();
}
