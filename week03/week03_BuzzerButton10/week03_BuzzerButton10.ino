
//week03 - 버튼에 LED는 켜져 있고 부저는 ON/OFF 반복

int buzzer = 5;
int led = 7;
int key = 13;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(key, INPUT);
}

void loop() {
  if(digitalRead(key) == HIGH) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
  else
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
}
