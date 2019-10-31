/**
 * HAB4 flight code.
 * 
 * Includes functions for recieving data,
 * writing it to the SD card,
 * and the main control loop.
 * 
 * Originally based from the HAB3 flight code.
 * 
 * 
 * BOARD: GENERIC STM32F4 SERIES
 * BLACK F407VE
 * 
 */
#include <IridiumSBD.h>
#include <Adafruit_GPS.h>
#include "IntersemaBaro.h"
#include "Adafruit_MAX31855.h"
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h" 
#include <SD.h>
#include <Servo.h> 

#include <SparkFunLSM9DS1.h> //IMU library


#define LOG_FILE "datalog.txt"
#define DATA_DELAY_TIME 10000

#define DIAGNOSTICS false // Iridium Diagnostics
#define GPSECHO false     // GPS Diagnostics

//Define serial communication pins
#define IridiumRX PA12
#define IridiumTX PA11
#define GPSRX D2
#define GPSTX D10 
#include "SoftwareSerial.h" //FOR XBEE

#define IridiumSleep D6

#define CTR1 D3
#define CTR2 D4

//Define IMU pins
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW <---EDIT WITH CORRECT VALUES
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW <---EDIT WITH CORRECT VALUES
#define DECLINATION 13.25 // https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml#declination

//SERVO
#define servoPinL 8 //CHANGE!
#define servoPinR 9 //CHANGE!
#define SENSITIVITY 15 //sensitivity of the controls. ie, if you give the control to move 




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

//Declare IMU
LSM9DS1 imu;

//XBEE COMMUNICATION
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3); //CHANGE PINS <--- long range: ground to payload
//SoftwareSerial XBee(4, 5); //CHANGE PINS <--- short range: payload to balloon

//SERVO
Servo servoL;
Servo servoR;
int angleR = 0; //global variable for what the right servo's angle is
int angleL = 0; //global variable for what the left servo's angle is


/**
 * 
 * DATA STRUCTURES
 * 
 */

 /**
  * Structure for RTC data
  */
struct RTCData {
  byte hour, minute, second;
};

 /**
  * Structure for ThermocoupleData data
  */
struct ThermocoupleData {
  double internal, external, externalFarenheit;
};

/**
 * Structure for holding GPS data
 */
struct GPSData {
  bool fix;
  uint8_t fixQuality, satellites;
  float speed, latitude, longitude, altitude, angle;
};

/**
 * Structure for holding Altimeter data
 */
struct AltimeterData {
  double heightMeters1, heightMeters2;
  int32_t pressure1, pressure2, temperature1, temperature2;
};

/**
 * Structure for holding IMU data
 */
struct IMUData {
  float gx, gy, gz, ax, ay, az, mx, my, mz;
};

/**
 * sets the CTR1, CTR2 pins depending on which
 * reciever rf chosen.
 */
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
bool getAllData(GPSData* gpsData, AltimeterData* altimeterData, ThermocoupleData* thermocoupleData, RTCData* rtcData, IMUData* imuData) {
  
  getGPSData(gpsData);
  getAltimeterData(altimeterData);
  getThermocoupleData(thermocoupleData);
  getRTCData(rtcData);
  getIMUData(imuData, true); //True for DPS values

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
    dataFile.print("Fix: "); dataFile.print( (int) gpsData->fix, DEC ); dataFile.print(", ");
    dataFile.print("Fix Quality: "); dataFile.print((int) gpsData->fixQuality, DEC); dataFile.print(", ");
    dataFile.print("Speed: "); dataFile.print(gpsData->speed, DEC); dataFile.print(" Knots\n ");
    dataFile.print("Longitude: "); dataFile.print(gpsData->longitude, DEC); dataFile.print(", ");
    dataFile.print("Latitude: "); dataFile.print(gpsData->latitude, DEC); dataFile.print(", ");
    dataFile.print("Altitude: "); dataFile.print(gpsData->altitude, DEC); dataFile.print(", ");
    dataFile.print("Angle: "); dataFile.print(gpsData->angle, DEC); dataFile.print("\n\n");

    dataFile.print("Altimeter Data || ");
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

  }
  else {
    Serial.println("error opening the file!");
  }

  Serial.print("=======================================================================\n\n");
    Serial.print("Timestamp: "); Serial.print(rtcData->hour, DEC); Serial.print(":");
    Serial.print(rtcData->minute, DEC); Serial.print(":");
    Serial.print(rtcData->second, DEC); Serial.print("\n\n");

    Serial.print("GPS Data || ");
    /*
    struct GPSData {
      bool fix;
      uint8_t fixQuality, satellites;
      float speed, latitude, longitude, altitude, angle;
    }
    */
    //prints all GPSData info.
    Serial.print("Fix: "); Serial.print( (int) gpsData->fix, DEC ); Serial.print(", ");
    Serial.print("Fix Quality: "); Serial.print((int) gpsData->fixQuality, DEC); Serial.print(", ");
    Serial.print("Speed: "); Serial.print(gpsData->speed, DEC); Serial.print(" Knots\n");
    Serial.print("Longitude: "); Serial.print(gpsData->longitude, DEC); Serial.print(", ");
    Serial.print("Latitude: "); Serial.print(gpsData->latitude, DEC); Serial.print(", ");
    Serial.print("Altitude: "); Serial.print(gpsData->altitude, DEC); Serial.print(", ");
    Serial.print("Angle: "); Serial.print(gpsData->angle, DEC); Serial.print("\n\n");

    Serial.print("Altimeter Data || ");
    /*
    struct AltimeterData {
      double heightMeters1, heightMeters2;
      int32_t pressure1, pressure2, temperature1, temperature2;
    }
    */
    Serial.print("Height (1st/2nd): "); Serial.print(altimeterData->heightMeters1, DEC); 
    Serial.print(" / "); Serial.print(altimeterData->heightMeters2, DEC); Serial.print(" Meters\n");
    Serial.print("Pressure (1st/2nd): "); Serial.print(altimeterData->pressure1, DEC); 
    Serial.print(" / "); Serial.print(altimeterData->pressure2, DEC); Serial.print(" Pa, ");
    Serial.print("Temperature (1st/2nd): "); Serial.print(altimeterData->temperature1, DEC); 
    Serial.print(" / "); Serial.print(altimeterData->temperature2, DEC); Serial.print(" C \n\n");

    Serial.print("Thermocouple Data || ");
    /*
    struct ThermocoupleData {
     double internal, external, externalFarenheit;
    }
    */
    Serial.print("Internal Temp: "); Serial.print(thermocoupleData->internal, DEC); Serial.print(" C, ");
    Serial.print("External Temp: "); Serial.print(thermocoupleData->external, DEC); Serial.print(" C / ");
    Serial.print(thermocoupleData->externalFarenheit, DEC); Serial.print(" F \n\n");

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
  return true;
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
 *  Gets the IMU data
 *  Takes in RTCData pointer and bool:
 * TRUE: adc output
 * FALSE: dps output
 */
