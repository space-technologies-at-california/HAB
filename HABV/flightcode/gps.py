from ublox_gps import UbloxGps
import serial

port = serial.Serial('/dev/ttyACM0', baudrate=19200, timeout=1)
gps = UbloxGps(port)

class HAB_gps:
    def __init__(self, port_name='/dev/ttyACM0'):
        port = serial.Serial(port_name, baudrate=19200, timeout=1)
        gps = UbloxGps(port)

    def read(self):
        coords = gps.geo_coords()
        print(coords.lon, coords.lat)
        return coords
    
class location:
    def __init__(self, long, lat):
        self.coord = [long, lat]

    def getLong(self):
        return self.coord[0]

    def getLat(self):
        return self.coord[1]

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

'''
