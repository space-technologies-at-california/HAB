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
  double altM1 = baro.getHeightMeters(1);
  int32_t pressure1 = baro.getP(1);
  int32_t temperature1 = baro.getT(1);
  
  double altM2 = baro.getHeightMeters(2);
  int32_t pressure2 = baro.getP(2);
  int32_t temperature2 = baro.getT(2);
  
  Serial.println("\n1st Order Algorithm Values...");
  Serial.print("Altitude (m): ");
  Serial.println(altM1);
  Serial.print("Pressure (Pa): ");
  Serial.println((pressure1));
  Serial.print("Temperature (C): ");
  Serial.println((double)(temperature1)/100);

  Serial.println("2nd Order Algorithm Values...");
  Serial.print("Altitude (m): ");
  Serial.println(altM2);
  Serial.print("Pressure (Pa): ");
  Serial.println((pressure2));
  Serial.print("Temperature (C): ");
  Serial.println((double)(temperature2)/100);
  delay(1000);
}

/* PROM Coefficients
 *  C1 = 42512 = 0xA610
 *  C2 = 38208 = 0x9540
 *  C3 = 27127 = 0x69F7
 *  C4 = 24461 = 0x5F8D
 *  C5 = 28157 = 0x6DFD
 *  C6 = 32001 = 0x7D01
 */
