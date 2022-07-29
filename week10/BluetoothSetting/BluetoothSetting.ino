// 소프트웨어 시리얼을 이용해서 블루투스 초기세팅하는 소스
#include <SoftwareSerial.h> 

SoftwareSerial BT(2, 3); //Connect HC-06 TX,RX 

void setup()  
{
  Serial.begin(9600);
  BT.begin(9600);//블루투스연결
}

void loop()
{
  if (BT.available())
  {
    Serial.write(BT.read());
  }
  
  if (Serial.available())
  {
    BT.write(Serial.read());
  }
}
