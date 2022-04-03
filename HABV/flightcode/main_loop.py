import struct
from servo_control import HabServo
from pid import PID
from rockblock_v2 import HAB_rock
import servo_control
import time, threading
from state import HABVehicle
import internal_sensors
from gps import HAB_gps
from gps import location
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
controller = PID(kP, kI, kD, time.time())

destination =  location(0, 0) # GPS coordinates for destination
MAX_TURN = 0.0052

if USE_XBEE:
    #XBEE_timer = threading.Timer(XBEE_FREQ, xbee.update)
    BALLOON = HABVehicle(imu_internal=IMU, gps=GPS, rockblock=HAB_rock, servo=[SERVO1, SERVO2], pid = controller)
#else:
    #PID_controller = PID(kP, kI, kD, interval=1/PID_FREQ)
    #BALLOON = VehicleState(PID_controller, GPS, SERVO)

print("Vehicle Initialized successfully!")


def _toRad(meas):
    return meas * math.pi / 180

def _toDeg(meas):
    return meas * 180 / math.pi

def desiredHeading(self, curr_pos):
    dLon = _toRad(destination.getLong()-curr_pos.lon)
    y = math.sin(dLon) * math.cos(_toRad(destination.getLat()))
    x = math.cos(_toRad(curr_pos.lat))*math.sin(_toRad(destination.getLat())) - math.sin(_toRad(curr_pos.lat))*math.cos(_toRad(destination.getLat()))*math.cos(dLon)
    brng = _toDeg(math.atan2(y, x))
    brng = ((brng + 360) % 360)
    return brng


def main(veh):
    """
    if USE_XBEE:
        XBEE_timer.start()

    else:
        PID_timer.start()
    """
    pos = GPS.read()
    heading = IMU.read_data().get('head')
    tolerance = math.pi / 18
    brng = desiredHeading(pos)
    state = veh.get_imu()
    veh.get_current_time()
    assigned_angle2 = 1.35
    assigned_angle1 = 1.35
    while abs(brng - heading) > tolerance:
        if brng - heading > 0:
            if veh.checkStability(state):
                servo_adjustment = controller.PID_adjust(controller.P_update(brng, heading, heading - 10, time.time()))
                assigned_angle2 -= min(servo_adjustment, MAX_TURN)
                SERVO2.setServo(assigned_angle2)
        else:
            if veh.checkStability(state):
                servo_adjustment = controller.PID_adjust(controller.P_update(brng, heading, heading - 10, time.time()))
                assigned_angle1 -= min(servo_adjustment, MAX_TURN)
                SERVO1.setServo(0-assigned_angle1)
        while not veh.checkStability(state):
            veh.adjustStability()
        time.sleep(300)
        heading = IMU.read_data().get('head')
        brng = desiredHeading(GPS.read())

    


# while True:
#     loop()

main(BALLOON)