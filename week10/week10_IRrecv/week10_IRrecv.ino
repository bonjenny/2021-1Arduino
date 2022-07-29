#include <IRremote.h> //adds the library code to the sketch

const int irReceiverPin = 2; //pin the receiver is connected to
const int ledPin = 12;

IRrecv irrecv(irReceiverPin); //create an IRrecv object
decode_results decodedSignal; //stores results from IR detectorvoid

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //wait for serial port to connect.
  }
  pinMode(ledPin, OUTPUT);
  irrecv.enableIRIn(); //Start the receiver object
}

boolean lightState = false;
unsigned long last = millis();

void loop() {
  if (irrecv.decode(&decodedSignal) == true)
  {
    if (millis() - last > 250/*250*/)
    {
      lightState = !lightState;
      digitalWrite(ledPin, lightState);
      Serial.print("value=");
      Serial.println(decodedSignal.value, HEX);
      Serial.print("decode_type=");
      Serial.println(decodedSignal.decode_type);
    }
 
    last = millis();
    irrecv.resume();
  }
}
