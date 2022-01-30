import time
import struct
#import board
from adafruit_rockblock import RockBlock
import serial


class RockTest:
    def __init__(self, port):
        self.uart = serial.Serial(port)  #VIA USB
        self.rb = RockBlock(self.uart)

    def read_port(self):
        print(self.uart.read())

    def send_data(self, some_int, some_float):
        # create binary data
        # decode on other end with struct.unpack("<6fB5f", data)
        # formating is dependent on the datatype and number of datapoints
        # https://docs.python.org/3/library/struct.html#format-characters
        print("Creating Binary Data...")
        data = struct.pack("i", some_int)
        data += struct.pack("f", some_float)

        print(f"DATA: {some_int}, {some_float}")
        print(f"BINARY: {data}, SIZE: {len(data)}")

        # put data in outbound buffer
        self.rb.data_out = data

        # try a satellite Short Burst Data transfer
        print("Talking to satellite...")
        status = self.rb.satellite_transfer()
        # loop as needed
        retry = 0
        while status[0] > 8:
            if retry > 50:
                print(f"Cannot Connect to Network! Tried {retry} times!")
                break
            time.sleep(10)
            status = self.rb.satellite_transfer()
            print(retry, status)
            retry += 1

        print("\nDONE.")


testing = RockTest('COM3')
i = 2112
ft = 42.123456789
testing.send_data(i,ft)