/**
   Structure for UVB data
*/

struct UVBData {
  float reading;
};


bool startUVB(int pin) {
  Serial.println("Starting up the UVB");
  return true;
}

bool getUVBData(struct UVBData* data) {
  Serial.println("Getting UVB data");
  Wire.beginTransmission(WIRE_INPUT);
  if (Wire.available() >= 4) {
    I2C_readAnything(data->reading);
    if (isnan(data->reading)) {
       Serial.println("Error reading from the UVB Sensor");
       return false;
    }
    return true;
  }
  Serial.println("Sensor is not ready yet.");
  return false;

  
  // should check to see if the I2C is ready, then add this to the struct.

  
  // This will sample from the other arduino UNO where the UVB sensor is connected to.
  return true;


  
}
