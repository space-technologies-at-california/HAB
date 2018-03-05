// http://code.google.com/p/ardroneme/
// From the file NavData2.zip 

/* Updated by MAPGPS based on Richi's code:
 * http://ulrichard.is-a-geek.net/?p=23
 */

//Update by boulderjoe 12/30/11 to work with arduino 1.0 

#ifndef INTERSEMA_BARO_H
#define INTERSEMA_BARO_H

#include <Wire.h>
#include <util/delay.h>
#include "Arduino.h"

namespace Intersema
{
  
class BaroPressure
{
public:
    virtual void init() = 0;   
   
    double getHeightMeters(int order)
    {
        return AcquireAveragedSampleM(NUM_SAMP_FOR_AVG, order);
    }
    
    int32_t getHeightCentiMeters(void)
    {
        return AcquireAveragedSampleCm(NUM_SAMP_FOR_AVG);
    }   

   int32_t getP(int order) {
     return AcquireAveragedSampleP(NUM_SAMP_FOR_AVG, order);
   }

   int32_t getT(int order) {
     return AcquireAveragedSampleT(NUM_SAMP_FOR_AVG, order);
   }

   uint32_t getRawT() {
    return AcquireRawT();
   }

   uint32_t getRawP() {
     AcquireRawP();
   }
    
protected:
    virtual int32_t AcquireAveragedSampleCm(const uint8_t nSamples) = 0;
    virtual double AcquireAveragedSampleM(const uint8_t nSamples, int order) = 0;
    virtual int32_t AcquireAveragedSampleP(const uint8_t nSamples, int order) = 0;
    virtual int32_t AcquireAveragedSampleT(const uint8_t nSamples, int order) = 0;
    virtual uint32_t AcquireRawP() = 0;
    virtual uint32_t AcquireRawT() = 0;

  //  virtual int32_t ConvertPressureTemperature(uint32_t pressure, uint32_t temperature) = 0;
    
    int32_t PascalToCentimeter(const int32_t pressurePa)
    {
        // Lookup table converting pressure in Pa to altitude in cm.
        // Each LUT entry is the altitude in cm corresponding to an implicit
        // pressure value, calculated as [PA_INIT - 1024*index] in Pa.
        // The table is calculated for a nominal sea-level pressure  = 101325 Pa.
        static const int32_t PZLUT_ENTRIES = 77;
        static const int32_t PA_INIT       = 99999;
        static const int32_t PA_DELTA      = 1024;

        static const int32_t lookupTable[PZLUT_ENTRIES] = {
	    -29408, -21087, -12700,  -4244,   4279,
	     12874,  21541,  30281,  39095,  47986,
	     56953,  66000,  75126,  84335,  93628,
	    103006, 112472, 122026, 131672, 141410,
	    151244, 161174, 171204, 181335, 191570,
	    201911, 212361, 222922, 233597, 244388,
	    255300, 266334, 277494, 288782, 300204,
	    311761, 323457, 335297, 347285, 359424,
	    371719, 384174, 396795, 409586, 422552,
	    435700, 449033, 462560, 476285, 490216,
	    504360, 518724, 533316, 548144, 563216,
	    578543, 594134, 609999, 626149, 642595,
	    659352, 676431, 693847, 711615, 729752,
	    748275, 767202, 786555, 806356, 826627,
	    847395, 868688, 890537, 912974, 936037,
	    959766, 984206};

        

        if(pressurePa > PA_INIT) 
             return lookupTable[0];
        else 
        {
           const int32_t inx = (PA_INIT - pressurePa) >> 10;      
           if(inx >= PZLUT_ENTRIES - 1) 
               return lookupTable[PZLUT_ENTRIES - 1];
           else 
           {
                const int32_t pa1 = PA_INIT - (inx << 10);
                const int32_t z1 = lookupTable[inx];
                const int32_t z2 = lookupTable[inx+1];
                return (z1 + (((pa1 - pressurePa) * (z2 - z1)) >> 10));
            }
        }
    }

