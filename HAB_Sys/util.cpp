#include "util.h"
//#include "experiment.cpp"

int sd_card_pin = 47;  // SD card CS pin
//String delimiter = ",";  // Data string delimiter for SD logging b/w sensors
//File sd_card_file;  // filesystem object
//String sd_filename = "HABdata.csv";



/*
   RTC (Real Time Clock) Specific
*/
void setup_rtc(RTC_DS1307 RTC) {
  // connect to RTC
  Wire.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  if (!RTC.begin()) Serial.println("RTC failed");
}


/*
   Thermo Couple Sensor Setup
*/
void setup_thermo(Adafruit_MAX31855 thermocouple) {
  // Thermo couple is setup when creating the object.
  Serial.print("Initializing Thermo Couple...");
  delay(1000);  // wait for MAX thermo chip to stabilize
  double c = thermocouple.readCelsius();
  if (isnan(c)) {
    Serial.println("Failed to initialize Thermo Couple");
  } else {
    Serial.println("Thermo Couple initialization done.");
  }
}

/*
   SD Card Specific
*/
void setup_SD() {
  Serial.print("Initializing SD card...");
  if (!SD.begin(sd_card_pin)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");
}

void setup_all(Intersema::BaroPressure_MS5607B baro, Adafruit_MAX31855 thermocouple, RTC_DS1307 RTC){
  setup_SD();
  setup_thermo(thermocouple);
  baro.init();
  transceiver_setup();
}


