#include <SPI.h>
#include "tracksoar_comm.h"

byte transfer(const byte command) {
    
    byte a= SPI.transfer(command);
    delayMicroseconds(50);
    return a;

}

float get_alt_fl() {

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    byte input[4];
    digitalWrite(TRACKSOAR_SS, LOW);
    transfer('A');
    input[0] = transfer('B');
    input[1] = transfer('C');
    input[2] = transfer('D');
    input[3] = transfer(0);
    digitalWrite(TRACKSOAR_SS, HIGH);
    SPI.end();
    return *((float *)(&input));

}


float get_lat_fl() {

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    byte input[4];
    digitalWrite(TRACKSOAR_SS, LOW);
    transfer('E');
    input[0] = transfer('F');
    input[1] = transfer('G');
    input[2] = transfer('H');
    input[3] = transfer(0);
    digitalWrite(TRACKSOAR_SS, HIGH);
    SPI.end();
    return *((float *)(&input));

}

float get_lon_fl() {

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    byte input[4];
    digitalWrite(TRACKSOAR_SS, LOW);
    transfer('I');
    input[0] = transfer('J');
    input[1] = transfer('K');
    input[2] = transfer('L');
    input[3] = transfer(0);
    digitalWrite(TRACKSOAR_SS, HIGH);
    SPI.end();
    return *((float *)(&input));

}


float get_speed_fl() {

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    byte input[4];
    digitalWrite(TRACKSOAR_SS, LOW);
    transfer('M');
    input[0] = transfer('N');
    input[1] = transfer('O');
    input[2] = transfer('P');
    input[3] = transfer(0);
    digitalWrite(TRACKSOAR_SS, HIGH);
    SPI.end();
    return *((float *)(&input));

}

void get_lat_char(char* buffer) {

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    digitalWrite(TRACKSOAR_SS, LOW);
    transfer('Q');
    for (byte i = 0; i < 9; i++) {
        buffer[i] = transfer(((byte) 'R') + i);
    }
    digitalWrite(TRACKSOAR_SS, HIGH);
    SPI.end();
}

void get_lon_char(char* buffer) {

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    digitalWrite(TRACKSOAR_SS, LOW);
    transfer('a');
    for (byte i = 0; i < 10; i++) {
        buffer[i] = transfer(((byte) 'b') + i);
    }
    digitalWrite(TRACKSOAR_SS, HIGH);
    SPI.end();
}

byte get_gps_lock() {
    
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    digitalWrite(TRACKSOAR_SS, LOW);
    transfer('k');
    byte to_rtn = transfer(0);
    digitalWrite(TRACKSOAR_SS, HIGH);
    SPI.end();
    return to_rtn;
}
