int led = 9; //the pin that the LED is attached to
int i = 0; //how bright the LED is
int fadeAmount = 3; //how many points to fade the LED by

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  for(i = 0; i <= 255; i += fadeAmount) {
    analogWrite(led, i);
    delay(30);
  }
}
