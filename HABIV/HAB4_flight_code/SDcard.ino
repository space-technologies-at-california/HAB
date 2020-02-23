
/**
   Initializes the SD card.
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
   Write all data to the log file on the SD card. Returns false if it could not open the
   log file.
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
