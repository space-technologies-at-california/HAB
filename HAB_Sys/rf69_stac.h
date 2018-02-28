#include <RH_RF69.h>

#define RF69_FREQ 434.0

// for mega
#define RFM69_INT     18
#define RFM69_CS      44
#define RFM69_RST     45
#define LED           13

// for uno
//#define RFM69_INT     3
//#define RFM69_CS      4
//#define RFM69_RST     2
//#define LED           5

void transceiver_setup();

void Blink(uint8_t PIN, uint8_t DELAY_MS, uint8_t loops);

void slowBlink(uint8_t PIN, uint8_t loops);

void fastBlink(uint8_t PIN, uint8_t loops);

void manual_reset();

void scream_for_help();

void scream_for_help_with_message(char* msg);
