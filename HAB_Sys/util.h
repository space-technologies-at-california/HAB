
#include <SPI.h>
#include <SD.h>
#include <Wire.h> // I2C library
#include "Adafruit_MAX31855.h"  // Thermocouple library
#include <RTClib.h>
#include <Stream.h>
#include <Time.h>
#include "rf69_stac.h"
#include "tracksoar_comm.h"
#include "IntersemaBaro.h"



void setup_rtc(RTC_DS1307 RTC);

void setup_thermo(Adafruit_MAX31855 thermocouple);

void setup_SD();

void setup_all(Intersema::BaroPressure_MS5607B baro, Adafruit_MAX31855 thermocouple, RTC_DS1307 RTC);


