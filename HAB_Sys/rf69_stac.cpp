#include "rf69_stac.h"

RH_RF69 rf69(RFM69_CS, RFM69_INT);

void transceiver_setup() {
  
  pinMode(LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  
  digitalWrite(RFM69_RST, LOW);

  manual_reset();

  boolean init_flag = rf69.init();
  rf69.setIdleMode(RH_RF69_OPMODE_MODE_SLEEP);

  // initialize the transceiver
  if (!init_flag) {
    Serial.println("RFM69 radio init failed");
    // init failed
//    fastBlink(LED, 5);     // fast blink; 0.6s period; 50% duty cycle; 5 periods
//    while(1) {
//      slowBlink((uint8_t) LED, (uint8_t) 5);
//    }
  } else {
    // init success
    Serial.println("RFM69 radio init SUCCESS");
//    slowBlink((uint8_t) LED, (uint8_t) 2);  // slow blink; 2s period; 50% duty cycle; 2 periods
  }

  // set the frequency
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("RFM69 radio set freq failed");
    // set frequency failed
//    fastBlink(LED, 5);     // fast blink; 0.6s period; 50% duty cycle; 5 periods
//    while(1) {
//      slowBlink((uint8_t) LED, (uint8_t) 5);
//    }
  } else {
    // set frequency success
    Serial.println("RFM69 radio frequency set SUCCESS");
//    slowBlink((uint8_t) LED, (uint8_t) 2);  // slow blink; 2s period; 50% duty cycle; 2 periods
  }

  rf69.setTxPower(20, true);
  uint8_t key[] = { 0x6f, 0x73, 0x6b, 0x69, 0x74, 0x61, 0x6b, 0x65,
                    0x6d, 0x65, 0x68, 0x6f, 0x6d, 0x65, 0x3c, 0x33 };
  rf69.setEncryptionKey(key);

//  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}

void Blink(uint8_t PIN, uint8_t DELAY_MS, uint8_t loops) {
  for (uint8_t i=0; i<loops; i++)  {
    digitalWrite(PIN,HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN,LOW);
    delay(DELAY_MS);
  }
}

void slowBlink(uint8_t PIN, uint8_t loops) {
  Blink(PIN, (uint8_t) 1000, loops);
}

void fastBlink(uint8_t PIN, uint8_t loops) {
  Blink(PIN, (uint8_t) 100, loops);
}

void manual_reset() {
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
}

void scream_for_help() {
//  fastBlink(LED, 2);

  char radiopacket[20] = "Hello World #";

  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();
  delay(3000);
}

void scream_for_help_with_message(char* msg) {
//  fastBlink(LED, 2);
  
  for(int i = 0; i < 4096; i++) {
    rf69.send((uint8_t*)msg, RH_RF69_MAX_MESSAGE_LEN);
    rf69.waitPacketSent();
  }

//  fastBlink(LED, 3);
  
  delay(45000);
}

