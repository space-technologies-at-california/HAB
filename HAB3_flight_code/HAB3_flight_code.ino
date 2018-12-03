#include <IridiumSBD.h>
#include <Adafruit_GPS.h>
#include "IntersemaBaro.h"
#include "Adafruit_MAX31855.h"
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h" 
#include <SD.h>

#define LOG_FILE "datalog.txt"
#define DATA_DELAY_TIME 10000

#define DIAGNOSTICS false // Iridium Diagnostics
#define GPSECHO false     // GPS Diagnostics

//Define serial communication pins
#define IridiumRX D2
#define IridiumTX D10
#define GPSRX D3
#define GPSTX D4

#define IridiumSleep D6

#define CTR1 D5
#define CTR2 A3

//Define SPI slave select pins
#define altimeterChipSelect D7 // IMPORTANT!!!!! IF THIS IS CHANGED, YOU MUST CHANGE chipSelect IN IntersemaBaro.h
#define thermocoupleChipSelect D9
#define sdCardChipSelect D8

// Declare Serial communication
HardwareSerial GPSSerial(GPSRX, GPSTX);
HardwareSerial IridiumSerial(IridiumRX, IridiumTX);

// Declare peripheral objects
IridiumSBD modem(IridiumSerial, IridiumSleep);
Adafruit_GPS GPS(&GPSSerial);
Intersema::BaroPressure_MS5607B baro;
Adafruit_MAX31855 thermocouple(thermocoupleChipSelect);
RTC_PCF8523 rtc;


struct RTCData {
  byte hour, minute, second;
};

struct ThermocoupleData {
  double internal, external, externalFarenheit;
};


struct GPSData {
  bool fix;
  uint8_t fixQuality, satellites;
  float speed, latitude, longitude, altitude, angle;
};

struct AltimeterData {
  double heightMeters1, heightMeters2;
  int32_t pressure1, pressure2, temperature1, temperature2;
};

void setMode(int rf) {
  digitalWrite(CTR1, LOW);
  digitalWrite(CTR2, LOW);

  if (rf == 1) { digitalWrite(CTR1, HIGH); }
  else if (rf == 2) { digitalWrite(CTR2, HIGH); }
  else if (rf == 3) {
    digitalWrite(CTR1, HIGH);
    digitalWrite(CTR2, HIGH);
  }
}

/**
 * Buffers all peripheral data into the given structs.
*/
bool getAllData(GPSData* gpsData, AltimeterData* altimeterData, ThermocoupleData* thermocoupleData, RTCData* rtcData) {
  
  getGPSData(gpsData);
  getAltimeterData(altimeterData);
  getThermocoupleData(thermocoupleData);
  getRTCData(rtcData);

  return true;
}