    double PascalToMeter(int32_t pressurePa)
        {
          const double R = 8.3144598;
          const double g = 9.80665;
          const double M = 0.0289644;
    
          const uint32_t N = 5;
          const double h_b[N] = {0.0, 11000.0, 20000.0, 32000.0, 47000.0};
          const double P_b[N] = {101740.0, 22632.1, 5474.89, 868.02, 110.91};
          const double T_b[N] = {285.15, 216.65, 216.65, 228.65, 270.65};
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
    
    static const uint8_t NUM_SAMP_FOR_AVG = 4;

    unsigned int coefficients_[6];
};

class BaroPressure_MS5607B : public BaroPressure
{
public:
    /// @param CSB  i2c address select
    BaroPressure_MS5607B(bool CSB = false) : i2cAddr_((CSB ? 0xEC : 0xEE) >> 1) { }
    
    void init()
    {    
        ResetSensor();
        ReadCoefficients();
    }
    
private:

    const uint8_t i2cAddr_;
    static const uint8_t cmdReset_   = 0x1E;
    static const uint8_t cmdAdcRead_ = 0x00;
    static const uint8_t cmdAdcConv_ = 0x40;
    static const uint8_t cmdAdcD1_   = 0x00;
    static const uint8_t cmdAdcD2_   = 0x10;
    static const uint8_t cmdAdc256_  = 0x00;
    static const uint8_t cmdAdc512_  = 0x02;
    static const uint8_t cmdAdc1024_ = 0x04;
    static const uint8_t cmdAdc2048_ = 0x06;
    static const uint8_t cmdAdc4096_ = 0x08;
    static const uint8_t cmdPromRd_  = 0xA0;

    void ResetSensor()
    {
	      Wire.begin();
        Wire.beginTransmission(i2cAddr_);
        Wire.write(cmdReset_);   
        Wire.endTransmission(); 
        delay(3);
    }

    void ReadCoefficients(void)
    {
        for(uint8_t i=0; i<6; ++i)
            coefficients_[i] = ReadCoefficient(i + 1);  
            
#ifdef DEBUG
	for(uint8_t i=0; i<6; ++i)
        {
            Serial.print("Coefficient ");
            Serial.print(i + 1, DEC);
            Serial.print(" : ");
            Serial.println(coefficients_[i], DEC);
        }
        Serial.println(ConvertPressureTemperature(6074082, 8574974));
        Serial.println(ConvertPressureTemperature(6074082, 8574984));
#endif
    }

    uint16_t ReadCoefficient(const uint8_t coefNum)
    {
        uint16_t rC=0;
    
        Wire.beginTransmission(i2cAddr_);
        Wire.write(cmdPromRd_ + coefNum * 2); // send PROM READ command
        Wire.endTransmission(); 
    
        Wire.requestFrom(i2cAddr_, static_cast<uint8_t>(2));

        if(Wire.available() >= 2)
        {
            uint16_t ret = Wire.read();   // read MSB and acknowledge
            uint16_t rC  = 256 * ret;
            ret = Wire.read();        // read LSB and not acknowledge
            rC  = rC + ret;
            return rC;
        }
#ifdef DEBUG
        else
        {
	    Serial.println("No data available in ReadCoefficient()");
        }
#endif 
    
        return 0;
    }

    virtual int32_t AcquireAveragedSampleCm(const uint8_t nSamples)
    {
        int64_t pressAccum = 0;

        for(size_t n = nSamples; n; n--) 
        {
            const uint32_t temperature = ReadAdc(cmdAdcD2_ | cmdAdc4096_); // digital temperature value : typical 8077636  
            const uint32_t pressure    = ReadAdc(cmdAdcD1_ | cmdAdc4096_); // digital pressure value : typical 6465444        
            const uint32_t pressConv   = ConvertPressureTemperature(pressure, temperature);                 
            pressAccum += pressConv;

            //MAPGPS
//            Serial.print("pressure: ");
//            Serial.print(pressure, DEC);
//            Serial.print(", pressConv: ");
//            Serial.print(pressConv, DEC);
//            Serial.print(", temperature: ");
//            Serial.println(temperature, DEC);

        }

        const int32_t pressAvg = pressAccum / nSamples;
//        Serial.print(pressAvg);        
        const int32_t AltCm = PascalToCentimeter(pressAvg);
	
        return AltCm;	
    }

