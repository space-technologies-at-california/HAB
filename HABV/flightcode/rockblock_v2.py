import time
import struct
import board
import adafruit_rockblock


class RockBlock:
    def __init__(self):
        self.uart = board.UART()
        self.uart.baudrate = 19200
        self.rb = adafruit_rockblock.RockBlock(self.uart)
        self.signal_quality = -1

    def package_data(self, data):
        # data is a list of all different sensor data
        # build data
        # can decode on other end with struct.unpack("<6fB5f", data)
        # formating is dependent on the datatype and number of datapoints
        # https://docs.python.org/3/library/struct.html#format-characters
        data = struct.pack("3f", *accelo.acceleration)
        data += struct.pack("3f", *magno.magnetic)
        data += struct.pack("2f", sht.relative_humidity, sht.temperature)
        data += struct.pack("3f", bmp.pressure, bmp.altitude, bmp.temperature)
        return data

    def send_data(self, data):
        # data here is the packaged binary data
        best_quality = []

        def get_qual():
            return best_quality[0][1]

        def get_ant():
            return best_quality[0][0]

        ''' TO GET BEST ANTENNA
        for i in range(1, 4):
            time.sleep(1000)  # in seconds
            quality = modem.getSignalQuality(-1)
            if not len(best_quality):
                best_quality.append(quality)
            else:
                if quality > get_qual():
                    best_quality = [(i, quality)]
        '''
        self.rb.data_out = data
        print("Talking to satellite...")
        retry = 0
        status = self.rb.satellite_transfer()
        while status[0] > 8:
            time.sleep(10)
            status = self.rb.satellite_transfer()
            print(retry, status)
            retry += 1
        print("\nDONE.")

