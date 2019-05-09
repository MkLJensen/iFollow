#include "SPI.h"

// SPI slave-select pin
const int slavePin = 53;

//Speed, data order and data mode - to be matched with PSoC creator settings
SPISettings MasterSettings(2000000, MSBFIRST, SPI_MODE0);


/*
    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
    Keep sensor #1 awake by keeping XSHUT pin high
    Put all other sensors into shutdown by pulling XSHUT pins low
    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
*/
void setup() {
  //SS pin set to output
  pinMode (slavePin, OUTPUT);
  // initialize SPI:
  SPI.begin();
  // initialize UART:
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  Serial.println("Starting...");
}

void loop() {
  int data = Serial.read();
  if (data != -1)
  {
    Serial.print(data);
    SPI.beginTransaction(MasterSettings);
    digitalWrite (slavePin, LOW);
    if (SPI.transfer(data) == 0)
    {
      Serial.println("Not Flipped");
    }
    else
    {
      Serial.println("Flipped");
    }
    digitalWrite (slavePin, HIGH);
    SPI.endTransaction();

    Serial.println("Sending... ");
    delay(100);
  }
}
