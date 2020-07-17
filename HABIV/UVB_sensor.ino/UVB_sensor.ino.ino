
/* VernierLibTutorialAnalogGraph (v2017)
   This sketch reads a data point from a Vernier Analog (BTA)
   sensor once every half second and graphs the sensor data
   to the Serial Plotter.
   Plug the sensor into the Analog 1 port on the Vernier Arduino
   Interface Shield or into an Analog Protoboard Adapter wired
   to Arduino pin A0. Open the Serial Plotter from the Tools
   menu.
*/
#include <VernierLib.h> //include Vernier functions in this sketch
#include "I2C_Anything.h"
#include <Wire.h>

#define WireSCL 0xA4 //CHANGE!
#define WireSDA 0xA5 //CHANGE!

const byte SLAVE_ADDRESS = 42; //CHANGE, NOT SURE HOW THIS WORKS.

VernierLib Vernier; //create an instance of the VernierLib library
volatile float sensorReading; //create global variable to store sensor reading
// float offset = 12.95;
void setup() {
  Serial.begin(9600); //setup communication to display
  Wire.begin();
  Vernier.autoID(); //identify the sensor being used
}


void loop() {
  sensorReading = Vernier.readSensor(); //read one data value
  Wire.beginTransmission(SLAVE_ADDRESS);
  I2C_writeAnything(sensorReading);
  Wire.endTransmission(SLAVE_ADDRESS);  
  Serial.println(sensorReading*204/1000); //graph data point
  //  Serial.println(0); //optional command to create a filled-in plot
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
//  delay(500); //wait half second
}
