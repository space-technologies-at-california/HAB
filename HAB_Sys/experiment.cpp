#include "experiment.h"

String delimiter = ",";  // Data string delimiter for SD logging b/w sensors
File sd_card_file;  // filesystem object
String curr_data = "";
String sd_filename = "HABdata.csv";

// Conversion constants
double ft_to_m = 0.3048;
// Experiment Specific Code
// 35-45K feet altitude
int servo1_start_alt = 10668;  // 35000 * ft_to_m; // Feet converted to meters
int servo1_end_alt = 13716;  // 45000 * ft_to_m;
// 90-100K feet altitude
int servo2_start_alt = 27432;  // 90000 * ft_to_m;
int servo2_end_alt = 30480;  // 100000 * ft_to_m;

// Globals for servos
Servo servo1;
Servo servo2;
int servo1_pin = 2;
int servo2_pin = 3;
const int servo1_enable_pin = 16;
const int servo2_enable_pin = 6;
int servo_min = 45; // Value to retract servo
int servo_max = 165; // Value to extend servo
bool servo1_extended = false;
bool servo2_extended = false;
unsigned long exp1_start_time = 0;
unsigned long exp2_start_time = 0;
bool exp1_complete = false;
bool exp2_complete = false;
unsigned long timeout = 900000;  // 900 seconds experiment extended timer

bool exp1_locked = false;
bool exp2_locked = false;
unsigned long exp1_lock_time = 0;
unsigned long exp2_lock_time = 0;
unsigned long exp_lock_timeout = 30000;  // 30 seconds to retract on experiment completion

unsigned long scream_timeout = 14400000;  // 4 hour backup scream timeout (in milliseconds)
//unsigned long launch_start = 0;
unsigned long initial_scream_timeout = 9000000;  // 2.5 hour initial timeout stop (in milliseconds)
unsigned long max_scream_alt  = 1000;  // meters



bool time_elapsed(unsigned long exp_start, unsigned long time_diff) {
  // Compares milliseconds since startup to milliseconds since startup for experiment start plus time_diff
  if (millis() > exp_start + time_diff) {
    Serial.println("Time elapsed");
    return true;
  }
  return false;
}

