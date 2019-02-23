#include <WiFi.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>

/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

// Mpide 22 fails to compile Arduino code because it stupidly defines ARDUINO 
// as an empty macro (hence the +0 hack). UNO32 builds are fine. Just use the
// real Arduino IDE for Arduino builds. Optionally complain to the Mpide
// authors to fix the broken macro.
#if (ARDUINO + 0) == 0
#error "Oops! We need the real Arduino IDE (version 22 or 23) for Arduino builds."
#error "See trackuino.pde for details on this"

// Refuse to compile on arduino version 21 or lower. 22 includes an 
// optimization of the USART code that is critical for real-time operation
// of the AVR code.
#elif (ARDUINO + 0) < 22
#error "Oops! We need Arduino 22 or 23"
#error "See trackuino.pde for details on this"

#endif

// Trackuino custom libs
#include "config.h"
#include "afsk_avr.h"
#include "afsk_pic32.h"
#include "aprs.h"
#include "buzzer.h"
#include "gps.h"
#include "pin.h"
#include "power.h"
#include "sensors_avr.h"
#include "sensors_pic32.h"
#ifdef __AVR__
#include <avr/wdt.h>
#endif
// Arduino/AVR libs
#if (ARDUINO + 1) >= 100
#  include <Arduino.h>
#else
#  include <WProgram.h>
#endif
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
// Module constants
static const uint32_t VALID_POS_TIMEOUT = 2000;  // ms

// Though not used here, we need to include Wire.h in this file for other code:
#include <Wire.h>
// Same is true for SPI.h
//#include <SPI.h>

// Module variables
static int32_t next_aprs = 0;

//Variables for the SPI interface
static volatile float gps_altitude_spi = 0.0;
static volatile float gps_lat_spi = 0.0;
static volatile float gps_lon_spi = 0.0;
static volatile float gps_speed_spi = 0.0;
static volatile char gps_aprs_lon_spi[10];
static volatile char gps_aprs_lat_spi[9];
static volatile byte gps_lock_spi;

//SPI interface slave select falling interrupt
void spi_ss_falling() {

}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pin_write(LED_PIN, LOW);
  watchdogSetup();
// deactivate internal pull-ups for twi
    // as per note from atmega8 manual pg167
    cbi(PORTC, 4);
    cbi(PORTC, 5);

  Serial.begin(GPS_BAUDRATE);
#ifdef DEBUG_RESET
  Serial.println("RESET");
#endif

  //SPI Setup code written by Avi 
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  digitalWrite(MISO, HIGH);
  //Set Slave mode bit in SPI control register SPCR
  SPCR |= _BV(SPE);
  //Enable the slave interrupts 
  SPCR |= _BV(SPIE);
  
  buzzer_setup();
  afsk_setup();
  gps_setup();
  sensors_setup();

#ifdef DEBUG_SENS
  Serial.print("Ti=");
  Serial.print(sensors_int_lm60());
  Serial.print(", Te=");
  Serial.print(sensors_ext_lm60());
  Serial.print(", Vin=");
  Serial.println(sensors_vin());
#endif
  // Do not start until we get a valid time reference
  // for slotted transmissions.
  if (APRS_SLOT >= 0) {
    do {
      while (! Serial.available())
        power_save();
    } while (! gps_decode(Serial.read()));
    
    next_aprs = millis() + 1000 *
      (APRS_PERIOD - (gps_seconds + APRS_PERIOD - APRS_SLOT) % APRS_PERIOD);
  }
  else {
    next_aprs = millis();
  }  
  // TODO: beep while we get a fix, maybe indicating the number of
  // visible satellites by a series of short beeps?
}

void get_pos()
{
  // Get a valid position from the GPS
  int valid_pos = 0;
  uint32_t timeout = millis();
  do {
    if (Serial.available())
      valid_pos = gps_decode(Serial.read());
  } while ( (millis() - timeout < VALID_POS_TIMEOUT) && ! valid_pos) ;

  if (valid_pos) {
    gps_lock_spi = 1;
    if (gps_altitude > BUZZER_ALTITUDE) {
      buzzer_off();   // In space, no one can hear you buzz
    } else {
      buzzer_on();
    }
    gps_altitude_spi = gps_altitude;
    gps_lat_spi = gps_lat;
    gps_lon_spi = gps_lon;
    gps_speed_spi = gps_speed;
    for (int i = 0; i < 10; i++) {
      gps_aprs_lon_spi[i] = gps_aprs_lon[i];
    }
    for (int i = 0; i < 9; i++) {
      gps_aprs_lat_spi[i] = gps_aprs_lat[i];
    }
  } else {
    gps_lock_spi = 0;
  }
}

void loop()
{
  // Time for another APRS frame
  wdt_reset();
  if ((int32_t) (millis() - next_aprs) >= 0) {
    get_pos();
    aprs_send();
    wdt_reset();
    next_aprs += APRS_PERIOD * 1000L;
    while (afsk_flush()) {
      power_save();
      wdt_reset();
    }

#ifdef DEBUG_MODEM
    // Show modem ISR stats from the previous transmission
    afsk_debug();
#endif
  }

  power_save(); // Incoming GPS data or interrupts will wake us up
}

