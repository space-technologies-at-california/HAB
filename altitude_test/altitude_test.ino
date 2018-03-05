/* Written for the Parallax MS5607 module 
 * Datasheet: https://www.parallax.com/sites/default/files/downloads/29124-MS5607-02BA03-Datasheet.pdf
 * 
 * For the modified IntersemaBaro.h library
 * Used to test accuracy of calculations at high altitudes (above 11km)
 * 
 * By: Olivia Hsu
 */
union ArrayToInteger {
  byte arr[4];
  uint32_t integer;
};

int32_t coefficients_[6] = {42512, 38208, 27127, 24461, 28157, 32001};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  //put your main code here, to run repeatedly:
  ArrayToInteger in1, in2;
  while(Serial.available() <= 0) {}
  long int1, int2;
  while (Serial.available()) {
    if(Serial.available() > 0) {
       int1 = Serial.parseInt();
    }
  }
  Serial.print('a');
  
  while(Serial.available() <= 0) {}
  while (Serial.available()) {
    if(Serial.available() > 0) {
       int2 = Serial.parseInt();
    }
  }
    
    
  uint32_t dt = int1;
  uint32_t dp = int2;
  Serial.println(ConvertTemperature(dt));
  
  while(Serial.available() <= 0) {}  
  Serial.read();
  
  Serial.println(ConvertPressure(dp, dt));
  while(Serial.available() <= 0) {}
  Serial.read();
//  int32_t pressurePa = ConvertPressure(dp, dt);
//  //Serial.println((int32_t)pressurePa);
//  Serial.flush();
//  delay(500);
  
//  int32_t temp = ConvertTemperature(dt);
//  Serial.println(temp);
  Serial.flush();
}





// Functions from modified IntersemaBaro.h Library

double PascalToMeter(int32_t pressurePa)
    {
      const double R = 8.3144598;
      const double g = 9.80665;
      const double M = 0.0289644;

      const uint32_t N = 5;
      const double h_b[N] = {0.0, 11000.0, 20000.0, 32000.0, 47000.0};
      const double P_b[N] = {101325.0, 22632.1, 5474.89, 868.02, 110.91};
      const double T_b[N] = {288.15, 216.65, 216.65, 228.65, 270.65};
      const double L_b[N] = {-0.0065, 0, 0.001, 0.0028, 0};

      if (pressurePa > P_b[0]) {
        return 0;
      }
  
      int i;
      for(i = 0; i < N; i++) {
        if(pressurePa > P_b[i]) break;
      }
      i = i - 1;
      double height;
      if (L_b[i] == (double)(0)) {
        height = (double)(R*T_b[i]*log((double)(pressurePa)/(double)(P_b[i]))/((double)(-1) * g * M)) + (h_b[i]);
      } else {
        height = ((T_b[i]/pow((double)(pressurePa)/(double)(P_b[i]),  (R*L_b[i])/(g*M))) - T_b[i])/L_b[i] + (double)(h_b[i]);
      }
      
      return height;
}

int32_t ConvertPressure(uint32_t pressure, uint32_t temperature)
{
      // calculate 1st order pressure and temperature (MS5607 1st order algorithm)
      int32_t T2 = 0;
      int64_t OFF2 = 0;
      int64_t SENS2 = 0;
      
      const int32_t dT    = temperature - (int32_t)(coefficients_[4]) * 256;                     // difference between actual and reference temperature
      const int32_t temp  = (int32_t)(2000 + ((int64_t)dT * (int64_t)coefficients_[5]) / pow(2, 23)) ; // / 100;       // actual temperature

      // MS5607 2nd order algorithm
      if (temp < 2000) {
        T2 = (int32_t)(pow(dT, 2) / pow(2, 31)); //NEEDS FIXING
        OFF2 = (int64_t)(61 * pow((int64_t)(temp)-2000, 2)/ pow(2, 4));
        SENS2 = (int64_t)(2 * pow(temp-2000, 2));
        
        if(temp < -15) {
          OFF2 = OFF2 + (int64_t)(15 * pow(temp + 1500, 2));
          SENS2 = SENS2 + (int64_t)(8 * pow(temp + 1500, 2));
        }
      }
    
      const int64_t OFF1   = (int64_t)(coefficients_[1]) * pow(2, 17) + (int64_t)(dT) * (int64_t)(coefficients_[3]) / pow(2, 6); // offset at actual temperature
      const int64_t SENS1  = (int64_t)(coefficients_[0]) * pow(2, 16) + (int64_t)(dT) * (int64_t)(coefficients_[2]) / pow(2, 7); // sensitivity at actual temperature
      
      const int64_t OFF = OFF1 - OFF2;
      const int64_t SENS = SENS1 - SENS2;
      const int32_t press = (int32_t)(((int64_t)(pressure) * SENS / pow(2, 21) - OFF) / pow(2, 15));  // temperature compensated (2nd order) pressure

      if (press < 1000) {
        return 1000;
      } else if ( press > 120000) {
        return 120000;
      }
      return press; 
}

int32_t ConvertTemperature(uint32_t temperature)
{

    // calcualte 1st order pressure and temperature (MS5607 1st order algorithm)
    int32_t T2 = 0;
    const int32_t dT    = temperature - (int32_t)(coefficients_[4]) * 256;                     // difference between actual and reference temperature
    const int32_t temp1  = (int32_t)(2000 + ((int64_t)dT * (int64_t)coefficients_[5]) / pow(2, 23)) ;      // actual temperature

    if (temp1 < 2000) {
        T2 = (int32_t)(pow(dT, 2) / pow(2, 31)); //NEEDS FIXING
    }

    if (temp1 - T2 < -4000) {
      return -4000;
    } else if (temp1 - T2 > 8500) {
      return 8500;
    } 
    return temp1 - T2; 
}
