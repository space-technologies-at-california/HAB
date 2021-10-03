
/*
 * The place for all of the controls functions. 
 * 
 * May add the motor stuff here too.
 * 
 */


int sendControlData(GPSData* gpsData, AltimeterData* altimeterData, RTCData* rtcData, IMUData* imuData) {
  // send this data to the the other board for control stuff.
  // must be fairly fast and reliable, as it can't impede the main loop flow. 
  return 1; // should return 1 if all good, and define some other error codes.
}



float LatLongDistanceMeters(float lat1, float lon1, float lat2, float lon2) {
  float R = 6378.137; // Radius of earth in KM
  float dLat = lat2 * (PI / 180.0) - lat1 * (PI / 180.0);
  float dLon = lon2 * (PI / 180.0) - lon1 * (PI / 180.0);
  float a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1 * (PI / 180.0)) * cos(lat2 * (PI / 180.0)) * sin(dLon / 2.0) * sin(dLon / 2.0);
  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  float d = R * c;
  return d * 1000; // meters
}


struct restrictedZone(float lat, float lon, float r) {
  float latitude = lat;
  float longitude = lon;
  float radius = r; // meters
  
};

bool inZone(struct restrictedZone* zone, float lat, float lon) {
  float distance = LatLongDistanceMeters(lat, lon, zone->latitude, zone->longitude);
  return distance <= zone->radius;
}
