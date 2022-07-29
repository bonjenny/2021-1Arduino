
//LED 깜박이기

int led1 = 8;
int led2 = 9;

void setup() {
  // put your setup code here, to run once:
  //디지털 핀 8번과 9번을 출력핀으로 쓸 것이다.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(500);
  digitalWrite(led2, LOW);

  delay(500);
  digitalWrite(led2, HIGH);

  digitalWrite(led1, LOW);
  
  delay(500);
  digitalWrite(led2, LOW);

  delay(500);
  digitalWrite(led2, HIGH);
  
  digitalWrite(led1, HIGH);
}
