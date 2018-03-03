#include <Servo.h>

const int servo1_pin = 2;
const int servo2_pin = 3;
const int servo_enable_pin = 6;

const int servo_min = 45;
const int servo_max = 165;

Servo servo1;
Servo servo2;

// Protocol for using servos.
// Order of execution:
// 1) enableServos();
// 2) servo_action
// 3) disableServos(); //after some timeout

void setup() {
  // Power the servos by pulling the fet's gate high
  pinMode(servo_enable_pin, OUTPUT);
  delay(100);

  // Do some servo stuff
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);

  enable_servos();
  fully_retract_servos();
  disable_servos();
}

void loop() {

  enable_servos();
  
  // Start heading towards the maximum position
  kinda_extend_servos();

  // Disable the servos
  disable_servos();

  delay(5000);

  enable_servos();

  delay(5000);

  // Hipster version of while(true) {}
  for(;;) {}
}

void enable_servos() {
  digitalWrite(servo_enable_pin, HIGH);
}

void disable_servos() {
  digitalWrite(servo_enable_pin, LOW);
}

void kinda_extend_servos() {
  servo1.write(servo_max);
  servo2.write(servo_max);
  delay(5000);
}

void fully_retract_servos() {
servo1.write(servo_min);
  servo2.write(servo_min);

  // Wait for full retraction
  delay(9000);
}

