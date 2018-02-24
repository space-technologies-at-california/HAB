/*

  Completed:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** CS - pin 53
 * 

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

// Arduino Mega SPI Pins
#define MISO 50
#define MOSI 51
#define CLK 52

// Arduino Mega I2C Pins
#define SCL 21
#define SDA 20


File sd_card_file; // SD card file
int sd_card_pin = 53;
String curr_data = "";
String delimiter = "/~/";  // Data string delimiter for SD logging b/w sensors
String line_delimiter = "\\\r";  // Newline delimiter for SD logging

Adafruit_SI1145 uv_sensor = Adafruit_SI1145();  // uv sensor object declaration

Servo servo1;
Servo servo2;
int servo1_pin = 9;
int servo2_pin = 10;
int servo1_extended = false;
int servo2_extended = false;

// Thermo Couple
int thermoCS = 48;
Adafruit_MAX31855 thermocouple(CLK, thermoCS, MISO);  // Initializes the Thermocouple



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setup_SD();
  setup_UV();
  setup_thermo();
  
  setup_servos();  // Experiment specific linear actuator setup
  
}

void loop() {
  // put your main code here, to run repeatedly:
  String uv_data = get_uv_data();
  Serial.println(uv_data);
  curr_data += uv_data;
  curr_data += delimiter;

  String thermo_data = get_thermo_data();
  Serial.println(thermo_data);
  curr_data += thermo_data;
  curr_data += delimiter;

  curr_data += line_delimiter;
  write_to_sd("test.txt", curr_data);

  
  // 90-100K feet altitude
  // Timer 900 seconds

  // 35-45K feet altitude
  // Timer 900 seconds

  curr_data = "";
  delay(1000);
}


/*
 * UV sensor Specific
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
 * Thermo Couple Sensor Setup
 */
void setup_thermo() {
  // Thermo couple is setup when creating the object.
  Serial.println("Initializing Thermo Couple...");
  delay(500);  // wait for MAX thermo chip to stabilize
}
String get_thermo_data() {
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
 * SD Card Specific
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

/*
 * Experiment's Actuator Specific
 */
void setup_servos() {
  Serial.print("Initializiation Servos...");
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  Serial.println("Servo initialization done");
}
void extend_servo(int servo_id) {
  if (servo_id == 1) {
    servo1.write(165);
  } elif (servo_id == 2) {
    servo2.write(165);
  }
}
void return_servo(int servo_id) {
  if (servo_id == 1) {
    servo1.write(45);
  } elif (servo_id == 2) {
    servo2.write(45);
  }
}


