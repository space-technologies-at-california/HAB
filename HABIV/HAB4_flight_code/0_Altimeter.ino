/**

  fILE WITH ALL ALTIMETER STRUCTURE AND FUNCTION INFORMATION

   
 */



/**
   Structure for holding Altimeter data
*/
struct AltimeterData {
  double heightMeters1, heightMeters2;
  int32_t pressure1, pressure2, temperature1, temperature2;
};

/**
   Initializes the BaroPressure_MS5607B library that interfaces
   with our altimeter.
*/
bool startAltimeter() {
  Serial.println("Initializing the Altimeter");
  baro.init();
  return true;
}

/**
   Gets first and second order height, temperature, and pressure
   measurements from our altimeter and buffers them into the
   AltimeterData struct argument.

   TODO: figure out how to return false for error values.
*/
bool getAltimeterData(struct AltimeterData* data) {
  Serial.println("Getting data from the altimeter");

  data->heightMeters1 = baro.getHeightMeters(1);
  data->heightMeters2 = baro.getHeightMeters(2);
  data->temperature1 = baro.getT(1);
  data->temperature2 = baro.getT(2);
  data->pressure1 = baro.getP(1);
  data->pressure2 = baro.getP(2);

  return true;
}
