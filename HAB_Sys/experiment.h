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

//real time clock
String get_rtc(RTC_DS1307 RTC);

//thermocouple
String get_thermo_data(Adafruit_MAX31855 thermocouple);

//writing data to sd card
void write_to_sd(String data);

//servos
void setup_servos();

void enable_servos();

void disable_servos();

void extend_servo(int servo_id);

void return_servo(int servo_id);

//experiment running
bool should_scream(double alt);

void run_experiment(long launch_st, Intersema::BaroPressure_MS5607B baro, Adafruit_MAX31855 thermocouple, RTC_DS1307 RTC);



