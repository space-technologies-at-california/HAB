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
#include <SD.h>
#include <Wire.h> // I2C library
#include "Adafruit_SI1145.h"  // UV sensor library
#include "Adafruit_MAX31855.h"  // Thermocouple library
#include <Servo.h>
#include <RTClib.h>
#include <Stream.h>
#include <Time.h>
#include "IntersemaBaro.h"
#include "rf69_stac.h"
#include "tracksoar_comm.h"


// Arduino Mega SPI Pins
#define MISO 50
#define MOSI 51
#define CLK 52

// Arduino Mega I2C Pins
#define SCL 21
#define SDA 20



RTC_DS1307 RTC; // define the Real Time Clock object

#define DATA_HEADERS "Date, Time, UV, IR, Visible, ThermoCouple Internal Temp (C), ThermoCouple Temp (C), ThermoCouple Temp (F), Altitude (m), Pressure (Pa), Altimeter Temp (C), Altimeter Digital Temp, Altimeter Digital Pressure, Tracksoar Altitude, Tracksoar Latitude, Tracksoar Longitude, Tracksoar Speed, Servo1 Extended, Servo2 Extended"

int sd_card_pin = 47;  // SD card CS pin
String delimiter = ",";  // Data string delimiter for SD logging b/w sensors
File sd_card_file;  // filesystem object
String curr_data = "";
String sd_filename = "HABdata.csv";

Intersema::BaroPressure_MS5607B baro(true);

Adafruit_SI1145 uv_sensor = Adafruit_SI1145();  // uv sensor object declaration

// Thermo Couple
int thermoCS = 48;
Adafruit_MAX31855 thermocouple(CLK, thermoCS, MISO);  // Initializes the Thermocouple

// Conversion constants
double ft_to_m = 0.3048;
// Experiment Specific Code
// 35-45K feet altitude
int servo1_start_alt = 10668;  // 35000 * ft_to_m; // Feet converted to meters
int servo1_end_alt = 13716;  // 45000 * ft_to_m;
// 90-100K feet altitude
int servo2_start_alt = 27432;  // 90000 * ft_to_m;
int servo2_end_alt = 30480;  // 100000 * ft_to_m;

// Globals for servos
Servo servo1;
Servo servo2;
int servo1_pin = 2;
int servo2_pin = 3;
const int servo_enable_pin = 6;
int servo_min = 45; // Value to retract servo
int servo_max = 165; // Value to extend servo
bool servo1_extended = false;
bool servo2_extended = false;
unsigned long exp1_start_time = 0;
unsigned long exp2_start_time = 0;
bool exp1_complete = false;
bool exp2_complete = false;
unsigned long timeout = 900000;  // 900 seconds experiment extended timer

bool exp1_locked = false;
bool exp2_locked = false;
unsigned long exp1_lock_time = 0;
unsigned long exp2_lock_time = 0;
unsigned long exp_lock_timeout = 30000;  // 30 seconds to retract on experiment completion

unsigned long scream_timeout = 14400000;  // 4 hour backup scream timeout
unsigned long launch_start = 0;
unsigned long initial_scream_timeout = 3600000;  // 1 hour initial timeout stop
unsigned long max_scream_alt  = 1000;  // meters


void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  digitalWrite(TRACKSOAR_SS, HIGH);  // Setup SPI tracksoar
  setup_rtc();
  
  setup_SD();
  write_to_sd(sd_filename, DATA_HEADERS);
  setup_UV();
  setup_thermo();
  baro.init();
  transceiver_setup();
  launch_start = millis();  // Initialize for Secondary Transmitter Screaming
  setup_servos();  // Experiment specific linear actuator setup, takes up to 20 seconds
}

