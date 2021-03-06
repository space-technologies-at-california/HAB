
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
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!


void setup_rtc(RTC_DS1307 RTC);

void setup_thermo(Adafruit_MAX31855 thermocouple);

void setup_SD();

void setup_all(Intersema::BaroPressure_MS5607B baro, Adafruit_MAX31855 thermocouple, Adafruit_MAX31855 thermocouple_cam, RTC_DS1307 RTC, DallasTemperature system_sensor, DallasTemperature outside_sensor, Adafruit_LSM9DS0 lsm);


