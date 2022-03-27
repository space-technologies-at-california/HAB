import struct
from servo_control import HabServo
#from pid import PID
from rockblock_v2 import HAB_rock
import servo_control
import time, threading
from state import HABVehicle
import internal_sensors
from gps import HAB_gps
from internal_sensors import HAB_IMU_Temp
import math

# Global Variables / datastructures

# PID Coefficients
kP = 0  # update
kI = 0  # update
kD = 0  # update
PID_FREQ = 0.0  # update

# Controls
USE_XBEE = True

# XBEE
XBEE_FREQ = 0.0
XBEE_timer = None


print("HERE!")

print("Initializing Vehicle...")
current_time = time.time()
SERVO1 = HabServo(1.35, 50, 0)
SERVO2 = HabServo(-1.35, 50, 0)
GPS = HAB_gps()
print("GPS Initialized")
IMU = HAB_IMU_Temp()
print("IMU Initialized")
Rock_BLOCK = HAB_rock('/dev/ttyUSB0')
print("Rockblock Initialized")

destination =  0 # GPS coordinates for destination
MAX_TURN = 0.0052

if USE_XBEE:
    #XBEE_timer = threading.Timer(XBEE_FREQ, xbee.update)
    BALLOON = HABVehicle(imu_internal=IMU, gps=GPS, rockblock=HAB_rock)
#else:
    #PID_controller = PID(kP, kI, kD, interval=1/PID_FREQ)
    #BALLOON = VehicleState(PID_controller, GPS, SERVO)

print("Vehicle Initialized successfully!")


def _toRad(meas):
    return meas * math.pi / 180

def _toDeg(meas):
    return meas * 180 / math.pi

def adjustStability(self):


def main(veh):
    """
    if USE_XBEE:
        XBEE_timer.start()

    else:
        PID_timer.start()
    """
    pos = GPS.read()
    heading = IMU.read().get('head')
    tolerance = math.pi / 18

    dLon = _toRad(destination.lon-pos.lon)
    y = math.sin(dLon) * math.cos(_toRad(destination.lat))
    x = math.cos(_toRad(pos.lat))*math.sin(_toRad(destination.lat)) - math.sin(_toRad(pos.lat))*math.cos(_toRad(destination.lat))*math.cos(dLon)
    brng = _toDeg(math.atan2(y, x))
    brng = ((brng + 360) % 360)
    state = veh.get_imu()
    veh.get_current_time()
    while abs(brng - heading) > tolerance:
        if brng - heading > 0:
            if veh.checkStability():
                error = (brng - heading) / abs(brng - heading) * max(brng - heading - 10, 0)
                servo_adjustment = error * veh.pid.kP # KP is the proportional
                assigned_angle += min(servo_adjustment, MAX_TURN)
                SERVO2.setServo(assigned_angle)
        else:
            if veh.checkStability():
                error = (brng - heading) / abs(brng - heading) * max(brng - heading - 10, 0)
                servo_adjustment = error * veh.pid.kP # KP is the proportional
                assigned_angle += min(servo_adjustment, MAX_TURN)
                SERVO1.setServo(0-assigned_angle)
        if not veh.checkStability():
            adjustStability()
        time.sleep(300)
        heading = IMU.read().get('head')

    


# while True:
#     loop()

main(BALLOON)