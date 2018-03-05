#include <SPI.h>

//Define this to the slave select for the tracksoar
#define TRACKSOAR_SS     SS

//args : void
//returns: float represnting queried quantity
float get_alt_fl();

float get_lat_fl();

float get_lon_fl();

float get_speed_fl();

//These functions will return the char array the 
//tracksoar is emitting over APRS
//args: char* buffer : a buffer that will contain 
//                     the chars sent over aprs
//                     for get_lat_char, this must be
//                     atleast 9 chars long, for 
//                     get_lon_char, the buffer must be 
//                     atleast 10 chars long
//returns: void
void get_lat_char(char* buffer);

void get_lon_char(char* buffer);

//This function will return whether the tracksoar
//currently has a lock or not. 
//args: void
//returns: byte: 1 = gps lock; 0 = no gps lock

byte get_gps_lock();

