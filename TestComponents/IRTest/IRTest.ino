int DigitalIR_Left = 52;
int DigitalIR_Right = 53

void setup() {
  // put your setup code here, to run once:
  pinMode(DigitalIR_Left, INPUT);
  pinMode(DigitalIR_Right, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Digital IR Pin Left: ");
  Serial.print(digitalRead(DigitalIR_Left));
  Serial.print("  Analog IR Pin Data Left: ");
  Serial.print(analogRead(0));
  
  Serial.print("    Digital IR Pin Right: ");
  Serial.print(digitalRead(DigitalIR));
  Serial.print("  Analog IR Pin Data Right: ");
  Serial.print(analogRead(1));  
  Serial.println();
}
