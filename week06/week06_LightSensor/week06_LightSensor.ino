int lightPin = 0; // define a pin for Photo resistor
int ledPin = 11; // define a pin for LED

void setup() {
  Serial.begin(9600); // Begin serial communication
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.println(analogRead(lightPin));
  analogWrite(ledPin, analogRead(lightPin)/4);
  delay(10); // short delay for faster response to light.
}
