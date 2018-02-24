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
 -Set up Tracksoar
 -Set up Altimeter
 -Actuation Code w/ conditions
 -Wire diagram


  by Kireet Agrawal - 2018
*/

#include <SPI.h>
#include <SD.h>
#include <Wire.h> // I2C library
#include "Adafruit_SI1145.h"  // UV sensor library
#include <Servo.h>


File sd_card_file; // SD card file
Adafruit_SI1145 uv_sensor = Adafruit_SI1145();  // uv sensor object declaration

Servo servo1;
Servo servo2;
int servo1extended = false;
int servo2extended = false;
int servo1locked = false;
int servo2locked = false;

String delimiter = ",";  // Data string delimiter for SD logging 


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Set up SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(53)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");

  // Set up UV Sensor (SI1145)
  Serial.print("Initializing UV Sensor...");
  if (! uv_sensor.begin()) {
    Serial.println("Failed: Could not find Si1145 UV sensor");
    return;
  }
  Serial.println("UV Sensor initialization done.");

  Serial.print("Initializiation Servos...");
  servo1.attach(9);
  servo2.attach(10);
  Serial.println("Servo initialization done");

}

void loop() {
  // put your main code here, to run repeatedly:
  String uv_data = get_uv_data();
  Serial.println(uv_data);
  write_to_sd("test.txt", uv_data);
  delay(1000);
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

void write_to_sd(String filename, String data) {
  // The following is the code to write to sd card
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  sd_card_file = SD.open(filename, FILE_WRITE);

  // if the file opened okay, write to it:
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

void run_servo1() {
  Serial.println("Here");
  
  
  delay(15000);
  uv_data = get_uv_data();
  Serial.println(uv_data);
  write_to_sd("test.txt", uv_data);
  delay(1000);
  delay(15000);
  Serial.println("Now Here");
  
}

void extend_servo1() {
  servo1.write(165);
}

void lock_servo1() {
// 35-45K feet altitude
// Timer 900 seconds
  servo1.write(0);
}

void return_servo1() {
  servo1.write(45);
}

void extend_servo2() {
  servo2.write(165);
}

void lock_servo2() {
// 90-100K feet altitude
// Timer 900 seconds
  servo2.write(0);
}

void return_servo2() {
  servo2.write(45);
}


