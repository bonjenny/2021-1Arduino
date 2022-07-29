/*
  Repeating Web client

 This sketch connects to a a web server and makes a request
 using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
 the Adafruit Ethernet shield, either one will work, as long as it's got
 a Wiznet Ethernet module on board.

 This example uses DNS, by assigning the Ethernet client with a MAC address,
 IP address, and DNS address.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 19 Apr 2012
 by Tom Igoe
 modified 21 Jan 2014
 by Federico Vanzati

 http://www.arduino.cc/en/Tutorial/WebClientRepeating
 This code is in the public domain.

 */

#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <core_build_options.h>
#include <swRTC.h>

int bluetoothTx = 2;
int bluetoothRx = 3;


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
LiquidCrystal_I2C lcd(0x3F, 16, 2); // 안되면 주소를 0x27->0x3F로 변경
String lcdString = "";                   //객체 선언 : 출력 할 글자 저장

swRTC rtc;

int speakerPin = 8;
int switchPin = 9;
int temp;

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

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 219, 102);
IPAddress myDns(61, 41, 153, 2);

// initialize the library instance:
EthernetClient client;

char server[] = "www.kma.go.kr";  // also change the Host line in httpRequest()
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  //pinMode(speakerPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  bluetooth.begin(9600);   //블루투스 초기화
  // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);

  // initialize the LCD
  lcd.begin();
  lcd.clear();             //화면 초기화

  // Turn on the blacklight and print a message.
  rtc.stopRTC();           //정지
  rtc.setTime(23,48,0);    //시간, 분, 초 초기화
  rtc.setDate(12, 6, 2021);  //일, 월, 년 초기화 
  rtc.startRTC();          //시작
  
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  String a[3];
  int i=0;
  
  String tmp; // 온도
  String wfEn; // 날씨
  String reh;  // 습도
  String tmp_str;
  
  int tmp_index;
  int tmp_length;
  String rec, rec1, rec2; // 옷차림 결정
  
  if (client.connect(server, 80)) {  //starts client connection, checks for connection
    client.println("GET /wid/queryDFSRSS.jsp?zone=1156063000 HTTP/1.1");
    client.println("Host: www.kma.go.kr");
    client.println("Connection: close");
    client.println();

    delay(10);
    while(client.available()){
      
      String line = client.readStringUntil('\n');
      i= line.indexOf("</temp>");

      if(i>0){
        tmp_str="<temp>";
        tmp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        Serial.println(tmp);
        rec = determineRec(tmp);
        tmp_index = rec.indexOf(","); // 첫 번재 콤마 위치
        tmp_length = rec.length();
        rec1 = rec.substring(0, tmp_index);
        rec2 = rec.substring(tmp_index + 1, tmp_length);
        Serial.println(rec1);
        Serial.println(rec2);
      }

      i= line.indexOf("</wfEn>");

      if(i>0){
        tmp_str="<wfEn>";
        wfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        if(wfEn.equals("rain")) {
          Serial.println("It's a rainy day");
          Serial.println("Take an umbrella");
        }
        else {
          Serial.print("Today's weather");
          Serial.println(" is " + wfEn);
        }
      }

      i= line.indexOf("</reh>");

      if(i>0){
        tmp_str="<reh>";
        reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        Serial.println(reh);
        Serial.println();
        break;
      }
    }

    //(1) 날씨 출력
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print("T:");
    lcd.print(tmp);
    lcd.print((char)223);
    lcd.print("C ");
    lcd.print(" H:");
    lcd.print(reh);
    lcd.print("%");
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print("Cloudy: ");
    lcd.print(wfEn);
    delay(2000);

    //(2) 옷 추천
    lcd.clear();
    lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
    lcd.print(rec1);
    lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
    lcd.print(rec2);
    delay(2000);

    //(3) 우산 챙길지말지
    if(wfEn.equals("rain")) {
      lcd.clear();
      lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
      lcd.print("It's a rainy day");
      lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
      lcd.print("Take an umbrella");
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0); // 맨 위, 첫 번째 줄
      lcd.print("Today's weather");
      lcd.setCursor(0, 1); // 맨 아래, 두 번째 줄
      lcd.print("is " + wfEn);
    }
    delay(2000);
  }

  //시계 출력
  int day;
  lcd.clear();
  lcd.setCursor(0,0);                    //커서를 0,0에 지정
  
  //1초 단위로 갱신하며 현재시간을 LCD에 출력
  Set_AMPM(rtc.getHours()); 
  lcd.print(":");
  Set_lowThanTen(rtc.getMinutes());
  lcd.print(":");
  Set_lowThanTen(rtc.getSeconds());
  //날짜를 LCD에 출력
  lcd.print("[");
  Set_lowThanTen(rtc.getMonth());
  lcd.print("/");
  Set_lowThanTen(rtc.getDay());
  lcd.print("]");
  //세팅된 알람시간을 LCD에 출력
  lcd.setCursor(0,1);
  lcd.print("Alarm ");
  Set_AMPM(temp/100);
  lcd.print(":");
  Set_lowThanTen(temp%100); 
  
  //1초마다 LCD갱신
  lcdString = "";                      //문자열 초기화
  delay(1000);
  
  if(temp/100 == rtc.getHours() && temp%100 == rtc.getMinutes()) {
    if(wfEn.equals("rain")) {
      bearSong();
    }
    else {
      schoolSong();
    }
  }

  //스위치버튼이 눌렸을 경우 피에조센서의 소리를 0으로 하고 알람시간을 초기화 한다 
  if(!digitalRead(switchPin)) {
    temp = 0;
    day = 0;
    noTone(speakerPin);
    Serial.println("Alarm clock initialize");
    Serial.println("AM0:00");
  }
  
  //블루투스 통신을 통해 알람시간을 입력받고 시리얼 모니터에 출력
  char theDay[4];
  int k = 0;
  if(bluetooth.available())
  {
    while(bluetooth.available()) {
      theDay[k] = (char)bluetooth.read();
      k++;
    }
    day = atoi(theDay);
    if(day/100 >= 12) {
      Serial.print("PM");
      Serial.print((day/100)-12);
    }
    else {
      Serial.print("AM");
      Serial.print(day/100);
    }
    Serial.print(":");
    if(day%100 < 10)
      Serial.print("0");
    Serial.println(day%100);
    temp = checkTheAlarmClock(day);
  }
  
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
}

