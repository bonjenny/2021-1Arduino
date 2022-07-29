
int sensorPin = A0; //select the input pin for the potentiometer
int led = 9; //the pin that the LED is attached to

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = 0;
  float voltage = 0.0;

  sensorValue = analogRead(sensorPin);
  voltage = ((float)sensorValue/1023.0)*5.0;

  Serial.print(sensorValue);
  Serial.print(",");
  Serial.print(voltage);
  
  analogWrite(led, sensorValue/4);
  Serial.println(sensorValue);

  delay(10);
}
