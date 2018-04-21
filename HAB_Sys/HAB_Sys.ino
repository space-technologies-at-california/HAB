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
#include "experiment.h"
#include "util.h"


// Arduino Mega SPI Pins
#define MISO 50
#define MOSI 51
#define CLK 52

// Arduino Mega I2C Pins
#define SCL 21
#define SDA 20
#define DATA_HEADERS "Date, Time, UV, IR, Visible, ThermoCouple Internal Temp (C), ThermoCouple Temp (C), ThermoCouple Temp (F), Altitude (m), Pressure (Pa), Altimeter Temp (C), Altimeter Digital Temp, Altimeter Digital Pressure, Tracksoar Altitude, Tracksoar Latitude, Tracksoar Longitude, Tracksoar Speed, Servo1 Extended, Servo2 Extended"

unsigned long launch_start = 0;

Intersema::BaroPressure_MS5607B baro(true);
RTC_DS1307 RTC; // define the Real Time Clock object
int thermoCS = 48;
Adafruit_MAX31855 thermocouple(CLK, thermoCS, MISO);  // Initializes the Thermocouple


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  digitalWrite(TRACKSOAR_SS, HIGH);  // Setup SPI tracksoar
  setup_all(baro, thermocouple, RTC);
  write_to_sd(DATA_HEADERS);
  launch_start = millis();  // Initialize for Secondary Transmitter Screaming
  setup_servos();  // Experiment specific linear actuator setup, takes up to 20 seconds
}

void loop() {
  run_experiment(launch_start, baro, thermocouple, RTC);
}

