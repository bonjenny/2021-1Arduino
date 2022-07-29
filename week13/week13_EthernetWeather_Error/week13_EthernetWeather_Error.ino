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
#include <ArduinoJson.h>

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.kma.go.kr";  // also change the Host line in httpRequest()
//IPAddress server(64,131,82,241);

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 219, 102);
IPAddress myDns(61, 41, 153, 2);

// initialize the library instance:
EthernetClient client;

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 3*1000;  // delay between updates, in milliseconds

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2); // 안되면 주소를 0x27->0x3F로 변경

String a[3];
int i=0;
int counter=0;
String Date;
String temp;
String wfEn;
String reh;
String tmp_str;

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // start serial port:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  int cursorPosition=0;
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Connecting");  
  Serial.println("Connecting");

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
    lcd.setCursor(cursorPosition, 2);
    lcd.print(".");
    cursorPosition++;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  lcd.clear();
  lcd.print("   Connected!");  
  Serial.println("Connected");
  delay(1000);
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  // if (client.available()) {
  //   char c = client.read();
  //   Serial.write(c);
  // }
  
  if(counter == 60) //Get new data every 10 minutes
  {
    counter = 0;
    displayGettingData();
    delay(1000);
    getWeatherData();
  }
  else {
    counter++;
    displayWeather(Date);
    delay(5000);
    displayConditions(temp,reh,wfEn);
    delay(5000);
  }
}
 
void getWeatherData() //client function to send/receive GET request data.
{
  if (client.connect(server, 80)) {  //starts client connection, checks for connection
    client.println("GET /wid/queryDFSRSS.jsp?zone=1156063000 HTTP/1.1");
    client.println("Host: www.kma.go.kr");
    client.println("Connection: close");
    client.println();

    delay(10);
    while(client.available()){
      String line = client.readStringUntil('\n');

      i = line.indexOf("</pubDate>");
      if(i>0) {
        tmp_str = "<pubDate>";
        Date = line.substring(line.indexOf(tmp_str)+tmp_str.length(), i);
      }
      i= line.indexOf("</temp>");
      if(i>0){
        tmp_str="<temp>";
        temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      }
      i= line.indexOf("</wfEn>");
      if(i>0){
        tmp_str="<wfEn>";
        wfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      }
      i= line.indexOf("</reh>");
      if(i>0){
        tmp_str="<reh>";
        reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        break;
      }
    }
  }
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }
}
 
void displayWeather(String Date)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Seoul, Korea");
  lcd.setCursor(0,1);
  lcd.print(Date);
}
 
void displayConditions(String Temperature, String Humidity, String Cloudy)
{
  lcd.clear();
  lcd.print("T:"); 
 lcd.print(Temperature);
 lcd.print((char)223);
 lcd.print("C ");
 
 //Printing Humidity
 lcd.print(" H:");
 lcd.print(Humidity);
 lcd.print(" %");
 
 //Printing Cloudy
 lcd.setCursor(0,1);
 lcd.print("Cloudy: ");
 lcd.print(Cloudy);
 
}
 
void displayGettingData()
{
  lcd.clear();
  lcd.print("Getting data");
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
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
