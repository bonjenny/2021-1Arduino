#include <LiquidCrystal.h>

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2); // LCD 문장 가로 8개, 세로 2개 문자
}

void loop() {
  lcd.setCursor(0, 0); // 맨 윗 줄 첫번째 위치 // lcd.home()
  // Print a message to the LCD.
  lcd.print("hello, w"); // ,와 스페이스까지 총 8개 문자
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1); // 커서 한 줄 밑으로
  lcd.print("orld!");
  delay(1000);
}
