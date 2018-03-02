// Test code for the SPI interface

#include <SPI.h>

void setup() {
    
    Serial.begin(115200);
    Serial.println("=====Starting=====");

    digitalWrite(SS, HIGH);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);

}

byte transfer(const byte command) {

    byte a = SPI.transfer(command);
    delay(1);
    return a;
}

void loop() {
  byte input[4];
  char gps_aprs_lat[9];
  char gps_aprs_lon[10];
  byte valid;
  digitalWrite(SS,LOW);
  transfer('k');
  valid = transfer('A');
  input[0] = transfer('B');
  input[1] = transfer('C');
  input[2] = transfer('D');
  input[3] = transfer('E');
  float altitude =  *((float*)(&input));
  input[0] = transfer('F');
  input[1] = transfer('G');
  input[2] = transfer('H');
  input[3] = transfer('I');
  float latitude = *((float*)(&input));
  input[0] = transfer('J');
  input[1] = transfer('K');
  input[2] = transfer('L');
  input[3] = transfer('Q');
  float longitude = *((float*)(&input));
  gps_aprs_lat[0] = transfer('R');
  gps_aprs_lat[1] = transfer('S');
  gps_aprs_lat[2] = transfer('T');
  gps_aprs_lat[3] = transfer('U');
  gps_aprs_lat[4] = transfer('V');
  gps_aprs_lat[5] = transfer('W');
  gps_aprs_lat[6] = transfer('X');
  gps_aprs_lat[7] = transfer('Y');
  gps_aprs_lat[8] = transfer('a');
  gps_aprs_lon[0] = transfer('b');
  gps_aprs_lon[1] = transfer('c');
  gps_aprs_lon[2] = transfer('d');
  gps_aprs_lon[3] = transfer('e');
  gps_aprs_lon[4] = transfer('f');
  gps_aprs_lon[5] = transfer('g');
  gps_aprs_lon[6] = transfer('h');
  gps_aprs_lon[7] = transfer('i');
  gps_aprs_lon[8] = transfer('j');
  gps_aprs_lon[9] = transfer('k');
  Serial.print("GPS Valid = ");
  Serial.println(valid);
  Serial.print("Received Altitude From Tracksoar:");
  Serial.println(altitude);
  Serial.print("Received Longitude From Tracksoar:");
  Serial.println(longitude);
  Serial.print("Received Latitude From Tracksoar:");
  Serial.println(latitude);
  Serial.println("APRS Latitude Bytes: ");
  for (int i = 0; i < 9; i++) {
    Serial.print(gps_aprs_lat[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("APRS Longitude Bytes: ");
  for (int i = 0; i < 10; i++) {
    Serial.print(gps_aprs_lon[i]);
    Serial.print(" ");
  }
  Serial.println();
  digitalWrite(SS,HIGH);
  delay(2000);
}

