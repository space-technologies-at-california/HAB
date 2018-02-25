/*

  Completed:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** CS - pin 53


  TODO:
  -Set up Real Time Clock for everything to use.
  -Set up Tracksoar & 2ndary
  -Set up Altimeter
  -Actuation Code w/ conditions
  -Wire diagram


  by Kireet Agrawal - 2018
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

// Arduino Mega SPI Pins
#define MISO 50
#define MOSI 51
#define CLK 52

// Arduino Mega I2C Pins
#define SCL 21
#define SDA 20



RTC_DS1307 RTC; // define the Real Time Clock object

#define DATA_HEADERS "Date, Time, UV, IR, Visible, ThermoCouple Internal Temp (C), ThermoCoupleTemp (C)"
int sd_card_pin = 49;
String delimiter = ",";  // Data string delimiter for SD logging b/w sensors
File sd_card_file;  // filesystem object
String curr_data = "";


Adafruit_SI1145 uv_sensor = Adafruit_SI1145();  // uv sensor object declaration

// Thermo Couple
int thermoCS = 48;
Adafruit_MAX31855 thermocouple(CLK, thermoCS, MISO);  // Initializes the Thermocouple


// Experiment Specific Code
Servo servo1;
Servo servo2;
int servo1_pin = 9;
int servo2_pin = 10;
int servo1_extended = false;
int servo2_extended = false;
time_t start1_time;
time_t start2_time;
bool experiment1_complete = false;
bool experiment2_complete = false;

void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setup_rtc();

  setup_SD();
  setup_UV();
  setup_thermo();
  
  write_to_sd("test.csv", DATA_HEADERS);
  setup_servos();  // Experiment specific linear actuator setup
  setStartTime1();
}

void loop() {
  
  // put your main code here, to run repeatedly:
  // use buffer stream to format line
  // fetch the time
   String curr_time = get_rtc();
   Serial.println(curr_time);
   curr_data += curr_time;
   curr_data += delimiter;

   String uv_data = get_uv_data();
   Serial.println(uv_data);
   curr_data += uv_data;
   curr_data += delimiter;

  String thermo_data = get_thermo_data();
  Serial.println(thermo_data);
  curr_data += thermo_data;
  curr_data += delimiter;

  write_to_sd("test.csv", curr_data);
  curr_data = "";
  

  // Run Experiment Code
  // 90-100K feet altitude
  // Timer 900 seconds 
  return_servo(1);
  // 35-45K feet altitude
  // Timer 900 seconds
  
  

  delay(1500);
}

//int check_experiment(curr_altitude, min_alt, max_alt, start_time, experiment_complete, allowed_time) {
 // if (!experiment_complete) {
 //   if (curr_altitude > min_alt) {
 //     RTC.now();
 //   }
    
 // }
//}

/*
   Experiment's Actuator Specific
*/
void setup_servos() {
  Serial.print("Initializiation Servos...");
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  Serial.println("Servo initialization done");
}
void extend_servo(int servo_id) {
  if (servo_id == 1) {
    if (!servo1_extended) {
      servo1.write(180);
    }
  } else if (servo_id == 2) {
    if (!servo2_extended) {
      servo2.write(165);
    }
  }
}
void return_servo(int servo_id) {
  if (servo_id == 1) {
    if (servo1_extended) {
      servo1.write(45);
    }
  } else if (servo_id == 2) {
    if (servo2_extended) {
      servo2.write(45);
    }
  }
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

void setStartTime1(){
  start1_time = RTC.now().unixtime();
}

bool checkElapse() {
  time_t curr_time = RTC.now().unixtime();
  if(start1_time - curr_time > 5) {
    return true;
  }
  return false;
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
  Serial.println("Initializing Thermo Couple...");
  delay(500);  // wait for MAX thermo chip to stabilize
}
String get_thermo_data() {
  SPI.end();
  String thermo_data = "";
  thermo_data += thermocouple.readInternal();
  thermo_data += delimiter;
  double c = thermocouple.readCelsius();
  if (isnan(c)) {
    Serial.println("Something wrong with thermocouple!");
  } else {
    thermo_data += String(c);
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
    Serial.print("Writing to file ...");
    sd_card_file.println(data);
    // close the file:
    sd_card_file.close();
    Serial.println("done writing to file");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
}

