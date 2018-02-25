#include <Servo.h> 
#include <Wire.h>
#include "IntersemaBaro.h"
Intersema::BaroPressure_MS5607B baro(true);

void setup() 
{ 
  Serial.begin(9600);
  baro.init();
} 

void loop() 
{ 
  int32_t altCm = baro.getHeightCentiMeters();
  double altM = baro.getHeightMeters();
  int32_t pressure = baro.getP();
  int32_t temperature = baro.getT();
  Serial.print("Altitude (cm): ");
  Serial.print((altCm));
  Serial.print(", (m): ");
  Serial.println(altM);
  Serial.print("Pressure (Pa): ");
  Serial.println((pressure));
  Serial.print("Temperature (C): ");
  Serial.println((double)(temperature)/100);
  delay(400);
}

/* PROM Coefficients
 *  C1 = 42512 = 0xA610
 *  C2 = 38208 = 0x9540
 *  C3 = 27127 = 0x69F7
 *  C4 = 24461 = 0x5F8D
 *  C5 = 28157 = 0x6DFD
 *  C6 = 32001 = 0x7D01
 */
