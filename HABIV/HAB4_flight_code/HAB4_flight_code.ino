/**
   HAB4 flight code.

   Includes functions for recieving data,
   writing it to the SD card,
   and the main control loop.

   Originally based from the HAB3 flight code.


   BOARD: GENERIC STM32F4 SERIES
   BLACK F407VE

*/
#include <IridiumSBD.h>
#include <Adafruit_GPS.h>
#include "Adafruit_MAX31855.h"
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include "Servo.h"
#include "PID_v1.h"
#include "Math.h"

#include "IntersemaBaro.h"

#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

#define LOG_FILE "datalog.txt"
#define DATA_DELAY_TIME 10000

#define DIAGNOSTICS false // Iridium Diagnostics
#define GPSECHO false     // GPS Diagnostics

//Define serial communication pins
#define IridiumRX PA12
#define IridiumTX PA11
#define GPSRX PB0
#define GPSTX PB1
//#include "SoftwareSerial.h" //FOR XBEE

#define IridiumSleep D6

#define CTR1 PC12
#define CTR2 PC13

//Define IMU pins
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW <---EDIT WITH CORRECT VALUES
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW <---EDIT WITH CORRECT VALUES
#define DECLINATION 13.25 // https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml#declination

//XBEE
#define XBEE_RX PB1 //CHANGE! can be any 
#define XBEE_TX PB2 //CHANGE!!

//SERVO
#define servoPinL PA10 //CHANGE! can be PA10, PA9, PA0, PA1 top to bottom LR
#define servoPinR PA9 //CHANGE!
#define releasePin PA0 //CHANGE!
#define SENSITIVITY 15 //sensitivity of the controls. ie, if you give the control to move 

//Define SPI slave select pins
#define altimeterChipSelect D7 // IMPORTANT!!!!! IF THIS IS CHANGED, YOU MUST CHANGE chipSelect IN IntersemaBaro.h
#define thermocoupleChipSelect D9
#define sdCardChipSelect D8

// Declare Serial communication
HardwareSerial GPSSerial(GPSRX, GPSTX);
HardwareSerial IridiumSerial(IridiumRX, IridiumTX);

// Declare peripheral objects
IridiumSBD modem(IridiumSerial, IridiumSleep);
Adafruit_GPS GPS(&GPSSerial);
Intersema::BaroPressure_MS5607B baro;
Adafruit_MAX31855 thermocouple(thermocoupleChipSelect);
RTC_PCF8523 rtc;

//Declare IMU
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

//XBEE COMMUNICATION
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
//SoftwareSerial XBee(2, 3); //CHANGE PINS <--- long range: ground to payload
//SoftwareSerial XBee(4, 5); //CHANGE PINS <--- short range: payload to balloon

HardwareSerial XBee(XBEE_RX, XBEE_TX);

//SERVO
Servo servoL;
Servo servoR;
Servo servoRelease;
int angleR = 0; // global variable for what the right servo's angle is
int angleL = 0; // global variable for what the left servo's angle is

bool released = false;



//PID STUFF
float Kp=0; //Initial Proportional Gain
float Ki=10; //Initial Integral Gain
float Kd=0; // Initial Differential Gain

/**
   sets the CTR1, CTR2 pins depending on which
   reciever rf chosen.
*/


void setMode(int rf) {
  digitalWrite(CTR1, LOW);
  digitalWrite(CTR2, LOW);

  if (rf == 1) {
    digitalWrite(CTR1, HIGH);
  }
  else if (rf == 2) {
    digitalWrite(CTR2, HIGH);
  }
  else if (rf == 3) {
    digitalWrite(CTR1, HIGH);
    digitalWrite(CTR2, HIGH);
  }
}




/**
   Buffers all peripheral data into the given structs.
*/
bool getAllData(GPSData* gpsData, AltimeterData* altimeterData, ThermocoupleData* thermocoupleData, RTCData* rtcData, IMUData* imuData) {

  getGPSData(gpsData);
  getAltimeterData(altimeterData);
  getThermocoupleData(thermocoupleData);
  getRTCData(rtcData);
  getIMUData(imuData, true); //True for DPS values

  return true;
}

/**
   Gets the data from the Xbee and converts it to something controllable

*/

uint32_t timer = millis();


