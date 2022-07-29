
int sensorPin = A0; //select the input pin for the potentiometer
int led = 9; //the pin that the LED is attached to

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = 0;

  sensorValue = analogRead(sensorPin);
  analogWrite(led, sensorValue);
  Serial.println(sensorValue);

  delay(10);
}
