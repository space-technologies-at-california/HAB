import struct
from servo_control import HabServo
from pid import PID
import rockblock_v2
import servo_control
import time, threading
from state import HABVehicle
import internal_sensors
import gps

# Global Variables / datastructures

# PID Coefficients
kP = 0  # update
kI = 0  # update
kD = 0  # update
PID_FREQ = 0.0  # update

# Controls
USE_XBEE = False

# XBEE
XBEE_FREQ = 0.0
XBEE_timer = None


def init():
    current_time = time.time()
    SERVO = HabServo()
    GPS = GPS()

    if USE_XBEE:
        XBEE_timer = threading.Timer(XBEE_FREQ, xbee.update)
        BALLOON = VehicleState(XBEE_timer, GPS, SERVO)
    else:
        PID_controller = PID(kP, kI, kD, interval=1/PID_FREQ)
        BALLOON = VehicleState(PID_controller, GPS, SERVO)

    Rock_BLOCK = rockblock_v2.RockTest()


def main():
    if USE_XBEE:
        XBEE_timer.start()

    else:
        PID_timer.start()

    Rock_BLOCK.send_data(0)  # update


init()

# while True:
#     loop()

main()

"""
def setmode(rf):  # writitng to pins depends on which lib we are using rcpy?
    digitalWrite(CTR1, LOW)
    digitalWrite(CTR2, LOW)

    if rf == 1:
        digitalWrite(CTR1, HIGH)

    elif rf == 2
        digitalWrite(CTR2, HIGH)

    elif rf == 3
        digitalWrite(CTR1, HIGH)
        digitalWrite(CTR2, HIGH)

def get_all_data():
    gpsData = getGPSData()
    altimeterData = getAltimeterData()
    thermocoupleData = getThermocoupleData()
    rtcData = getRTCData()
    imuData = getIMUData() # True for DPS values
    uvbData = getUVBData()
    return gpsData, altimeterData, thermocoupleData, rtcData, imuData, uvbData

def main():
    all_data = get_all_data()
    write_all_to_SD(all_data)

    # The data will be written to a dataString in this format:
    # <TripNumber>:<Hour>:<Minute>:<FixQuality>:<Speed>:<Angle>:<Lon>:<Lat>:<Altitude>:<ExternalTemp>
    datastring = str("202")
    for i in range(len(all_data)):
        datastring += ':' + str(all_data[i])

"""