bool getIMUData(IMUData* data, bool adcdps) {
  Serial.println("Getting IMU data");
  imu.readGyro();
  imu.readGyro();
  imu.readGyro();
  #ifdef adcdps
    data->gx = imu.gx;
    data->gy = imu.gy;
    data->gz = imu.gz;
    data->ax = imu.ax;
    data->ay = imu.ay;
    data->az = imu.az;
    data->mx = imu.mx;
    data->my = imu.my;
    data->mz = imu.mz;
  #else
    data->gx = imu.calcGyro(imu.gx);  //in Deg per S
    data->gy = imu.calcGyro(imu.gy);
    data->gz = imu.calcGyro(imu.gz);
    data->ax = imu.calcAccel(imu.ax); //in g's
    data->ay = imu.calcAccel(imu.ay);
    data->az = imu.calcAccel(imu.az);
    data->mx = imu.calcMag(imu.mx);   //in Gauss
    data->my = imu.calcMag(imu.my);
    data->mz = imu.calcMag(imu.mz);
  #endif
  return true;
}

/**
 * Gets data from the balloon Flora:
 * 
 * 
 */
bool getBalloonData(IMUData* data) {
  return true;
}


/**
 * Gets the data from the Xbee and converts it to something controllable
 * 
 */

int getXBeeControl() {
  byte input = XBee.read(); 
  
  //input should be a delta: [_ _ _ _] [_ _ _ _] <- 8 bits
  // the first 4 bits determine the delta for the left bit, the last 
  int dL = input >> 4; //getting last 4 bits
  int dR = input & 15; //getting first 4 bits

  // converting dL to be either positive or negative.

  if (dL > 7) {
    angleL += (dL - 8) * SENSITIVITY;
  } else {
    angleL -= dL * SENSITIVITY;
  }

  if (dR > 7) {
    angleR += (dR - 8) * SENSITIVITY;
  } else {
    angleR -= dR * SENSITIVITY;
  }
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
  return true;
}

uint32_t timer = millis();

