
int serial_buffer_len = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Serial started!");
}

void loop() {
  // put your main code here, to run repeatedly:
  serial_buffer_len = Serial.available();

  if(serial_buffer_len > 5) {
    serial_buffer_len = 5;
  }
  
  if(serial_buffer_len > 0) {
    char serial_buffer[serial_buffer_len];
    Serial.readBytes(serial_buffer, serial_buffer_len);
    Serial.print(serial_buffer);
  }

  delay(1000);
}
