
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

void setup() {
  
}

void loop() {
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