/**
 * Write all data to the log file on the SD card. Returns false if it could not open the
 * log file.
*/
bool writeAllDataToSDCard(GPSData* gpsData, AltimeterData* altimeterData, ThermocoupleData* thermocoupleData, RTCData* rtcData) {
 
  File dataFile = SD.open(LOG_FILE, FILE_WRITE);

  Serial.println("Opening datalog file for writing");
  if (dataFile) {

    dataFile.print("=======================================================================\n\n");
    dataFile.print(rtcData->hour, DEC); dataFile.print(":");
    dataFile.print(rtcData->minute, DEC); dataFile.print(":");
    dataFile.print(rtcData->second, DEC); dataFile.print("\n");

    dataFile.print("GPS Data || ");
    /*
    struct GPSData {
      bool fix;
      uint8_t fixQuality, satellites;
      float speed, latitude, longitude, altitude, angle;
    }
    */
    dataFile.print("Fix: "); dataFile.print( (int) gpsData->fix, DEC ); dataFile.print(", ");
    dataFile.print("Fix Quality: "); dataFile.print((int) gpsData->fixQuality, DEC); dataFile.print(", ");
    dataFile.print("Speed: "); dataFile.print(gpsData->speed, DEC); dataFile.print(" Knots\n ");
    dataFile.print("Longitude: "); dataFile.print(gpsData->longitude, DEC); dataFile.print(", ");
    dataFile.print("Latitude: "); dataFile.print(gpsData->latitude, DEC); dataFile.print(", ");
    dataFile.print("Altitude: "); dataFile.print(gpsData->altitude, DEC); dataFile.print(", ");
    dataFile.print("Angle: "); dataFile.print(gpsData->angle, DEC); dataFile.print("\n\n");

    dataFile.print("Altimeter Data || ");
    /*
    struct AltimeterData {
      double heightMeters1, heightMeters2;
      int32_t pressure1, pressure2, temperature1, temperature2;
    }
    */
    dataFile.print("Height (1st/2nd): "); dataFile.print(altimeterData->heightMeters1, DEC); 
    dataFile.print(" / "); dataFile.print(altimeterData->heightMeters2, DEC); dataFile.print(" Meters\n ");
    dataFile.print("Pressure (1st/2nd): "); dataFile.print(altimeterData->pressure1, DEC); 
    dataFile.print(" / "); dataFile.print(altimeterData->pressure2, DEC); dataFile.print(" Pa, ");
    dataFile.print("Temperature (1st/2nd): "); dataFile.print(altimeterData->temperature1, DEC); 
    dataFile.print(" / "); dataFile.print(altimeterData->temperature2, DEC); dataFile.print(" C \n\n");

    dataFile.print("Thermocouple Data || ");
    /*
    struct ThermocoupleData {
     double internal, external, externalFarenheit;
    }
    */
    dataFile.print("Internal Temp: "); dataFile.print(thermocoupleData->internal, DEC); dataFile.print(" C, ");
    dataFile.print("External Temp: "); dataFile.print(thermocoupleData->external, DEC); dataFile.print(" C / ");
    dataFile.print(thermocoupleData->externalFarenheit, DEC); dataFile.print(" F \n\n");


    dataFile.close();
    Serial.println("Wrote data to file and closed");


    Serial.print("=======================================================================\n\n");
    Serial.print(rtcData->hour, DEC); dataFile.print(":");
    Serial.print(rtcData->minute, DEC); dataFile.print(":");
    Serial.print(rtcData->second, DEC); dataFile.print("\n");

    Serial.print("GPS Data || ");
    /*
    struct GPSData {
      bool fix;
      uint8_t fixQuality, satellites;
      float speed, latitude, longitude, altitude, angle;
    }
    */
    Serial.print("Fix: "); dataFile.print( (int) gpsData->fix, DEC ); dataFile.print(", ");
    Serial.print("Fix Quality: "); dataFile.print((int) gpsData->fixQuality, DEC); dataFile.print(", ");
    Serial.print("Speed: "); dataFile.print(gpsData->speed, DEC); dataFile.print(" Knots\n ");
    Serial.print("Longitude: "); dataFile.print(gpsData->longitude, DEC); dataFile.print(", ");
    Serial.print("Latitude: "); dataFile.print(gpsData->latitude, DEC); dataFile.print(", ");
    Serial.print("Altitude: "); dataFile.print(gpsData->altitude, DEC); dataFile.print(", ");
    Serial.print("Angle: "); dataFile.print(gpsData->angle, DEC); dataFile.print("\n\n");

    Serial.print("Altimeter Data || ");
    /*
    struct AltimeterData {
      double heightMeters1, heightMeters2;
      int32_t pressure1, pressure2, temperature1, temperature2;
    }
    */
    Serial.print("Height (1st/2nd): "); dataFile.print(altimeterData->heightMeters1, DEC); 
    Serial.print(" / "); dataFile.print(altimeterData->heightMeters2, DEC); dataFile.print(" Meters\n ");
    Serial.print("Pressure (1st/2nd): "); dataFile.print(altimeterData->pressure1, DEC); 
    Serial.print(" / "); dataFile.print(altimeterData->pressure2, DEC); dataFile.print(" Pa, ");
    Serial.print("Temperature (1st/2nd): "); dataFile.print(altimeterData->temperature1, DEC); 
    Serial.print(" / "); dataFile.print(altimeterData->temperature2, DEC); dataFile.print(" C \n\n");

    Serial.print("Thermocouple Data || ");
    /*
    struct ThermocoupleData {
     double internal, external, externalFarenheit;
    }
    */
    Serial.print("Internal Temp: "); dataFile.print(thermocoupleData->internal, DEC); dataFile.print(" C, ");
    Serial.print("External Temp: "); dataFile.print(thermocoupleData->external, DEC); dataFile.print(" C / ");
    Serial.print(thermocoupleData->externalFarenheit, DEC); dataFile.print(" F \n\n");

    Serial.println("Wrote data to file and closed");
  }
  else {
    Serial.println("error opening the file!");
    return false;
  }

  return true;
}

