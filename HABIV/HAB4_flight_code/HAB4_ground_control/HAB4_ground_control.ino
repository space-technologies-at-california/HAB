/* Input-side (button) Arduino code */
#define SENSITIVITY 15 //sensitivity of the controls. ie, if you give the control to move
int command = 0;
int outByte = 0;
// does release from serial on computer, then picks which test flight we want to do.


void setup()
{
  Serial.begin(9600);
  // Baud rate MUST match XBee settings (as set in XCTU)
}
byte makeCommand(int l, int r) {
  return byte(((l + 8) << 4) | (r + 8));
}
bool up = true;
void loop()
{
   if (Serial.available()) {
    command = Serial.read();
    if (command == 'r') {
      Serial.write(makeCommand(-8, 1)); // reset
    } else if (command == 'n') { // any test :)
      int testAngleL = 15 / 15;
      int testAngleR = 0 / 15;
      Serial.write(makeCommand(testAngleL, testAngleR));
     }
   }
}