void watchdogSetup(void)
{
 cli();
 wdt_reset();
/*
 WDTCSR configuration:
 WDIE = 1: Interrupt Enable
 WDE = 1 :Reset Enable
 See table for time-out variations:
 WDP3 = 0 :For 1000ms Time-out
 WDP2 = 1 :For 1000ms Time-out
 WDP1 = 1 :For 1000ms Time-out
 WDP0 = 0 :For 1000ms Time-out
*/
// Enter Watchdog Configuration mode:
WDTCSR |= (1<<WDCE) | (1<<WDE);
// Set Watchdog settings:
 WDTCSR = (0<<WDIE) | (1<<WDE) |
(1<<WDP3) | (0<<WDP2) | (0<<WDP1) |
(1<<WDP0);
Serial.println("WDT reset");
sei();
}

//This is the Interrupt Service Routine that 
//handles SPI communication, it's rased everytime
//a byte is in the SPI Data Register (SPDR)
//Protocol:
//Upon bringing SS low, the master sends a command byte
//Commands     Function                     GPS Var Name
//  A-D:    Access the altitude bytes 1-4  (gps_altitude)
//  E-H:    Acesss the Latitude byte 1-4   (gps_lat)
//  I-L:    Access the Longitude byte 1-4  (gps_lon)
//  M-P:    Access the Speed byte 1-4      (gps_speed)
//  Q-Y:    Access gps_aprs_lat chars      (gps_aprs_lat)
//  a-k:    Access gps_aprs_lon chars      (gps_aprs_lat)

//Helper Function for the ISR
byte get_byte_from_float(float a, byte loc){
    char* ptr = (char*)&a;
    return *(ptr + loc);
}

ISR (SPI_STC_vect)
{
  byte input = SPDR;
  //Serial.print("Incoming Serial Input :");
  //Serial.println(input);
  
  switch (input)
  {
    case 'A': SPDR = get_byte_from_float(gps_altitude_spi, 0); break;
    case 'B': SPDR = get_byte_from_float(gps_altitude_spi, 1); break;
    case 'C': SPDR = get_byte_from_float(gps_altitude_spi, 2); break;
    case 'D': SPDR = get_byte_from_float(gps_altitude_spi, 3); break;
    case 'E': SPDR = get_byte_from_float(gps_lat_spi, 0); break;
    case 'F': SPDR = get_byte_from_float(gps_lat_spi, 1); break;
    case 'G': SPDR = get_byte_from_float(gps_lat_spi, 2); break;
    case 'H': SPDR = get_byte_from_float(gps_lat_spi, 3); break;
    case 'I': SPDR = get_byte_from_float(gps_lon_spi, 0); break;
    case 'J': SPDR = get_byte_from_float(gps_lon_spi, 1); break;
    case 'K': SPDR = get_byte_from_float(gps_lon_spi, 2); break;
    case 'L': SPDR = get_byte_from_float(gps_lon_spi, 3); break;
    case 'M': SPDR = get_byte_from_float(gps_speed_spi, 0); break;
    case 'N': SPDR = get_byte_from_float(gps_speed_spi, 1); break;
    case 'O': SPDR = get_byte_from_float(gps_speed_spi, 2); break;
    case 'P': SPDR = get_byte_from_float(gps_speed_spi, 3); break;
    case 'Q': SPDR = gps_aprs_lat_spi[0]; break;
    case 'R': SPDR = gps_aprs_lat_spi[1]; break;
    case 'S': SPDR = gps_aprs_lat_spi[2]; break;
    case 'T': SPDR = gps_aprs_lat_spi[3]; break;
    case 'U': SPDR = gps_aprs_lat_spi[4]; break;
    case 'V': SPDR = gps_aprs_lat_spi[5]; break;
    case 'W': SPDR = gps_aprs_lat_spi[6]; break;
    case 'X': SPDR = gps_aprs_lat_spi[7]; break;
    case 'Y': SPDR = gps_aprs_lat_spi[8]; break;
    case 'a': SPDR = gps_aprs_lon_spi[0]; break;
    case 'b': SPDR = gps_aprs_lon_spi[1]; break;
    case 'c': SPDR = gps_aprs_lon_spi[2]; break;
    case 'd': SPDR = gps_aprs_lon_spi[3]; break;
    case 'e': SPDR = gps_aprs_lon_spi[4]; break;
    case 'f': SPDR = gps_aprs_lon_spi[5]; break;
    case 'g': SPDR = gps_aprs_lon_spi[6]; break;
    case 'h': SPDR = gps_aprs_lon_spi[7]; break;
    case 'i': SPDR = gps_aprs_lon_spi[8]; break;
    case 'j': SPDR = gps_aprs_lon_spi[9]; break;
    case 'k': SPDR = gps_lock_spi; break;
    default : SPDR = 0x02; break;
  }
}
  


    
  
