void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("$CLEAR\r\n");
  Serial.print("$GO 1 4\r\n");
  Serial.print("$PRINT Welcome to\r\n");
  Serial.print("$GO 2\r\n");
  Serial.print("$PRINT Dongyang Univ.\r\n");
  Serial.print("$CURSOR 1 1\r\n");
  delay(1000);
}
