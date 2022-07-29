
//week03 - 버튼에 부저가 같이 울리도록

int led = 7;
int key = 13;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(key, INPUT);
}

void loop() {
  if(digitalRead(key) == HIGH) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
  else
    digitalWrite(led, LOW);
}