void loop() {
  
  // put your main code here, to run repeatedly:
  // fetch the time
   String curr_time = get_rtc();
   Serial.print("Current Time: ");
   Serial.println(curr_time);
   curr_data += curr_time;
   curr_data += delimiter;

   String uv_data = get_uv_data();
   Serial.print("UV Data: ");
   Serial.println(uv_data);
   curr_data += uv_data;
   curr_data += delimiter;

  String thermo_data = get_thermo_data();
  Serial.print("Thermocouple Temp: ");
  Serial.println(thermo_data);
  curr_data += thermo_data;
  curr_data += delimiter;

  double alt = baro.getHeightMeters(2);
  int32_t alt_pressure = baro.getP(2);
  double alt_temp = (double)(baro.getT(2))/100;
  uint32_t raw_alt_temp = baro.getRawT();
  uint32_t raw_alt_press = baro.getRawP();
  Serial.print("Meters: ");
  Serial.print((float)(alt));
  Serial.print(", Feet: ");
  Serial.println((float)(alt) * 3.2808);
  Serial.print("Pressure (Pa): ");
  Serial.println(alt_pressure);
  Serial.print("Altimeter Temp: ");
  Serial.println(alt_temp);
  curr_data += String(alt, 2);
  curr_data += delimiter;
  curr_data += String(alt_pressure);
  curr_data += delimiter;
  curr_data += String(alt_temp);
  curr_data += delimiter;
  curr_data += String(raw_alt_temp);
  curr_data += delimiter;
  curr_data += String(raw_alt_press);
  
  //Tracksoar Code
  Serial.println("Tracksoar Code");
  float tr_alt = get_alt_fl();
  float tr_lat = get_lat_fl();
  float tr_lon = get_lon_fl();
  float tr_spd = get_speed_fl();
//  char lat_arr[10] = "";
//  char lon_arr[10] = "";
//  get_lon_char(lon_arr);
//  get_lat_char(lat_arr);
//  Serial.print("Tracksoar Char Lat: ");
//  Serial.println(lat_arr);
//  Serial.print("Tracksoar Char Lon: ");
//  Serial.println(lon_arr);
  byte gps_lock = get_gps_lock();
  Serial.print("Tracksoar GPS Lock: ");
  Serial.println(gps_lock);
  Serial.print("Tracksoar Altitude: ");
  Serial.println(tr_alt);
  Serial.print("Tracksoar Latitude: ");
  Serial.println(tr_lat);
  Serial.print("Tracksoar Longitude: ");
  Serial.println(tr_lon);
  Serial.print("Tracksoar Speed: ");
  Serial.println(tr_spd);
  curr_data += String(tr_alt);
  curr_data += delimiter;
  curr_data += String(tr_lat);
  curr_data += delimiter;
  curr_data += String(tr_lon);
  curr_data += delimiter;
  curr_data += String(tr_spd);
  curr_data += delimiter;
  
  // Run Experiment Code
  // Starts experiment 1
  if (!exp1_complete && !servo1_extended && alt > servo1_start_alt && alt < servo1_end_alt) {
    enable_servos();
    extend_servo(1);
    exp1_start_time = millis();
    Serial.print("Started Experiment 1 at ");
    Serial.print(alt/ft_to_m);
    Serial.println("ft");
  }
  // Stops experiment 1
  if (!exp1_complete && servo1_extended && !exp1_locked && (alt > servo1_end_alt || time_elapsed(exp1_start_time, timeout)) ) {
    return_servo(1);
    exp1_complete = true;
    exp1_lock_time = millis();
    Serial.print("Experiment 1 Complete at ");
    Serial.print(alt/ft_to_m);
    Serial.println("ft");
  }
  // Sets experiment 1 Lock so we do not continue to send PWM signal in case of stall
  if (!exp1_locked && exp1_complete && time_elapsed(exp1_lock_time, exp_lock_timeout)) {
    disable_servos();
    exp1_locked = true;
    servo1_extended = false;
    Serial.println("Locked Servo 1");
  }

  // Starts experiment 2
  if (!exp2_complete && !servo2_extended && alt > servo2_start_alt && alt < servo2_end_alt) {
    enable_servos();
    extend_servo(2);
    exp2_start_time = millis();
    Serial.print("Started Experiment 2 at ");
    Serial.print(alt/ft_to_m);
    Serial.println("ft");
  }
  // Stops experiment 2
  if (!exp2_complete && servo2_extended && !exp2_locked && (alt > servo2_end_alt || time_elapsed(exp2_start_time, timeout))) {
    return_servo(2);
    exp2_complete = true;
    exp2_lock_time = millis();
    Serial.print("Experiment 2 Complete at ");
    Serial.print(alt/ft_to_m);
    Serial.println("ft");
  }
  // Sets experiment 2 Lock so we do not continue to send PWM sig in case of stall
  if (!exp2_locked && exp2_complete && time_elapsed(exp2_lock_time, exp_lock_timeout)) {
    disable_servos();
    exp2_locked = true;
    servo2_extended = false;
    Serial.println("Locked Servo 2");
  }
  
  curr_data += servo1_extended;
  curr_data += delimiter;
  curr_data += servo2_extended;
  
  write_to_sd(sd_filename, curr_data);
  curr_data = "";

   if(should_scream(alt)){
    Serial.println("Secondary Transmitter Screaming");
    char msg[60];
    String buf;
    buf += F("lat: ");
    buf += String(tr_lat);
    buf += F("\nlon: ");
    buf += String(tr_lon);
    buf += String("\nalt: ");
    buf += String(tr_alt);
    buf += String("\nspd: ");
    buf += String(tr_spd);
    buf.toCharArray(msg, 60);
    scream_for_help_with_message(msg);
  }
  
  delay(1000);
}