    virtual double AcquireAveragedSampleM(const uint8_t nSamples, int order)
    {
        int64_t pressAccum = 0;

        for(size_t n = nSamples; n; n--) 
        {
            const uint32_t temperature = ReadAdc(cmdAdcD2_ | cmdAdc4096_); // digital temperature value : typical 8077636  
            const uint32_t pressure    = ReadAdc(cmdAdcD1_ | cmdAdc4096_); // digital pressure value : typical 6465444        
            uint32_t pressConv   = 0;
            if (order == 1) {
              pressConv = ConvertPressure(pressure, temperature);                 
            } else {
              pressConv = ConvertPressure2(pressure, temperature);                   
            }
            pressAccum += pressConv;
        }

        const int32_t pressAvg = pressAccum / nSamples;      
        const double AltM = PascalToMeter(pressAvg);
	
        return AltM;	
    }
    virtual int32_t AcquireAveragedSampleP(const uint8_t nSamples, int order)
    {
        int64_t pressAccum = 0;

        for(size_t n = nSamples; n; n--) 
        {
            const uint32_t temperature = ReadAdc(cmdAdcD2_ | cmdAdc4096_); // digital temperature value : typical 8077636  
            const uint32_t pressure    = ReadAdc(cmdAdcD1_ | cmdAdc4096_); // digital pressure value : typical 6465444  
            uint32_t pressConv         = 0;   
            if (order == 1) {
                pressConv  =  ConvertPressure(pressure, temperature);
            } else {
              pressConv = ConvertPressure2(pressure, temperature);             
            }
            pressAccum += pressConv;
        }

        const int32_t pressAvg = pressAccum / nSamples;      
        return pressAvg;
    }
    virtual uint32_t AcquireRawT() {
      return (uint32_t)ReadAdc(cmdAdcD2_ | cmdAdc4096_);
    }
    virtual uint32_t AcquireRawP() {
      return (uint32_t)ReadAdc(cmdAdcD1_ | cmdAdc4096_);
    }
    virtual int32_t AcquireAveragedSampleT(const uint8_t nSamples, int order)
    {
        int64_t tempAccum = 0;

        for(size_t n = nSamples; n; n--) 
        {
            const uint32_t temperature = ReadAdc(cmdAdcD2_ | cmdAdc4096_); // digital temperature value : typical 8077636        
            int32_t tempConv   = 0;
            if (order == 1) {
              tempConv = ConvertTemperature(temperature);                 
            } else {
              tempConv = ConvertTemperature2(temperature);   
            }
            tempAccum += tempConv;
        }

        const int32_t tempAvg = tempAccum / nSamples;      
        return tempAvg;
    }
    int32_t ReadAdc(const uint8_t cmd)
    {             
        Wire.beginTransmission(i2cAddr_);
        Wire.write(cmdAdcConv_ | cmd); // send conversion command
        Wire.endTransmission(); 

        // wait necessary conversion time
        switch(cmd & 0x0f) 
        {
        case cmdAdc256_: 
            delay(1);
            break;
        case cmdAdc512_: 
            delay(3);
            break;
        case cmdAdc1024_: 
            delay(4);
            break;
        case cmdAdc2048_: 
            delay(6);
            break;
        case cmdAdc4096_: 
            delay(10); 
            break;
        }

        Wire.beginTransmission(i2cAddr_);
        Wire.write(cmdAdcRead_);
        Wire.endTransmission();
    
        Wire.requestFrom(i2cAddr_, static_cast<uint8_t>(3));

        if(Wire.available() >= 3)
        {
            uint16_t ret  = Wire.read(); // read MSB and acknowledge
            uint32_t temp = 65536 * ret;
            ret  = Wire.read();      // read byte and acknowledge
            temp = temp + 256 * ret;
            ret  = Wire.read();  // read LSB and not acknowledge
            temp = temp + ret;
                
            return temp;
        }
#ifdef DEBUG
        else
        {
	    Serial.println("No data available in cmdAdc()");
        }
#endif 
        
        return 0;
    }

