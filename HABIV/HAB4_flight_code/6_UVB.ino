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

  // This will sample from the other arduino UNO where the UVB sensor is connected to.
  return true;
}