bool should_scream(double alt) {
  // alt in meters
  if ((millis() > launch_start + scream_timeout) || ((alt < max_scream_alt) && (millis() > launch_start + initial_scream_timeout)) ) {
    return true;
  }
  return false;
}

/*
   Experiment's Actuator Specific
*/
void setup_servos() {
  Serial.print("Initialization Servos...");
  // Power the servos by pulling the fet's gate high
  pinMode(servo_enable_pin, OUTPUT);
  delay(100);
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  
  enable_servos();
  return_servo(1);
  return_servo(2);
  delay(20000);  // Setup servos to be fully retracted
  disable_servos();
  Serial.println("Servo initialization done");
}

void enable_servos() {
  Serial.println("Enabling Servos");
  digitalWrite(servo_enable_pin, HIGH);
}

void disable_servos() {
  Serial.println("Disabling Servos");
  digitalWrite(servo_enable_pin, LOW);
}

void extend_servo(int servo_id) {
  if (servo_id == 1) {
      servo1.write(servo_max);
      servo1_extended = true;
  } else if (servo_id == 2) {
      servo2.write(servo_max);
      servo2_extended = true;
  }
}

void return_servo(int servo_id) {
  if (servo_id == 1) {
      servo1.write(servo_min);
      servo1_extended = false;
  } else if (servo_id == 2) {
      servo2.write(servo_min);
      servo2_extended = false;
  }
}

bool time_elapsed(unsigned long exp_start, unsigned long time_diff) {
  // Compares milliseconds since startup to milliseconds since startup for experiment start plus time_diff
  if (millis() > exp_start + time_diff) {
    Serial.println("Time elapsed");
    return true;
  }
  return false;
}

/*
   UV sensor Specific
*/
void setup_UV() {
  // Set up UV Sensor (SI1145)
  Serial.print("Initializing UV Sensor...");
  if (! uv_sensor.begin()) {
    Serial.println("Failed: Could not find Si1145 UV sensor");
    return;
  }
  Serial.println("UV Sensor initialization done.");
}
String get_uv_data() {
  String uv_data = "";
  uv_data += String(uv_sensor.readUV());
  uv_data += delimiter;
  uv_data += String(uv_sensor.readIR());
  uv_data += delimiter;
  uv_data += String(uv_sensor.readVisible());
  return uv_data;
}


/*
   RTC (Real Time Clock) Specific
*/
void setup_rtc() {
  // connect to RTC
  Wire.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  if (!RTC.begin()) Serial.println("RTC failed");
}
String get_rtc() {
  DateTime now = RTC.now();
  char buffer[25] = "";
  sprintf(buffer, "%04d/%02d/%02d, %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  return buffer;
}

/*
   Thermo Couple Sensor Setup
*/
void setup_thermo() {
  // Thermo couple is setup when creating the object.
  Serial.print("Initializing Thermo Couple...");
  delay(1000);  // wait for MAX thermo chip to stabilize
  double c = thermocouple.readCelsius();
  if (isnan(c)) {
    Serial.println("Failed to initialize Thermo Couple");
  } else {
    Serial.println("Thermo Couple initialization done.");
  }
}
String get_thermo_data() {
  SPI.end();
  String thermo_data = "";
  thermo_data += thermocouple.readInternal();
  thermo_data += delimiter;
  double c = thermocouple.readCelsius();
  double f = thermocouple.readFarenheit();
  if (isnan(c)) {
    Serial.println("Something wrong with thermocouple!");
    thermo_data += "Failed";
  } else {
    thermo_data += String(c);
  }
  thermo_data += delimiter;
  if (isnan(f)) {
    Serial.println("Something wrong with thermocouple!");
    thermo_data += "Failed";
  } else {
    thermo_data += String(f);
  }
  return thermo_data;
}


/*
   SD Card Specific
*/
void setup_SD() {
  Serial.print("Initializing SD card...");
  if (!SD.begin(sd_card_pin)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");
}
void write_to_sd(String filename, String data) {
  // The following is the code to write to sd card
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  sd_card_file = SD.open(filename, FILE_WRITE);

  // if the file opened, write to it:
  if (sd_card_file) {
//    Serial.print("Writing to file ...");
    sd_card_file.println(data);
    // close the file:
    sd_card_file.close();
//    Serial.println("done writing to file");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
}

