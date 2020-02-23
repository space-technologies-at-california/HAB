/**
   Structure for ThermocoupleData data
*/
struct ThermocoupleData {
  double internal, external, externalFarenheit;
};

/**
   The thermocouple chip just needs some time to start up. Come on, give it a break!
*/
bool startThermocouple() {
  delay(500); // Give the MAX chip time to start up
  return true;
}


/**
   Get the internal temperature of the thermocouple, along with the external
   temperature in both celsius and farenheit.
*/
bool getThermocoupleData(struct ThermocoupleData* data) {
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
