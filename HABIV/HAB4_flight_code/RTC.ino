/**
   Structure for RTC data
*/
struct RTCData {
  byte hour, minute, second;
};

/**
   Starts up the RTC. Returns false in the event of failure.
*/


bool startRTC() {
  Serial.println("Starting up the RTC");
  if (! rtc.begin()) {
    Serial.println("Failed to begin RTC");
    return false;
  }

  if (! rtc.initialized()) {
    Serial.println("RTC not initialized, setting current time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  return true;
}

/**
   Gets the hour, minute, and second from the RTC, and places it in the RTCData struct you provide.
*/
bool getRTCData(RTCData* data) {
  Serial.println("Getting RTC data");
  DateTime now = rtc.now();
  data->hour   = now.hour();
  data->minute = now.minute();
  data->second = now.second();
  Serial.print("Got: "); Serial.print(data->hour); Serial.print(": "); Serial.print(data->minute); Serial.print(": "); Serial.print(data->second); Serial.println("");
  return true;
}
