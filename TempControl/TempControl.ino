
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_MAX31855.h"  // Thermocouple library


#include <SPI.h>

// Ambient Temperature Reading
#define SYSTEM_PIN 34  // system ambient temperature pin
#define OUTER_PIN 36  // outside ambient temperature pin


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire system_wire(SYSTEM_PIN);
OneWire outer_wire(OUTER_PIN);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature system_sensor(&system_wire);
DallasTemperature outer_sensor(&outer_wire);


// Arduino Mega SPI Pins
#define MISO 50
#define MOSI 51
#define CLK 52

// ThermoCouple temperature readings for cameras (updated camera thermo couple code)
int cam1_thermoCS = 48;  // Camera 1 Thermo Couple TODO
Adafruit_MAX31855 cam1_thermocouple(CLK, cam1_thermoCS, MISO);  // Initializes the Thermocouple

int cam2_thermoCS = 43;  // Camera 2 Thermo Couple TODO
Adafruit_MAX31855 cam2_thermocouple(CLK, cam2_thermoCS, MISO);  // Initializes the Thermocouple

// Create HeatTape objects and use the HeatTapeMap functions to map from the V -> T w/ PID Control Loop to regulate to specified temperature
// with Observed Input Temperature from ambient temp sensor or thermocouple?


/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Reading from two one wire ambient temperature sensors");

  // Setup Ambient Temp Sensors
  system_sensor.begin();
  outer_sensor.begin();
  

}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  get_ambient_temp(system_sensor,outer_sensor);
}


// Read ambient sensor temperature
String get_ambient_temp(DallasTemperature system_sensor, DallasTemperature outer_sensor) {
  String ambient_temp = "";
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting System temperature...");
  system_sensor.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
 // Serial.print("Temperature for the" + sensor_name +  " sensor (index 0) is: ");
  Serial.println(system_sensor.getTempCByIndex(0));
  ambient_temp += system_sensor.getTempCByIndex(0);

  Serial.print("Requesting outer temperature...");
  outer_sensor.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
 // Serial.print("Temperature for the" + sensor_name +  " sensor (index 0) is: ");
  Serial.println(outer_sensor.getTempCByIndex(0));
  ambient_temp += outer_sensor.getTempCByIndex(0);
  return ambient_temp;
}
