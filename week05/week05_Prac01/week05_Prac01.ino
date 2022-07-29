int led = 9; //the pin that the LED is attached to
int brightness = 0; //how bright the LED is
int fadeAmount = 3; //how many points to fade the LED by

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, brightness);
  brightness += fadeAmount;
  if (brightness >= 255) {
    brightness = 0;
  }
  delay(30);
}
