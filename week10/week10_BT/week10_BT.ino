#include <SoftwareSerial.h>

int bluetoothTx = 2;
int bluetoothRx = 3;
int LED8 = 8;
int LED6 = 7;
int LED4 = 6;
int LED2 = 5;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  Serial.begin(9600);
  delay(100);
  bluetooth.begin(9600);
  pinMode(LED8, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  char cmd;
  if(bluetooth.available())
  {
    cmd = (char)bluetooth.read();
    Serial.print("Command = ");
    Serial.print(cmd);

    if(cmd == '8')
    {
      Serial.println("LED8 ON");
      digitalWrite(LED8, HIGH);
    }
    if(cmd == '6')
    {
      Serial.println("LED6 ON");
      digitalWrite(LED6, HIGH);
    }
    if(cmd == '4')
    {
      Serial.println("LED4 ON");
      digitalWrite(LED4, HIGH);
    }
    if(cmd == '2')
    {
      Serial.println("LED2 ON");
      digitalWrite(LED2, HIGH);
    }
    if(cmd == '5')
    {
      Serial.println("ALL LEDS ON");
      digitalWrite(LED8, HIGH);
      digitalWrite(LED6, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED2, HIGH);
    }
    if(cmd == '0')
    {
      Serial.println("ALL LEDS OFF");
      digitalWrite(LED8, LOW);
      digitalWrite(LED6, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED2, LOW);
    }
  }
}
