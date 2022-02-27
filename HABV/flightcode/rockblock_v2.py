import time
import struct
#import board
from adafruit_rockblock import RockBlock
import serial


class HAB_rock:
    def __init__(self, port):
        self.uart = serial.Serial(port)  #VIA USB
        self.rb = RockBlock(self.uart)
        print("Rockblock init")

    def read_port(self):
        print(self.uart.read())

    def package_data(self, GPS=None, Acc=None, Temp=None, Baro=None, Gyro=None, Battery=None):  # creates a packet of data to be sent
        # create binary data
        # decode on other end with struct.unpack("<6fB5f", data)
        # formating is dependent on the datatype and number of datapoints
        # https://docs.python.org/3/library/struct.html#format-characters
        print("Creating Binary Data...")
        data = struct.pack("f", GPS[0])  # Latitude
        data += struct.pack("f", GPS[1])  # Longitude

        #print(f"DATA: {GPS[0]}, {GPS[1]}")
        #print(f"BINARY: {data}, SIZE: {len(data)}")

        # put data in outbound buffer
        self.rb.data_out = data

    def send_data(self):
        # try a satellite Short Burst Data transfer
        print("Talking to satellite...")
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
#testing = HAB_rock('/dev/ttyUSB0')
#i = (2112.0, 4134314.3)
#ft = 42.123456789
#testing.package_data(i,ft)
#testing.send_data()



