#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
 
LiquidCrystal_I2C lcd(0x3F, 16, 2);
 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
String APIKEY = "d6032c816e0ef958bbc1aa475ad88d3e";
String CityID = "1835848"; // Seoul, KR

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[]="api.openweathermap.org";
String result;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 219, 102);
IPAddress dns_server(61,41,153,2);
IPAddress gateway(192,168,219,1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

int  counter = 60;
String weatherDescription ="";
String weatherLocation = "";
String Country;
float Temperature;
float Humidity;
float Pressure;
 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
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
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, dns_server, gateway);
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
    if(counter == 60) //Get new data every 10 minutes
    {
      counter = 0;
      displayGettingData();
      delay(1000);
      getWeatherData();
    }else
    {
      counter++;
      displayWeather(weatherLocation,weatherDescription);
      delay(5000);
      displayConditions(Temperature,Humidity,Pressure);
      delay(5000);
    }
}
 
void getWeatherData() //client function to send/receive GET request data.
{
  if (client.connect(server, 80)) {  //starts client connection, checks for connection
    client.println("GET /data/2.5/weather?id="+CityID+"&units=metric&APPID="+APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }
 
  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
      result = result+c;
    }
 
  client.stop(); //stop client
  result.replace('[', ' ');
  result.replace(']', ' ');
  Serial.println(result);
 
char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';
 
StaticJsonBuffer<1024> json_buf;
JsonObject &root = json_buf.parseObject(jsonArray);
if (!root.success())
{
  Serial.println("parseObject() failed");
}
 
String location = root["name"];
String country = root["sys"]["country"];
float temperature = root["main"]["temp"];
float humidity = root["main"]["humidity"];
String weather = root["weather"]["main"];
String description = root["weather"]["description"];
float pressure = root["main"]["pressure"];
 
weatherDescription = description;
weatherLocation = location;
Country = country;
Temperature = temperature;
Humidity = humidity;
Pressure = pressure;
 
}
 
void displayWeather(String location,String description)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(location);
  lcd.print(", ");
  lcd.print(Country);
  lcd.setCursor(0,1);
  lcd.print(description);
}
 
void displayConditions(float Temperature,float Humidity, float Pressure)
{
  lcd.clear();
  lcd.print("T:"); 
 lcd.print(Temperature,1);
 lcd.print((char)223);
 lcd.print("C ");
 
 //Printing Humidity
 lcd.print(" H:");
 lcd.print(Humidity,0);
 lcd.print(" %");
 
 //Printing Pressure
 lcd.setCursor(0,1);
 lcd.print("P: ");
 lcd.print(Pressure,1);
 lcd.print(" hPa");
 
}
 
void displayGettingData()
{
  lcd.clear();
  lcd.print("Getting data");
}
