/* L3G4200D.h */
/**********************
   L3G4200D Registers
**********************/

#include <SPI.h>

#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_TSH_XH 0x32
#define INT1_TSH_XL 0x33
#define INT1_TSH_YH 0x34
#define INT1_TSH_YL 0x35
#define INT1_TSH_ZH 0x36
#define INT1_TSH_ZL 0x37
#define INT1_DURATION 0x38

#include <Servo.h>

//pin definitions
const int int2pin = 6;
const int int1pin = 7;
const int chipSelect = 10;

//gyro readings
int x, y, z;

int motor_control = 8;
Servo servo;
int potpin = 0; //analog pin used to connect the potentiometer
int val; //variable to read the value from the analog pin

void setup()
{
  servo.attach(motor_control);
  
  Serial.begin(9600);

  //Start the SPI library:
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  pinMode(int1pin, INPUT);
  pinMode(int2pin, INPUT);
  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect, HIGH);
  delay(100);

  setupL3G4200D(2); //Configure L3G4200 with selectable full scale range
  //0: 250dps
  //1: 500dps
  //2: 2000dps

  servo.write(0);
}

void loop() {
  int servo_range, old_servo_range;
  
  //Don't read gyro values until the gyro says it's ready
  while(!digitalRead(int2pin));
  
  getGyroValues(); //This will update x, y, and z with new values

  Serial.print("x=");
  Serial.print(x, DEC);
  Serial.print("\t");
  Serial.print("y=");
  Serial.print(y, DEC);
  Serial.print("\t");
  Serial.print("z=");
  Serial.print(z, DEC);
  Serial.print("\t");
  Serial.println();

  val = x; //reads the value of the gyro y axis (change if you use other axis)
  val = map(val, 0, 1023, 0, 179); //scale it to use it with the servo (value between 0 and 180)
  
  if(val < -20 || val > 20)
    servo.write(val);

  Serial.print("servo_range = ");
  Serial.print("\t");
  Serial.print(val, DEC);
  Serial.println();
  Serial.println();
  
  delay(100);
}

int readRegister(byte address)
{
  int toRead;

  address |= 0x80; //This tells the L3G4200D we're reading:

  digitalWrite(chipSelect, LOW);
  SPI.transfer(address);
  toRead = SPI.transfer(0x00);
  digitalWrite(chipSelect, HIGH);

  return toRead;
}

void writeRegister(byte address, byte data)
{
  address &= 0x7F; //This to tell the L3G4200D we're writing

  digitalWrite(chipSelect, LOW);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(chipSelect, HIGH);
}

int setupL3G4200D(byte fullScale)
{
  //Let's first check that we're communicating properly
  //The WHO_AM_I register should read 0xD3
  if(readRegister(WHO_AM_I)!=0xD3)
    return -1;
  
  //Enable x, y, z and turn off power down:
  writeRegister(CTRL_REG1, 0b00001111);

  //if you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(CTRL_REG2, 0b00000000);

  //Configure CTRL_REG3 to generate data ready interrupt on INT2
  //No interrupts used on INT1, if you'd like to configure INT1
  //or INT2 otherwise, consult the datasheet:
  writeRegister(CTRL_REG3, 0b00001000);

  //CTRL_REG4 controls the full-scale range, among other things:
  fullScale &= 0x03;
  writeRegister(CTRL_REG4, fullScale << 4);
  
  //CTRL_REG5 controls high-pass filtering of outputs, use it
  writeRegister(CTRL_REG5, 0b00000000);
}

void getGyroValues()
{
  x = (readRegister(0x29)&0xFF)<<8;
  x |= (readRegister(0x28)&0xFF);
  
  y = (readRegister(0x2B)&0xFF)<<8;
  y |= (readRegister(0x2A)&0xFF);
  
  z = (readRegister(0x2D)&0xFF)<<8;
  z |= (readRegister(0x2C)&0xFF);
}
