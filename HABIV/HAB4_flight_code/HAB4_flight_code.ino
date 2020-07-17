/**
   HAB4 flight code.

   Includes functions for recieving data,
   writing it to the SD card,
   and the main control loop.

   Originally based from the HAB3 flight code.


   BOARD: GENERIC STM32F4 SERIES
   BLACK F407VE


   THIS FILE WILL INCLUDE ALL OF THE GLOBAL VARIABLES AND DEFINITIONS.

*/
#include <IridiumSBD.h>
#include <Adafruit_GPS.h>
#include "Adafruit_MAX31855.h"
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include "Servo.h"
#include <AutoPID.h>
#include "Math.h"

#include "IntersemaBaro.h"

#include "I2C_Anything.h"

#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

#define LOG_FILE "datalog.txt"
#define DATA_DELAY_TIME 10000

#define DIAGNOSTICS false // Iridium Diagnostics
#define GPSECHO true     // GPS Diagnostics

//Define serial communication pins
#define IridiumRX PA12
#define IridiumTX PA11

#define GPSRX PB0
#define GPSTX PB1

//#include "SoftwareSerial.h" //FOR XBEE

#define IridiumSleep PB10

#define CTR1 PC12
#define CTR2 PC13

//Define IMU pins
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW <---EDIT WITH CORRECT VALUES
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW <---EDIT WITH CORRECT VALUES
#define DECLINATION 13.25 // https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml#declination

//XBEE
#define XBEE_RX D6 //CHANGE! can be any 
#define XBEE_TX D7 //CHANGE!!

//SERVO
#define servoPinL PA10 //CHANGE! can be PA10, PA9, PA0, PA1 top to bottom LR
#define servoPinR PA9 //CHANGE!
#define releasePin PA0 //CHANGE!
#define SENSITIVITY 15 //sensitivity of the controls. ie, if you give the control to move 

//Define SPI slave select pins
#define altimeterChipSelect PA8 // IMPORTANT!!!!! IF THIS IS CHANGED, YOU MUST CHANGE chipSelect IN IntersemaBaro.h
#define thermocoupleChipSelect PC7
#define sdCardChipSelect PA4


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

//COMMUNICATIONS
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
//SoftwareSerial XBee(2, 3); //CHANGE PINS <--- long range: ground to payload
//SoftwareSerial XBee(4, 5); //CHANGE PINS <--- short range: payload to balloon

HardwareSerial XBee(XBEE_RX, XBEE_TX);

#define WIRE_INPUT D7 //CHANGE!

//MOVEMENT
Servo servoRelease;
bool released = false;

//motor
#define motorPinLIn1 3 //CHANGE!
#define motorPinLIn2 4 //CHANGE!

#define motorPinRIn1 5 //CHANGE!
#define motorPinRIn2 6 //CHANGE!

//motor constants
#define gearRatio 488.28125

//PID STUFF
#define OUTPUT_MIN 0 //CHANGE!
#define OUTPUT_MAX 255 //CHANGE!
#define KP .12 //CHANGE!
#define KI .0003 //CHANGE!
#define KD 0 //CHANGE!


uint32_t timer = millis();
