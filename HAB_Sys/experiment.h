#include <SPI.h>
#include <SD.h>
#include <Wire.h> // I2C library
#include "Adafruit_MAX31855.h"  // Thermocouple library
#include <RTClib.h>
#include <Stream.h>
#include <Time.h>
#include "IntersemaBaro.h"
#include <Servo.h>
#include "rf69_stac.h"
#include "tracksoar_comm.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

//real time clock
String get_rtc(RTC_DS1307 RTC);

//thermocouple
String get_thermo_data(Adafruit_MAX31855 thermocouple);

//writing data to sd card
void write_to_sd(String data);

//servos
void setup_servos();

void enable_servo(int servo_id);

void disable_servo(int servo_id);

void extend_servo(int servo_id);

void return_servo(int servo_id);

//experiment running
bool should_scream(double alt);

void run_experiment(long launch_st, Intersema::BaroPressure_MS5607B baro, Adafruit_MAX31855 thermocouple, Adafruit_MAX31855 thermocouple_cam, RTC_DS1307 RTC, DallasTemperature system_sensor, DallasTemperature outside_sensor);