void initializeSPI() {
  Serial.println("Starting up SPI...");

  SPI.begin();

  //Set all chip select pins to high
  pinMode(altimeterChipSelect, OUTPUT);
  digitalWrite(altimeterChipSelect, HIGH);
  pinMode(thermocoupleChipSelect, OUTPUT);
  digitalWrite(thermocoupleChipSelect, HIGH);
  pinMode(sdCardChipSelect, OUTPUT);
  digitalWrite(sdCardChipSelect, HIGH);

  Serial.println("Wrote all CS pins to high.");

  Serial.println("Success");
}

/**
   This function will run on a loop when the RockBLOCK is attempting
   to send data. We just collect data and then write it to the data log.
*/
bool ISBDCallback()
{
  //Serial.println("Still trying to send data... STORING DATA IN A CALLBACK");
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return true; // we can fail to parse a sentence in which case we should just wait for another
  }


  //delay(DATA_DELAY_TIME);

  return true;
}

#if DIAGNOSTICS
void ISBDConsoleCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}

void ISBDDiagsCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}
#endif

void setup()
{
  pinMode(CTR1, OUTPUT);
  pinMode(CTR2, OUTPUT);

  Serial.begin(115200);

  initializeSPI();

  Serial.println("About to start GPS");
  //startGPS();

  Serial.println("About to start Altimeter");
  startAltimeter();

  Serial.println("About to start Thermocouple");
  startThermocouple();

  Serial.println("About to start RTC");
  startRTC();

  Serial.println("About to start SD");
  startSD();

  Serial.println("About to start RockBLOCK");
  //startRockBlock();

  Serial.println("About to start IMU");
  if (!lsm.begin()) {
    Serial.println("Failed to communicate with LSM9DS1.");
    while (1);
  }
  setupLSM();



  servoL.attach(servoPinL);
  servoR.attach(servoPinR);
  servoRelease.attach(releasePin);
  servoL.write(angleL); //pointed straight up, angleL = 0
  servoR.write(angleR); //pointed straight up, angleR = 0



}

int rockBlockSendTime = 0;
int rockBlockSendRate = 60000;

void loop()
{
  Serial.println("Looping");
  GPSData gpsData;
  AltimeterData altimeterData;
  ThermocoupleData thermocoupleData;
  RTCData rtcData;
  IMUData imuData;

  int input;

  getAllData(&gpsData, &altimeterData, &thermocoupleData, &rtcData, &imuData);
  writeAllDataToSDCard(&gpsData, &altimeterData, &thermocoupleData, &rtcData);

  //Should we send data to ground?
  if (false) {//if (millis() > rockBlockSendTime) {

    /* The data will be written to a dataString in this format:
      <TripNumber>:<Hour>:<Minute>:<FixQuality>:<Speed>:<Angle>:<Lon>:<Lat>:<Altitude>:<ExternalTemp>
    */

    Serial.println("It's time to send a message from the rockblock");

    String hour = String((int) rtcData.hour, DEC);
    String minute = String((int) rtcData.minute, DEC);
    String fixQuality = String((int) gpsData.fixQuality, DEC);
    String speed = String(gpsData.speed, 2);
    String angle = String(gpsData.angle, 2);
    String lon = String(gpsData.longitude, 6);
    String lat = String(gpsData.latitude, 6);
    String altitude = String((int) altimeterData.heightMeters1, DEC);
    String externalTemp = String((int) thermocoupleData.externalFarenheit, DEC);

    String dataString = String("202");
    dataString.concat(':'); dataString.concat(hour);
    dataString.concat(':'); dataString.concat(minute);
    dataString.concat(':'); dataString.concat(fixQuality);
    dataString.concat(':'); dataString.concat(speed);
    dataString.concat(':'); dataString.concat(angle);
    dataString.concat(':'); dataString.concat(lon);
    dataString.concat(':'); dataString.concat(lat);
    dataString.concat(':'); dataString.concat(altitude);
    dataString.concat(':'); dataString.concat(externalTemp);

    Serial.print("Attmepting to send ################################################################################################");
    Serial.println(dataString);
    rockBlockSendData(dataString.c_str()); // Send the string data to the rock block

    rockBlockSendTime = millis() + rockBlockSendRate; // Only send data through rock block once every minute.
  }

  /*
     Controls section of the loop!
  */
  if (XBee.available() > 0) {
    if (getXBeeControl() && !released) { //update angleL and angleR
      released = true;
      //move the  release servo
    }
    servoR.write(angleR);
    servoL.write(angleL);
  }

  Serial.print("Right servo: ");
  Serial.println(angleR);
  Serial.print("Left servo: ");
  Serial.println(angleL);

  delay(DATA_DELAY_TIME);

}