//AM PM을 구분해 주는 함수
void Set_AMPM(int hour) {
  if(hour >=12) 
    lcd.print("PM");
  else 
    lcd.print("AM");

  lcd.print(hour%12, DEC);     //시간 출력
}

//10보다 작은수를 출력할때 앞에 0을 출력하게 하는 함수
void Set_lowThanTen(int time) {
  if(time < 10) {
    lcd.print("0");
    lcd.print(time%10);
  }
  else
    lcd.print(time);
}

//유효한 알람시간인지 체크하는 함수
int checkTheAlarmClock(int time) {
  if(time/100 < 24 && time %100 < 60) {
    Serial.println("Success");
    return time;
  }
  else {
    Serial.println("Failed");
    return 0;
  }  
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {  //starts client connection, checks for connection
    client.println("GET /wid/queryDFSRSS.jsp?zone=1156063000 HTTP/1.1");
    client.println("Host: www.kma.go.kr");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

// 어떤 옷을 입을지 결정
String determineRec(String temperature) {
  String rec;
  int tmpt;
  tmpt = temperature.toInt();
  if(tmpt >= 28) {
    rec = "Rec: sleeveless,shorts & a dress";
    // 민소매, 반팔, 반바지, 원피스 추천
  }
  if(tmpt >= 23 && tmpt < 28) {
    rec = "Rec: thin shirts,and cotton pants";
    // 반팔, 얇은 셔츠, 반바지, 면바지 추천
  }
  if(tmpt >= 20 && tmpt < 23) {
    rec = "Rec: long sleeve,cardigan & jeans";
    // 얇은 가디건, 긴팔, 면바지, 청바지 추천
  }
  if(tmpt >= 17 && tmpt < 20) {
    rec = "Rec: thin knit,mantoman & jeans";
    // 얇은 니트, 맨투맨, 가디건, 청바지 추천
  }
  if(tmpt >= 12 && tmpt < 17) {
    rec = "Rec: stockings,jacket & jeans";
    // 자켓, 가디건, 야상, 스타킹, 청바지, 면바지 추천
  }
  if(tmpt >= 9 && tmpt < 12) {
    rec = "Rec: trench coat,knit and jeans";
    // 자켓, 트렌치코트, 야상, 니트, 청바지, 스타킹 추천
  }
  if(tmpt >= 5 && tmpt < 9) {
    rec = "Rec: coat/hittec,knit & leggings";
    // 코트, 가죽자켓, 히트텍, 니트, 레깅스 추천
  }
  if(tmpt < 5) {
    rec = "Rec: padding,nanny products";
    // 패딩, 두꺼운 코트, 목도리, 기모제품 추천
  }
  return rec;
}

// 곰 세마리 알람노래
void bearSong() {
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

// 학교 종이 땡땡땡 알람노래
void schoolSong() {
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
