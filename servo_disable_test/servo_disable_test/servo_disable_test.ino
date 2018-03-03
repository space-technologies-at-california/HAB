#include <Servo.h>

const int servo1_pin = 2;
const int servo2_pin = 3;
const int servo_enable_pin = 13;

const int servo_min = 45;
const int servo_max = 165;

Servo servo1;
Servo servo2;

void setup() {
  // Power the servos by pulling the fet's gate high
  pinMode(servo_enable_pin, OUTPUT);
  digitalWrite(servo_enable_pin, HIGH);
  delay(100);

  // Do some servo stuff
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);

  servo1.write(servo_min);
  servo2.write(servo_min);

}

void loop() {
  // Wait for full retraction
  delay(10000);

  // Start heading towards the maximum position
  servo1.write(servo_max);
  servo2.write(servo_max);
  delay(1500);

  // Disable the servos
  digitalWrite(servo_enable_pin, LOW);

  // Hipster version of while(true) {}
  for(;;) {}
}