/**
 * Initializes the SD card.
*/
bool startSD() {
  Serial.println("Initializing the SD card");
  if (!SD.begin(sdCardChipSelect)) {
    Serial.println("Card failed, or not present");
    return false;
  }
  Serial.println("card initialized.");
}

/**
 * Gets the hour, minute, and second from the RTC, and places it in the RTCData struct you provide. 
*/
bool getRTCData(RTCData* data) {
  Serial.println("Getting RTC data");
  DateTime now = rtc.now();
  data->hour   = now.hour();
  data->minute = now.minute();
  data->second = now.second();
  return true; 
}

/**
 * Starts up the RTC. Returns false in the event of failure.
*/
bool startRTC() {
  Serial.println("Starting up the RTC");
  if (! rtc.begin()) {
    Serial.println("Failed to begin RTC");
    return false;
  }

  if (! rtc.initialized()) {
    Serial.println("RTC not initialized, setting current time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  return true;
}

/**
 * Get the internal temperature of the thermocouple, along with the external
 * temperature in both celsius and farenheit.
*/
bool getThermocoupleData(ThermocoupleData* data) {
  Serial.println("Getting Thermocouple data");
  
  data->internal = thermocouple.readInternal();
  data->external = thermocouple.readCelsius();
  data->externalFarenheit = thermocouple.readFarenheit();

  //check if the data was read properly :)
  if (isnan(data->internal) || isnan(data->external) || isnan(data->externalFarenheit)) {
    Serial.println("Error reading from the thermocouple");
    return false;
  }
  return true;
}

/**
 * The thermocouple chip just needs some time to start up. Come on, give it a break!
*/
bool startThermocouple() {
  delay(500); // Give the MAX chip time to start up
  return true;
}

/**
 * Gets first and second order height, temperature, and pressure
 * measurements from our altimeter and buffers them into the 
 * AltimeterData struct argument.
 * 
 * TODO: figure out how to return false for error values.
*/
bool getAltimeterData(AltimeterData* data) {
  Serial.println("Getting data from the altimeter");
  
  data->heightMeters1 = baro.getHeightMeters(1);
  data->heightMeters2 = baro.getHeightMeters(2);
  data->temperature1 = baro.getT(1);
  data->temperature2 = baro.getT(2);
  data->pressure1 = baro.getP(1);
  data->pressure2 = baro.getP(2);

  return true;
}

/**
 * Initializes the BaroPressure_MS5607B library that interfaces
 * with our altimeter.
*/
bool startAltimeter() {
  Serial.println("Initializing the Altimeter");
  baro.init();
}

/**
 * Will fill a GPSData struct with the current GPS data,
 * or will return false if a fix is not found on the GPS
 * or if it could not parse the GPS message.
*/
bool getGPSData(GPSData* data) {
  Serial.print("Checking if GPS has data...");
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) { Serial.println(" no data as of yet"); return false; }
  }
  if (!GPS.fix) { Serial.println(" there is no fix"); return false; }

  Serial.println(" it does, reading it now");
  data->fix         =   GPS.fix;
  data->fixQuality  =   GPS.fixquality;
  data->satellites  =   GPS.satellites;
  data->latitude    =   GPS.latitude;
  data->longitude   =   GPS.longitude;
  data->speed       =   GPS.speed;
  data->angle       =   GPS.angle;
  data->altitude    =   GPS.altitude; 

  return true;
}

/**
 * Initializes the GPS chip. Will return false
 * if there was an error, and true otherwise.
 * 
 * TODO: Figure out how to detect an error.
*/
bool startGPS() {
  Serial.println("Starting up the GPS chip");
  
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz
     
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);
  
  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);

  return true;
}


/**
 * This function initializes the RockBLOCK and tests its signal
 * quality. It assumes that `Serial` has been initialized already.
 * 
 * Will return false if initialization of the RockBLOCK was not successful.
*/
bool startRockBlock() {
  int signalQuality = -1;
  int err;
  
  IridiumSerial.begin(19200);

  setMode(3);

  Serial.println("Starting modem...");
  err = modem.begin();
  if (err != ISBD_SUCCESS)
  {
    Serial.print("Begin failed: error ");
    Serial.println(err);
    if (err == ISBD_NO_MODEM_DETECTED)
      Serial.println("No modem detected: check wiring.");
    return false;
  }
  else {
    Serial.println("Modem started successfully");
  }


  err = modem.getSignalQuality(signalQuality);
  if (err != ISBD_SUCCESS)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return false;
  }
  Serial.print("On a scale of 0 to 5, signal quality is currently ");
  Serial.print(signalQuality);
  Serial.println(".");  

  return true;
}

