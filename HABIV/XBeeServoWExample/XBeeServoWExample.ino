/* Input-side (button) Arduino code */
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
#include "SoftwareSerial.h"

#include <Servo.h>
Servo servoR;
Servo servoL;

#define servoPinL 8 //CHANGE!
#define servoPinR 9 //CHANGE!
#define SENSITIVITY 15 //sensitivity of the controls. ie, if you give the control to move

SoftwareSerial XBee(2, 3);

byte inByte = 0;
int angleR = 0; //global variable for what the right servo's angle is
int angleL = 0;

bool getXBeeControl() { //returns if the parachute should be dropped.
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

void setup()
{
  servoR.attach(servoPinR);
  servoL.attach(servoPinL);
  Serial.begin(9600);
  XBee.begin(9600);
  //Serial.write("setting up Servo");
  servoR.write(0);
  servoL.write(0);
  
  delay(1000);
  // Baud rate MUST match XBee settings (as set in XCTU)
}



void loop()
{
  if (XBee.available() > 0)
  {
    getXBeeControl();
    servoR.write(angleR);
    servoL.write(angleL);
  }
}
