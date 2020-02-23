/**
   sets the CTR1, CTR2 pins depending on which
   reciever rf chosen.
*/


void setMode(int rf) {
  digitalWrite(CTR1, LOW);
  digitalWrite(CTR2, LOW);

  if (rf == 1) {
    digitalWrite(CTR1, HIGH);
  }
  else if (rf == 2) {
    digitalWrite(CTR2, HIGH);
  }
  else if (rf == 3) {
    digitalWrite(CTR1, HIGH);
    digitalWrite(CTR2, HIGH);
  }
}

/**
   Buffers all peripheral data into the given structs.
*/
bool getAllData(struct GPSData* gpsData, struct AltimeterData* altimeterData, struct ThermocoupleData* thermocoupleData, struct RTCData* rtcData, struct IMUData* imuData) {

  getGPSData(gpsData);
  getAltimeterData(altimeterData);
  getThermocoupleData(thermocoupleData);
  getRTCData(rtcData);
  getIMUData(imuData, true); //True for DPS values

  return true;
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
   This function will run on a loop when the RockBLOCK is attempting
   to send data. We just collect data and then write it to the data log.
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

int rockBlockSendTime = 0;
int rockBlockSendRate = 60000;

void setup()
{
  pinMode(CTR1, OUTPUT);
  pinMode(CTR2, OUTPUT);

  Serial.begin(115200);

  initializeSPI();

  Serial.println("About to start GPS");
  //startGPS();

  Serial.println("About to start Altimeter");
  startAltimeter();

  Serial.println("About to start Thermocouple");
  startThermocouple();

  Serial.println("About to start RTC");
  startRTC();

  Serial.println("About to start SD");
  startSD();

  Serial.println("About to start RockBLOCK");
  //startRockBlock();

  Serial.println("About to start IMU");
  if (!lsm.begin()) {
    Serial.println("Failed to communicate with LSM9DS1.");
    while (1);
  }
  setupLSM();



  servoRelease.attach(releasePin);

}

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
  writeAllDataToSDCard(&gpsData, &altimeterData, &thermocoupleData, &rtcData);

  //Should we send data to ground?
  if (false) {//if (millis() > rockBlockSendTime) {

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
  delay(DATA_DELAY_TIME);

}