/**
 * Sends data through the RockBLOCK to the location we specified.
 * Usually, only 50 bytes of data should be send in `data` so that
 * only one credit is used during transmission.
 * 
 * When the function is called, the main loop will stall until
 * the RockBLOCK is able to send all the data. During this time,
 * the function `ISBDCallBack` will be called instead of loop.
 */
void rockBlockSendData(const char* data) {
  int err = modem.sendSBDText(data);
  if (err != ISBD_SUCCESS)
  {
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    if (err == ISBD_SENDRECEIVE_TIMEOUT)
      Serial.println("Try again with a better view of the sky.");
  }
  else
  {
    Serial.println("Hey, it worked!");
  }
}

void initializeSPI() {
  Serial.println("Starting up SPI...");
  
  SPI.begin();

  //Set SPI Pins here!

  //Set all chip select pins to high
  pinMode(altimeterChipSelect, OUTPUT);
  digitalWrite(altimeterChipSelect, HIGH);
  pinMode(thermocoupleChipSelect, OUTPUT);
  digitalWrite(thermocoupleChipSelect, HIGH);
  pinMode(sdCardChipSelect, OUTPUT);
  digitalWrite(sdCardChipSelect, HIGH);

  Serial.println("Success");
}

/**
 * This function will run on a loop when the RockBLOCK is attempting 
 * to send data. We just collect data and then write it to the data log.
*/
bool ISBDCallback()
{
  GPSData gpsData;
  AltimeterData altimeterData;
  ThermocoupleData thermocoupleData;
  RTCData rtcData;

  getAllData(&gpsData, &altimeterData, &thermocoupleData, &rtcData);  
  writeAllDataToSDCard(&gpsData, &altimeterData, &thermocoupleData, &rtcData);

  delay(DATA_DELAY_TIME);
  
  return true;
}

#if DIAGNOSTICS
void ISBDConsoleCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}

void ISBDDiagsCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}
#endif

void setup()
{
  Serial.begin(115200);
  
  initializeSPI();

  Serial.println("About to start GPS");
  startGPS();

  Serial.println("About to start Altimeter");
  startAltimeter();

  Serial.println("About to start Thermocouple");
  startThermocouple();

  Serial.println("About to start RTC");
  startRTC();

  Serial.println("About to start SD");
  startSD();

  Serial.println("About to start RockBLOCK");
  startRockBlock();
  
}

int rockBlockSendTime = 0;
int rockBlockSendRate = 60000;

void loop()
{
  GPSData gpsData;
  AltimeterData altimeterData;
  ThermocoupleData thermocoupleData;
  RTCData rtcData;

  getAllData(&gpsData, &altimeterData, &thermocoupleData, &rtcData);  
  writeAllDataToSDCard(&gpsData, &altimeterData, &thermocoupleData, &rtcData);

  //Should we send data to ground?
  if (millis() > rockBlockSendTime) {
    
    /* The data will be written to a dataString in this format:
    <Hour>:<Minute>:<FixQuality>:<Speed>:<Angle>:<Lon>:<Lat>:<Altitude>:<ExternalTemp>
    */

    Serial.println("It's time to send a message from the rockblock");
    
    String hour = String((int) rtcData.hour, DEC);
    String minute = String((int) rtcData.minute, DEC);
    String fixQuality = String((int) gpsData.fixQuality, DEC);
    String speed = String(gpsData.speed, 2);
    String angle = String(gpsData.angle, 2);
    String lon = String(gpsData.longitude, 6);
    String lat = String(gpsData.latitude, 6);
    String altitude = String((int) altimeterData.heightMeters1, DEC);
    String externalTemp = String((int) thermocoupleData.externalFarenheit, DEC);

    String dataString = hour;
    dataString.concat(':'); dataString.concat(minute);
    dataString.concat(':'); dataString.concat(fixQuality);
    dataString.concat(':'); dataString.concat(speed);
    dataString.concat(':'); dataString.concat(angle);
    dataString.concat(':'); dataString.concat(lon);
    dataString.concat(':'); dataString.concat(lat);
    dataString.concat(':'); dataString.concat(altitude);
    dataString.concat(':'); dataString.concat(externalTemp);

    rockBlockSendData(dataString.c_str()); // Send the string data to the rock block

    rockBlockSendTime = millis() + rockBlockSendRate; // Only send data through rock block once every minute.
  }

  delay(DATA_DELAY_TIME);

}
