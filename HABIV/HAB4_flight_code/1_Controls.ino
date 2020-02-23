
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
