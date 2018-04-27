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
 * IMU Sensor Setup
 */


void setup_imu_sensor(Adafruit_LSM9DS0 lsm) {
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);


   // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("LSM9DS0 9DOF IMU Initialized");

}

/*
 * Ambient Temperature Sensor Setup
 */

void setup_ambient(DallasTemperature system_sensor, DallasTemperature outside_sensor) {
   // Setup Ambient Temp Sensors
  system_sensor.begin();
  outside_sensor.begin();
  Serial.println("Ambient sensor intialization done");
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

void setup_all(Intersema::BaroPressure_MS5607B baro, Adafruit_MAX31855 thermocouple, Adafruit_MAX31855 thermocouple_cam, RTC_DS1307 RTC, DallasTemperature system_sensor, DallasTemperature outside_sensor){
  setup_rtc(RTC);
  setup_SD();
  setup_thermo(thermocouple);
  setup_thermo(thermocouple_cam);
  setup_ambient(system_sensor, outside_sensor);
  baro.init();
  transceiver_setup();
}


