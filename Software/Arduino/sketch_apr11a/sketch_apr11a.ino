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
<<<<<<< HEAD
*/
=======
 */
void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  Serial.print("Pins reset");
  
  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);
  Serial.print("Sensor 1 initiated");


  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  Serial.print("Sensor 2 activated");

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

  Serial.print("Sensor 2 initiated");

  delay(10);

    // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
   Serial.print("Sensor 3 initiated");
}

void read_three_ranges(){
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

  //16 bit integers for received ranges in milimeters
  uint16_t range_1 = 0;
  uint16_t range_2 = 0;
  uint16_t range_3 = 0;
  
  // Get ranges from all three sensors
  if(measure1.RangeStatus != 4) {     // if not out of range
    range_1 = measure1.RangeMilliMeter;
  } else{
    range_1 = 1;
  }
  if(measure2.RangeStatus != 4) {     // if not out of range
    range_2 = measure2.RangeMilliMeter;
  } else{
    range_2 = 1;
  }
  if(measure3.RangeStatus != 4) {     // if not out of range
    range_3 = measure3.RangeMilliMeter;
  } else{
    range_3 = 1;
  }

  //Split each range_ data into two uint8_t and update to global array
  sensorData[1] = (range_1>>8)+1;
  sensorData[2] = range_1;
  sensorData[3] = (range_2>>8)+1;
  sensorData[4] = range_2;
  sensorData[5] = (range_3>>8)+1;
  sensorData[6] = range_3;

  uint16_t toReceive = (sensorData[1]<<8)|sensorData[2]; 
  Serial.println(toReceive);
  Serial.println();
}

void read_dual_sensors() {
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
  Serial.print("1: ");
  if(measure1.RangeStatus != 4) {     // if not out of range
    Serial.print(measure1.RangeMilliMeter);
  } else {
    Serial.print("Out of range");
  }
  
  Serial.print(" ");

  // print sensor two reading
  Serial.print("2: ");
  if(measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
  } else {
    Serial.print("Out of range");
  }

  Serial.print(" ");
  
  // print sensor three reading
  Serial.print("3: ");
  if(measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
  } else {
    Serial.print("Out of range");
  }
  
  Serial.println();
}

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
  // read_dual_sensors();
  read_three_ranges();
  delay(100);

  read_three_ranges(); // Update global array sensorData
  SPI.beginTransaction(slaveSettings);
  digitalWrite (slavePin, LOW);
  SPI.transfer(sensorData[0]); // Start byte
  delay(3);
  SPI.transfer(sensorData[1]); // 8 MSB's of sensor 1
  delay(3);
  SPI.transfer(sensorData[2]); // 8 LSB's of sensor 1
  delay(3);
  SPI.transfer(sensorData[3]); // 8 MSB's of sensor 2
  delay(3);
  SPI.transfer(sensorData[4]); // 8 LSB's of sensor 2
  delay(3);
  SPI.transfer(sensorData[5]); // 8 MSB's of sensor 3
  delay(3);
  SPI.transfer(sensorData[6]); // 8 LSB's of sensor 3
  delay(3);
  digitalWrite (slavePin, HIGH);
  SPI.endTransaction();
  Serial.println("Sending...");
  //delay(10);
}
