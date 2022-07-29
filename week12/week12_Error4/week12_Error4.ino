//zoomkat 12-22-10
//simple ethernet client test code
//for use with IDE 0021 and W5100 ethernet shield
//modify the arduino lan ip address as needed
//open serial monitor to see what the arduino receives
//push the shield reset button to run client again

#include <SPI.h>
#include <Ethernet.h>
String readString, readString1;
int x=0;
char lf=10;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 219, 102 };
byte server[] = { 61, 41, 153, 2 }; // NOAA

EthernetClient client; //(server, 80);

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  Serial.println("starting simple arduino client test");
  Serial.println();
  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /data/5day2/44013_5day.txt HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    //Serial.print(c);  // uncomment to see raw feed
    if (c==lf) x=(x+1);
    if (x==14) readString += c;
    //readString += c;
  }

  if (!client.connected()) {
     client.stop();

    Serial.println("Current data row:" );
    Serial.print(readString);
    Serial.println();
    readString1 = (readString.substring(41,43));
    Serial.println();
    Serial.print("DPD sec: ");
    Serial.println(readString1);
    Serial.println("done");

    for(;;);

    }
 }
