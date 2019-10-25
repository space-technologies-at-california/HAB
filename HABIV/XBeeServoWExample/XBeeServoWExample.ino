/* Input-side (button) Arduino code */
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
#include "SoftwareSerial.h"

#include <Servo.h>
Servo servoR;

SoftwareSerial mySerial(2, 3);

byte inByte = 0;
int outByte = 0;

void setup()
{
  servoR.attach(6);
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.write("setting up Servo");
  servoR.write(0);
  // Baud rate MUST match XBee settings (as set in XCTU)
}

void loop()
{
  if (mySerial.available() > 0)
  {
    inByte = mySerial.read();
    Serial.write(inByte);
    servoR.write(inByte);
  }
}
