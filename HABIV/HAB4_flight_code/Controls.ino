
/*
 * The place for all of the controls functions. 
 * 
 * 
 */



float LatLongDistanceMeters(float lat1, float lon1, float lat2, float lon2) {
  float R = 6378.137; // Radius of earth in KM
  float dLat = lat2 * (PI / 180.0) - lat1 * (PI / 180.0);
  float dLon = lon2 * (PI / 180.0) - lon1 * (PI / 180.0);
  float a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1 * (PI / 180.0)) * cos(lat2 * (PI / 180.0)) * sin(dLon / 2.0) * sin(dLon / 2.0);
  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  float d = R * c;
  return d * 1000; // meters
}

/*
 * 
 * Gets controls from ground control using XBee
 * 
 */


bool getXBeeControl() { //returns if the parachute should be dropped.

  //TODO: THIS SUCKS MAKE IT BETTER, ALEX.
  
  byte input = XBee.read();

  //input should be a delta angle: [_ _ _ _] [_ _ _ _] <- 8 bits
  // the first 4 bits determine the delta for the left servo, vice versa for right servo
  int dL = (input >> 4) - 8; //getting last 4 bits, centering them (range for dL is [-8, 7])
  int dR = (input & 15) - 8; //getting first 4 bits, centering them (range for dR is [-8, 7])

  if ((dL == -8 && dR != -8) || (dL != -8 && dR == -8)) { //reset to zero
    angleR = 0;
    angleL = 0;
    return false;
  } else if (dL == -8 && dR == -8) { //drop command!
    return true;
  }

  // moving servo angle by
  int newAngleL = angleL + dL * SENSITIVITY;
  int newAngleR = angleR + dR * SENSITIVITY;

  //just some fail-safe stuff so we don't overturn the servos

  if (newAngleL > 180) {
    angleL = 180;
  } else if (newAngleL < 0) {
    angleL = 0;
  } else {
    angleL = newAngleL;
  }

  if (newAngleR > 180) {
    angleR = 180;
  } else if (newAngleR < 0) {
    angleR = 0;
  } else {
    angleR = newAngleR;
  }
  return false;
}
