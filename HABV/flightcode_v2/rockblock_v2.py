import time
import struct
##import board
from adafruit_rockblock import RockBlock
import serial
import sys


class HAB_rock:
    def __init__(self, port='/dev/ttyUSB0'):
        self.port = port
        self.uart = serial.Serial(self.port)  #VIA USB
        self.rb= RockBlock(self.uart)

    def read_port(self):
        print(self.uart.read())

    def package_data(self, GPS=None, Acc=None, Temp=None, Baro=None, Gyro=None, Battery=None):  # creates a packet of data to be sent
        # create binary data
        # decode on other end with struct.unpack("<6fB5f", data)
        # formating is dependent on the datatype and number of datapoints
        # https://docs.python.org/3/library/struct.html#format-characters
        #print("Creating Binary Data...")
        #data = struct.pack("f", GPS[0])  # Latitude
        #data += struct.pack("f", GPS[1])  # Longitude

        #print(f"DATA: {GPS[0]}, {GPS[1]}")
        #print(f"BINARY: {data}, SIZE: {len(data)}")

        # put data in outbound buffer
        print("BEFORE", GPS[0], GPS[1])
        string =  str(GPS[0]) + "|" + str(GPS[1])
        #string = 'Hello'
        print("AFTER", string)
        sys.exit()
        self.rb.text_out = string

    def send_data(self):
        # try a satellite Short Burst Data transfer
        print("Talking to satellite...")
        #self.rb.text_out = "Hello from HAB"
        status = self.rb.satellite_transfer()
        # loop as needed
        retry = 0
        while status[0] > 8:
            if retry > 50:
                print("Cannot Connect to Network! Tried", retry, "times!")
                break
            time.sleep(10)
            status = self.rb.satellite_transfer()
            print(retry, status)
            retry += 1

        print("\nDONE.")
        
        
# FOR TESTING PURPOSE
#testing = HAB_rock()
#i = (232.0, 4134314.3)
#ft = 42.123456789
#testing.package_data("Hello Test")
#testing.send_data()