    uint32_t ConvertPressureTemperature(uint32_t pressure, uint32_t temperature)
    {
        // calcualte 1st order pressure and temperature (MS5607 1st order algorithm)
        const int32_t dT    = temperature - (int32_t)(coefficients_[4]) * 256;                     // difference between actual and reference temperature
        //const int32_t temp  = (2000 + (dT * coefficients_[5]) / pow(2, 23)) ; // / 100;       // actual temperature

        //const int64_t OFF   = static_cast<int64_t>(coefficients_[1]) * pow(2, 17) + dT * coefficients_[3] / pow(2, 6); // offset at actual temperature
        //const int64_t SENS  = static_cast<int64_t>(coefficients_[0]) * pow(2, 16) + dT * coefficients_[2] / pow(2, 7); // sensitivity at actual temperature
        //const int32_t press = ((pressure * SENS / pow(2, 21) - OFF) / pow(2, 15)); // / 100;      // temperature compensated pressure
         
        //MAPGPS: adapt formulas to avoid overflow
        const int32_t OFF   = coefficients_[1] * 4 + ((float)dT / 2048) * ((float)coefficients_[3] / 1024);
        const int32_t SENS  = coefficients_[0] * 2 + ((float)dT / 4096) * ((float)coefficients_[2] / 1024);
        const int32_t press =  ((float)pressure / 2048) * ((float)SENS / 1024) - OFF;

/*
        Serial.println();
        Serial.println(dT, DEC);
        Serial.println(OFF, DEC);
        Serial.println(SENS, DEC);
        Serial.println();
*/
        return press; 
    }
    int32_t ConvertPressure(uint32_t pressure, uint32_t temperature)
    {
        // calcualte 1st order pressure and temperature (MS5607 1st order algorithm)
        const int32_t dT    = temperature - (int32_t)(coefficients_[4]) * 256;                     // difference between actual and reference temperature

        const int64_t OFF   = (int64_t)(coefficients_[1]) * pow(2, 17) + (int64_t)(dT) * (int64_t)(coefficients_[3]) / pow(2, 6); // offset at actual temperature
        const int64_t SENS  = (int64_t)(coefficients_[0]) * pow(2, 16) + (int64_t)(dT) * (int64_t)(coefficients_[2]) / pow(2, 7); // sensitivity at actual temperature
        const int32_t press = (int32_t)(((int64_t)(pressure) * SENS / pow(2, 21) - OFF) / pow(2, 15)); // / 100;      // temperature compensated pressure

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
        const int32_t dT    = temperature - (int32_t)(coefficients_[4]) * 256;                     // difference between actual and reference temperature
        const int32_t temp  = (int32_t)(2000 + ((int64_t)dT * (int64_t)coefficients_[5]) / pow(2, 23)) ; // / 100;       // actual temperature
        
       if (temp < -4000) {
          return -4000;
        } else if (temp > 8500) {
          return 8500;
        } 
        return temp; 
    }

    int32_t ConvertPressure2(uint32_t pressure, uint32_t temperature)
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

int32_t ConvertTemperature2(uint32_t temperature)
{

    // calcualte 1st order pressure and temperature (MS5607 1st order algorithm)
    int32_t T2 = 0;
    const int32_t dT    = temperature - (int32_t)(coefficients_[4]) * 256;                     // difference between actual and reference temperature
    const int32_t temp1  = (int32_t)(2000 + ((int64_t)dT * (int64_t)coefficients_[5]) / pow(2, 23)) ;      // actual temperature

    if (temp1 < 2000) {
        T2 = (int32_t)(pow(dT, 2) / pow(2, 31));
    }

    if (temp1 - T2 < -4000) {
      return -4000;
    } else if (temp1 - T2 > 8500) {
      return 8500;
    } 
    return temp1 - T2; 
}

};

} // namespace Intersema
#endif



