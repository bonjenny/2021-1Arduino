#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define trigPin 13
#define echoPin 12

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2); // 안되면 주소를 0x27->0x3F로 변경

void setup() {
  lcd.begin(); // initialize the LCD
  lcd.backlight(); // Turn on the blacklight and print a message.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))),
  // there are 73.746 microseconds per inch
  return microseconds/74/2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds/29/2;
}

void loop() {
  long duration, inches, cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  lcd.clear();
  lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄 위치, lcd.home()
  lcd.print(inches);
  lcd.print("inch, ");
  lcd.setCursor(0, 1);
  lcd.print(cm);
  lcd.print("cm");

  delay(1000);
}
