/*
  Completed:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 * -Wire diagram
 *  -Actuation Code w/ conditions
 *  2ndary transmitter w/ conditions
 * -2ndary transmitter on receive side
  
  -Add edge conditions:
    -altimeter = inf

  by Kireet Agrawal - STAC 2018
*/
#include <SPI.h>
//#include <SD.h>
//#include <Wire.h> // I2C library
//#include "Adafruit_SI1145.h"  // UV sensor library
//#include "Adafruit_MAX31855.h"  // Thermocouple library
//#include <RTClib.h>
//#include <Stream.h>
//#include <Time.h>
//#include "IntersemaBaro.h"
//#include <Servo.h>
//#include "rf69_stac.h"
//#include "tracksoar_comm.h"
//#include "util.h"
#include "experiment.h"
//#include "experiment.cpp"


// Arduino Mega SPI Pins
#define MISO 50
#define MOSI 51
#define CLK 52

// Arduino Mega I2C Pins
#define SCL 21
#define SDA 20



//RTC_DS1307 RTC; // define the Real Time Clock object

#define DATA_HEADERS "Date, Time, UV, IR, Visible, ThermoCouple Internal Temp (C), ThermoCouple Temp (C), ThermoCouple Temp (F), Altitude (m), Pressure (Pa), Altimeter Temp (C), Altimeter Digital Temp, Altimeter Digital Pressure, Tracksoar Altitude, Tracksoar Latitude, Tracksoar Longitude, Tracksoar Speed, Servo1 Extended, Servo2 Extended"

//int sd_card_pin = 47;  // SD card CS pin
//String delimiter = ",";  // Data string delimiter for SD logging b/w sensors
//File sd_card_file;  // filesystem object
//String curr_data = "";
String sd_filename = "HABdata.csv";
//
//Intersema::BaroPressure_MS5607B baro(true);
////
//Adafruit_SI1145 uv_sensor = Adafruit_SI1145();  // uv sensor object declaration
//
//// Thermo Couple
//int thermoCS = 48;
//Adafruit_MAX31855 thermocouple(CLK, thermoCS, MISO);  // Initializes the Thermocouple

unsigned long launch_start = 0;



void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  digitalWrite(TRACKSOAR_SS, HIGH);  // Setup SPI tracksoar
  setup_all();
  write_to_sd(sd_filename, DATA_HEADERS);


  launch_start = millis();  // Initialize for Secondary Transmitter Screaming
  setup_servos();  // Experiment specific linear actuator setup, takes up to 20 seconds
}

void loop() {
  run_experiment(launch_start, sd_filename);
}

