/**
   Structure for holding GPS data
*/
struct GPSData {
  bool fix;
  uint8_t fixQuality, satellites;
  float speed, latitude, longitude, altitude, angle;
};


/**
   Initializes the GPS chip. Will return false
   if there was an error, and true otherwise.

   TODO: Figure out how to detect an error.
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
   Will fill a GPSData struct with the current GPS data,
   or will return false if a fix is not found on the GPS
   or if it could not parse the GPS message.
*/
bool getGPSData(GPSData* data) {
  char c = GPS.read();
  Serial.print("Checking if GPS has data...");
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      Serial.println(" no data as of yet");
      return false;
    }
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
