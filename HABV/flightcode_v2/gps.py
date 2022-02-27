from ublox_gps import UbloxGps
import serial

#port = serial.Serial('/dev/serial0', baudrate=19200, timeout=1)

class HAB_gps:
    def __init__(self, port_name='/dev/ttyACM0'):
        self.port = serial.Serial(port_name, baudrate=19200, timeout=1)
        self.gps = UbloxGps(self.port)

    def read(self):
        coords = self.gps.geo_coords()
        print(coords.lon, coords.lat)
        return coords


'''
def run():
    try:
        print("Listenting for UBX Messages.")
        while True:
            try:
                coords = gps.geo_coords()
                print("Coords", coords.lon, coords.lat, coords.headMot, coords)
            except (ValueError, IOError) as err:
                print(err)

    finally:
        port.close()


if __name__ == '__main__':
    run()

#added this locally
'''