String get_rtc(RTC_DS1307 RTC) {
    DateTime now = RTC.now();
    char buffer[25] = "";
    sprintf(buffer, "%04d/%02d/%02d, %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    return buffer;
}

String get_thermo_data(Adafruit_MAX31855 thermocouple) {
    SPI.end();
    String thermo_data = "";
    thermo_data += thermocouple.readInternal();
    thermo_data += delimiter;
    double c = thermocouple.readCelsius();
    double f = thermocouple.readFarenheit();
    if (isnan(c)) {
        Serial.println("Something wrong with thermocouple!");
        thermo_data += "Failed";
    } else {
        thermo_data += String(c);
    }
    thermo_data += delimiter;
    if (isnan(f)) {
        Serial.println("Something wrong with thermocouple!");
        thermo_data += "Failed";
    } else {
        thermo_data += String(f);
    }
    return thermo_data;
}

// Read ambient sensor temperature
String get_ambient_temp(DallasTemperature system_sensor, DallasTemperature outer_sensor) {
  String ambient_temp = "";
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting System temperature...");
  system_sensor.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
 // Serial.print("Temperature for the" + sensor_name +  " sensor (index 0) is: ");
  Serial.println(system_sensor.getTempCByIndex(0));
  ambient_temp += system_sensor.getTempCByIndex(0);
  ambient_temp += delimiter;

  Serial.print("Requesting outer temperature...");
  outer_sensor.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
 // Serial.print("Temperature for the" + sensor_name +  " sensor (index 0) is: ");
  Serial.println(outer_sensor.getTempCByIndex(0));
  ambient_temp += outer_sensor.getTempCByIndex(0);
  return ambient_temp;
}


void write_to_sd(String data) {
    // The following is the code to write to sd card
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    sd_card_file = SD.open(sd_filename, FILE_WRITE);
    
    // if the file opened, write to it:
    if (sd_card_file) {
        //    Serial.print("Writing to file ...");
        sd_card_file.println(data);
        // close the file:
        sd_card_file.close();
        //    Serial.println("done writing to file");
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening file");
    }
}


void enable_servo(int servo_id) {
  if (servo_id == 1) {
      Serial.println("Enabling Servo 1");
      digitalWrite(servo1_enable_pin, HIGH);
  } else if (servo_id == 2) {
      Serial.println("Enabling Servo 2");
      digitalWrite(servo2_enable_pin, HIGH);
  }
}

/*
 * Read imu data
 */

String read_imu(Adafruit_LSM9DS0 lsm) {
  lsm.read();
  String imu_data = "";
  Serial.print("Accel X: "); 
  Serial.print((int)lsm.accelData.x); 
  Serial.println(" ");
  imu_data += (int)lsm.accelData.x;
  imu_data += delimiter;
  Serial.print("Accel Y: "); 
  Serial.print((int)lsm.accelData.y);       
  Serial.println(" ");
  imu_data += (int)lsm.accelData.y;
  imu_data += delimiter;
  Serial.print("Accel Z: "); 
  Serial.print((int)lsm.accelData.z);     
  Serial.println(" ");
  imu_data += (int)lsm.accelData.z;
  imu_data += delimiter;
  Serial.print("Mag X: "); 
  Serial.print((int)lsm.magData.x);     
  Serial.println(" ");
  imu_data += (int)lsm.magData.x;
  imu_data += delimiter;
  Serial.print("Mag Y: "); 
  Serial.print((int)lsm.magData.y);         
  Serial.println(" ");
  imu_data += (int)lsm.magData.y;
  imu_data += delimiter;
  Serial.print("Mag Z: "); 
  Serial.print((int)lsm.magData.z);       
  Serial.println(" ");
  imu_data += (int)lsm.magData.z;
  imu_data += delimiter;
  Serial.print("Gyro X: "); 
  Serial.print((int)lsm.gyroData.x);   
  Serial.println(" ");
  imu_data += (int)lsm.gyroData.x;
  imu_data += delimiter;
  Serial.print("Gyro Y: "); 
  Serial.print((int)lsm.gyroData.y);        
  Serial.println(" ");
  imu_data += (int)lsm.gyroData.y;
  imu_data += delimiter;
  Serial.print("Gyro Z: "); 
  Serial.print((int)lsm.gyroData.z);      
  Serial.println(" ");
  imu_data += (int)lsm.gyroData.z;
  imu_data += delimiter;
  Serial.print("Temp: "); 
  Serial.print((int)lsm.temperature);    
  Serial.println(" ");
  imu_data += (int)lsm.temperature;
  delay(200);
  return imu_data;
}
void disable_servo(int servo_id) {
  if (servo_id == 1) {
      Serial.println("Disabling Servo 1");
      digitalWrite(servo1_enable_pin, LOW);
  } else if (servo_id == 2) {
      Serial.println("Disabling Servo 2");
      digitalWrite(servo2_enable_pin, LOW);
  }
  
}

void setup_servos() {
  Serial.println("Initialization Servos...");
  // Power the servos by pulling the fet's gate high
  pinMode(servo1_enable_pin, OUTPUT);
//  pinMode(servo2_enable_pin, OUTPUT);
  delay(100);
  servo1.attach(servo1_pin);
//  servo2.attach(servo2_pin);

  enable_servo(1);
//  enable_servo(2);
  extend_servo(1);
  delay(20000);
  return_servo(1);
//  return_servo(2);
  delay(20000);  // Setup servos to be fully retracted
  disable_servo(1);
//  disable_servo(2);
  Serial.println("Servo initialization done");
}

void extend_servo(int servo_id) {
  if (servo_id == 1) {
      servo1.write(servo_max);
      servo1_extended = true;
  } else if (servo_id == 2) {
      servo2.write(servo_max);
      servo2_extended = true;
  }
}

void return_servo(int servo_id) {
  if (servo_id == 1) {
      servo1.write(servo_min);
      servo1_extended = false;
  } else if (servo_id == 2) {
      servo2.write(servo_min);
      servo2_extended = false;
  }
}

bool should_scream(double alt, long launch_start) {
  // alt in meters
  if ((millis() > launch_start + scream_timeout) || ((alt < max_scream_alt) && (millis() > launch_start + initial_scream_timeout)) ) {
    return true;
  }
  return false;
}


void run_experiment(long launch_st, Intersema::BaroPressure_MS5607B baro, Adafruit_MAX31855 thermocouple, Adafruit_MAX31855 thermocouple_cam, RTC_DS1307 RTC, DallasTemperature system_sensor, DallasTemperature outside_sensor, Adafruit_LSM9DS0 lsm) {
  // fetch the time
   String curr_time = get_rtc(RTC);
   Serial.print("Current Time: ");
   Serial.println(curr_time);
   curr_data += curr_time;
   curr_data += delimiter;

  String thermo_data = get_thermo_data(thermocouple);
  Serial.print("Thermocouple Temp: ");
  Serial.println(thermo_data);
  curr_data += thermo_data;
  curr_data += delimiter;

  String thermo_cam_data = get_thermo_data(thermocouple_cam);
  Serial.print("Camera thermocouple temp: ");
  Serial.println(thermo_cam_data);
  curr_data += thermo_cam_data;
  curr_data += delimiter;

  double alt = baro.getHeightMeters(2);
  int32_t alt_pressure = baro.getP(2);
  double alt_temp = (double)(baro.getT(2))/100;
  uint32_t raw_alt_temp = baro.getRawT();
  uint32_t raw_alt_press = baro.getRawP();
  Serial.print("Meters: ");
  Serial.print((float)(alt));
  Serial.print(", Feet: ");
  Serial.println((float)(alt) * 3.2808);
  Serial.print("Pressure (Pa): ");
  Serial.println(alt_pressure);
  Serial.print("Altimeter Temp: ");
  Serial.println(alt_temp);
  curr_data += String(alt, 2);
  curr_data += delimiter;
  curr_data += String(alt_pressure);
  curr_data += delimiter;
  curr_data += String(alt_temp);
  curr_data += delimiter;
  curr_data += String(raw_alt_temp);
  curr_data += delimiter;
  curr_data += String(raw_alt_press);
  
  //Tracksoar Code
  Serial.println("Tracksoar Code");
  float tr_alt = get_alt_fl();
  float tr_lat = get_lat_fl();
  float tr_lon = get_lon_fl();
  float tr_spd = get_speed_fl();
//  char lat_arr[10] = "";
//  char lon_arr[10] = "";
//  get_lon_char(lon_arr);
//  get_lat_char(lat_arr);
//  Serial.print("Tracksoar Char Lat: ");
//  Serial.println(lat_arr);
//  Serial.print("Tracksoar Char Lon: ");
//  Serial.println(lon_arr);
  byte gps_lock = get_gps_lock();
  Serial.print("Tracksoar GPS Lock: ");
  Serial.println(gps_lock);
  Serial.print("Tracksoar Altitude: ");
  Serial.println(tr_alt);
  Serial.print("Tracksoar Latitude: ");
  Serial.println(tr_lat);
  Serial.print("Tracksoar Longitude: ");
  Serial.println(tr_lon);
  Serial.print("Tracksoar Speed: ");
  Serial.println(tr_spd);
  curr_data += String(tr_alt);
  curr_data += delimiter;
  curr_data += String(tr_lat);
  curr_data += delimiter;
  curr_data += String(tr_lon);
  curr_data += delimiter;
  curr_data += String(tr_spd);
  curr_data += delimiter;
  
  // Run Experiment Code
  // Starts experiment 1
  if (!exp1_complete && !servo1_extended && alt > servo1_start_alt && alt < servo1_end_alt) {
    enable_servo(1);
    extend_servo(1);
    exp1_start_time = millis();
    Serial.print("Started Experiment 1 at ");
    Serial.print(alt/ft_to_m);
    Serial.println("ft");
  }
  // Stops experiment 1
  if (!exp1_complete && servo1_extended && !exp1_locked && (alt > servo1_end_alt || time_elapsed(exp1_start_time, timeout)) ) {
    return_servo(1);
    exp1_complete = true;
    exp1_lock_time = millis();
    Serial.print("Experiment 1 Complete at ");
    Serial.print(alt/ft_to_m);
    Serial.println("ft");
  }
  // Sets experiment 1 Lock so we do not continue to send PWM signal in case of stall
  if (!exp1_locked && exp1_complete && time_elapsed(exp1_lock_time, exp_lock_timeout)) {
    disable_servo(1);
    exp1_locked = true;
    servo1_extended = false;
    Serial.println("Locked Servo 1");
  }

//  // Starts experiment 2
//  if (!exp2_complete && !servo2_extended && alt > servo2_start_alt && alt < servo2_end_alt) {
//    enable_servo(2);
//    extend_servo(2);
//    exp2_start_time = millis();
//    Serial.print("Started Experiment 2 at ");
//    Serial.print(alt/ft_to_m);
//    Serial.println("ft");
//  }
//  // Stops experiment 2
//  if (!exp2_complete && servo2_extended && !exp2_locked && (alt > servo2_end_alt || time_elapsed(exp2_start_time, timeout))) {
//    return_servo(2);
//    exp2_complete = true;
//    exp2_lock_time = millis();
//    Serial.print("Experiment 2 Complete at ");
//    Serial.print(alt/ft_to_m);
//    Serial.println("ft");
//  }
//  // Sets experiment 2 Lock so we do not continue to send PWM sig in case of stall
//  if (!exp2_locked && exp2_complete && time_elapsed(exp2_lock_time, exp_lock_timeout)) {
//    disable_servo(2);
//    exp2_locked = true;
//    servo2_extended = false;
//    Serial.println("Locked Servo 2");
//  }
  
  curr_data += servo1_extended;
  curr_data += delimiter;
//  curr_data += servo2_extended;
  Serial.println("Collecting ambient temperature data");
  String ambient_data = get_ambient_temp(system_sensor, outside_sensor);
  curr_data += ambient_data;
  curr_data += delimiter;
  Serial.println("Collecting imu data");
  String imu_data = read_imu(lsm);
  curr_data += imu_data;
  curr_data += delimiter;
  
  write_to_sd(curr_data);
  curr_data = "";

   if(should_scream(alt, launch_st)){
    Serial.println("Secondary Transmitter Screaming");
    char msg[60];
    String buf;
    buf += F("lat: ");
    buf += String(tr_lat);
    buf += F("\nlon: ");
    buf += String(tr_lon);
    buf += String("\nalt: ");
    buf += String(tr_alt);
    buf += String("\nspd: ");
    buf += String(tr_spd);
    buf.toCharArray(msg, 60);
    scream_for_help_with_message(msg);
  }
  
  delay(1000);
}




