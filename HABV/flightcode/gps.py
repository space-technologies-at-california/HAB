from ublox_gps import UbloxGps
import serial

port = serial.Serial('/dev/serial0', baudrate=19200, timeout=1)
gps = UbloxGps(port)

class HAB_gps:
    def __init__(self, port_name):
        port = serial.Serial(f'/dev/{port_name}', baudrate=19200, timeout=1)
        gps = UbloxGps(port)

    def read(self):
        coords = gps.geo_coords()
        print(coords.lon, coords.lat)
        return coords


def run():
    try:
        print("Listenting for UBX Messages.")
        while True:
            try:
                coords = gps.geo_coords()
                print(coords.lon, coords.lat)
            except (ValueError, IOError) as err:
                print(err)

    finally:
        port.close()


if __name__ == '__main__':
    run()