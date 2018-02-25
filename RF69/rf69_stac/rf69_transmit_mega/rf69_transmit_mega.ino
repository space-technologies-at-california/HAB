#include <SPI.h>
#include "rf69_stac.h"

void setup() 
{
//  pinMode(LED, OUTPUT);
//  Serial.begin(115200);
  transceiver_setup();
}

void loop() {
//  Blink((uint8_t) LED, (uint8_t) 1000, (uint8_t) 5);
//  scream_for_help();

  char scream[20] = "stax";
  scream_for_help_with_message(scream);
}