/**
 * Will fill a GPSData struct with the current GPS data,
 * or will return false if a fix is not found on the GPS
 * or if it could not parse the GPS message.
*/
bool getGPSData(GPSData* data) {
  char c = GPS.read();
  Serial.print("Checking if GPS has data...");
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) { Serial.println(" no data as of yet"); return false; }
  }
  if (timer > millis()) timer = millis();
     
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
  if (GPS.fix) {  

    //Serial.println(" it does, reading it now");
    data->fix         =   (int)GPS.fix;
    data->fixQuality  =   GPS.fixquality;
    data->satellites  =   GPS.satellites;
    data->latitude    =   GPS.latitude;
    data->longitude   =   GPS.longitude;
    data->speed       =   GPS.speed;
    data->angle       =   GPS.angle;
    data->altitude    =   GPS.altitude; 
  }
  else {
    Serial.println(" there is no fix"); return false;
  }
  }
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
    Serial.print("Begin failed: error =========================================================== ");
    Serial.println(err);
    if (err == ISBD_NO_MODEM_DETECTED)
      Serial.println("No modem detected: check wiring=============================================.");
    return false;
  }
  else {
    Serial.println("Modem started successfully=======================================================================================");
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

  int quality1 = -1;
  int quality2 = -1;
  int quality3 = -1;

  Serial.println("Determining antenna with best signal quality");
  setMode(1);
  delay(1000);
  modem.getSignalQuality(quality1);
  setMode(2);
  delay(1000);
  modem.getSignalQuality(quality2);
  setMode(3);
  delay(1000);
  modem.getSignalQuality(quality3);

  int bestQuality;

  if (quality1 > quality2 && quality1 > quality3) { 
    Serial.print("1st antenna is best, with signal quality "); Serial.println(quality1); setMode(1); bestQuality = quality1; 
  } else if (quality2 > quality1 && quality2 > quality3) {
    Serial.print("2nd antenna is best, with signal quality "); Serial.println(quality2); setMode(2); bestQuality = quality2; 
  } else { 
    Serial.print("Third antenna is best, with signal quality "); Serial.println(quality3); setMode(3); bestQuality = quality3; 
  }

  if (bestQuality == 0) {
    Serial.println("No antenna can transmit... skipping.");
    return;
  }
  
  Serial.println("Attmepting to send message");
  int err = modem.sendSBDText(data);
  if (err != ISBD_SUCCESS)
  {
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    if (err == ISBD_SENDRECEIVE_TIMEOUT) {
      Serial.println("Try again with a better view of the sky.");
    }
  }
  else
  {
    Serial.print("Message <");
    Serial.print(data);
    Serial.println("> transmitted");
  }
}

void initializeSPI() {
  Serial.println("Starting up SPI...");
  
  SPI.begin();

  //Set all chip select pins to high
  pinMode(altimeterChipSelect, OUTPUT);
  digitalWrite(altimeterChipSelect, HIGH);
  pinMode(thermocoupleChipSelect, OUTPUT);
  digitalWrite(thermocoupleChipSelect, HIGH);
  pinMode(sdCardChipSelect, OUTPUT);
  digitalWrite(sdCardChipSelect, HIGH);

  Serial.println("Wrote all CS pins to high.");

  Serial.println("Success");
}

/**
 * This function will run on a loop when the RockBLOCK is attempting 
 * to send data. We just collect data and then write it to the data log.
*/
bool ISBDCallback()
{
  //Serial.println("Still trying to send data... STORING DATA IN A CALLBACK");
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return true; // we can fail to parse a sentence in which case we should just wait for another
  }
  

  //delay(DATA_DELAY_TIME);
  
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
  pinMode(CTR1, OUTPUT);
  pinMode(CTR2, OUTPUT);
  
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


  Serial.println("About to start IMU");
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  
  if (!imu.begin()) {
      Serial.println("Failed to communicate with LSM9DS1.");
  }

  servoL.attach(servoPinL);
  servoR.attach(servoPinR);
  servoL.write(angleL); //pointed straight up, angleL = 0
  servoR.write(angleR); //pointed straight up, angleR = 0

  
  
}

int rockBlockSendTime = 0;
int rockBlockSendRate = 60000;

void loop()
{
  Serial.println("Looping");
  GPSData gpsData;
  AltimeterData altimeterData;
  ThermocoupleData thermocoupleData;
  RTCData rtcData;
  IMUData imuData;
  
  int input;

  getAllData(&gpsData, &altimeterData, &thermocoupleData, &rtcData, &imuData);  
  //writeAllDataToSDCard(&gpsData, &altimeterData, &thermocoupleData, &rtcData);

  //Should we send data to ground?
  if (millis() > rockBlockSendTime) {
    
    /* The data will be written to a dataString in this format:
    <TripNumber>:<Hour>:<Minute>:<FixQuality>:<Speed>:<Angle>:<Lon>:<Lat>:<Altitude>:<ExternalTemp>
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

    String dataString = String("202");
    dataString.concat(':'); dataString.concat(hour);
    dataString.concat(':'); dataString.concat(minute);
    dataString.concat(':'); dataString.concat(fixQuality);
    dataString.concat(':'); dataString.concat(speed);
    dataString.concat(':'); dataString.concat(angle);
    dataString.concat(':'); dataString.concat(lon);
    dataString.concat(':'); dataString.concat(lat);
    dataString.concat(':'); dataString.concat(altitude);
    dataString.concat(':'); dataString.concat(externalTemp);

    Serial.print("Attmepting to send ################################################################################################");
    Serial.println(dataString);
    rockBlockSendData(dataString.c_str()); // Send the string data to the rock block

    rockBlockSendTime = millis() + rockBlockSendRate; // Only send data through rock block once every minute.
  }

  /*
   * Controls section of the loop!
   */
  if (XBee.available() > 0) {
    getXBeeControl(); //update angleL and angleR
    servoR.write(angleR);
    servoL.write(angleL);
  }
  
  Serial.print("Right servo: ");
  Serial.println(angleR);
  Serial.print("Left servo: ");
  Serial.println(angleL);
  
  delay(DATA_DELAY_TIME);

}
