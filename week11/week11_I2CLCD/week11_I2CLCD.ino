#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2); // 안되면 주소를 0x27->0x3F로 변경

int speakerPin = 8; 
#define C4 262
#define CS4 277
#define D4 294
#define DS4 311
#define E4 330
#define F4 349
#define FS4 370
#define G4 392
#define GS4 415
#define A4 440
#define AS4 466
#define B4 494
#define C5 523

void setup()
{
  // initialize Serial
  Serial.begin(9600);

  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop()
{
  char c = (char)Serial.read();
  int tmp, hum;

  Serial.println("온도 입력: ");
  while(Serial.available() == 0) {}
  tmp = Serial.parseInt();
  Serial.println(tmp);

  Serial.println("습도 입력: ");
  while(Serial.available() == 0) {}
  hum = Serial.parseInt();
  Serial.println(hum);
  
  lcd.clear();
  lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
  lcd.print("tmp: ");
  lcd.print(tmp);
  lcd.print("C(deg)");

  lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
  lcd.print("hum: ");
  lcd.print(hum);
  lcd.print("%");

  if(hum >= 60) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("It's a rainy day");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("Take an umbrella");

    // 곰 세마리 출력
    tone(speakerPin, C4); //곰
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //세
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //마
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //리
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //가
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, E4); //한
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //집
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //에
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //있
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //어
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, G4); //아
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //빠
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //곰
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //엄
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //마
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //곰
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, C4); //애
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //기
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //곰
    delay(950);
    noTone(speakerPin);
    delay(50);

    tone(speakerPin, G4); //아
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //빠
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //곰
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //은
    delay(450);
    noTone(speakerPin);
    delay(50);
  
    tone(speakerPin, G4); //뚱
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //뚱
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //해
    delay(950);
    noTone(speakerPin);
    delay(50);
 
    tone(speakerPin, G4); //엄
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //마
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //곰
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //은
    delay(450);
    noTone(speakerPin);
    delay(50);
  
    tone(speakerPin, G4); //날
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //씬
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //해
    delay(950);
    noTone(speakerPin);
    delay(50);
  
    tone(speakerPin, G4); //애
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //기
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //곰
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //은
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, G4); //너
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //무
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //귀
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, A4); //여
    delay(200);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //워
    delay(950);
    noTone(speakerPin);
    delay(50);
   
    tone(speakerPin, C5); //으
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //쓱
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C5); //으
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //쓱
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, E4); //잘
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, D4); //한
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, C4); //다
    delay(950);
    noTone(speakerPin);
    delay(50);
    
    noTone(speakerPin);
    delay(1800);
  }
  
  if(hum < 60) {    
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("It's a sunny day");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("Have a good day!");
    
    // 학교 종이 땡땡땡 출력    
    tone(speakerPin, G4); //학
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //교
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, A4); //종
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, A4); //이
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, G4); //땡
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //땡
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //땡
    delay(950);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, G4); //어
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //서
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //모
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //이
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, D4); //자
    delay(1450);
    noTone(speakerPin);
    delay(50);
    noTone(speakerPin);
    delay(500);
  
    tone(speakerPin, G4); //선
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //생
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, A4); //님
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, A4); //이
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, G4); //우
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, G4); //리
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //를
    delay(950);
    noTone(speakerPin);
    delay(50);
   
    tone(speakerPin, G4); //기
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //다
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, D4); //리
    delay(450);
    noTone(speakerPin);
    delay(50);
    tone(speakerPin, E4); //신
    delay(450);
    noTone(speakerPin);
    delay(50);
    
    tone(speakerPin, C4); //다
    delay(1450);
    noTone(speakerPin);
    delay(50);
    noTone(speakerPin);
    delay(500);
  
    noTone(speakerPin);
    delay(1800);
  }
  
  if(tmp >= 28) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: sleeveless,");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("shorts & a dress");
    // 민소매, 반팔, 반바지, 원피스 추천
  }
  if(23 <= tmp < 28) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: thin shirts");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("and cotton pants");
    // 반팔, 얇은 셔츠, 반바지, 면바지 추천
  }
  if(20 <= tmp < 23) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: long sleeve");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("cardigan & jeans");
    // 얇은 가디건, 긴팔, 면바지, 청바지 추천
  }
  if(17 <= tmp < 20) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: thin knit,");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("mantoman, jeans");
    // 얇은 니트, 맨투맨, 가디건, 청바지 추천
  }
  if(12 <= tmp < 17) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: jacket,jeans");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("and stockings");
    // 자켓, 가디건, 야상, 스타킹, 청바지, 면바지 추천
  }
  if(9 <= tmp < 12) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: trench coat");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("knit and jeans");
    // 자켓, 트렌치코트, 야상, 니트, 청바지, 스타킹 추천
  }
  if(5 <= tmp < 9) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: coat,hittec");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("knit & leggings");
    // 코트, 가죽자켓, 히트텍, 니트, 레깅스 추천
  }
  if(tmp < 5) {
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("Rec: padding");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("& nanny products");
    // 패딩, 두꺼운 코트, 목도리, 기모제품 추천
  }
  
  delay(2000);
}
