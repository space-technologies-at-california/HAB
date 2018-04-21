#include <SD.h>
#include <Wire.h> // I2C library
#include "Adafruit_SI1145.h"  // UV sensor library
#include "Adafruit_MAX31855.h"  // Thermocouple library
#include <RTClib.h>
#include <Stream.h>
#include <Time.h>
#include "IntersemaBaro.h"
#include <Servo.h>
#include "rf69_stac.h"
#include "tracksoar_comm.h"
//#include "util.h"
//#include "experiment.h"


// Arduino Mega SPI Pins
#define MISO 50
#define MOSI 51
#define CLK 52

// Arduino Mega I2C Pins
#define SCL 21
#define SDA 20

//servos
void setup_servos();

void enable_servos();

void disable_servos();

void extend_servo(int servo_id);

void return_servo(int servo_id);

//uv
String get_uv_data();

//real time clock
//String get_rtc;

//thermocouple
String get_thermo_data();

//writing data to sd card
void write_to_sd(String filename, String data);

bool should_scream(double alt);

void run_experiment(long launch_st, String sd_filename);

void setup_UV();

void setup_rtc();

void setup_thermo();

void setup_SD();

void setup_all();


