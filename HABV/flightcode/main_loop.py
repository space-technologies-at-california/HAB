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
#SERVO1 = HabServo(1.5, 50, 0)
#SERVO2 = HabServo(1.5, 50, 0)
GPS = HAB_gps()
print("GPS Initialized")
IMU = HAB_IMU_Temp()
print("IMU Initialized")
Rock_BLOCK = HAB_rock('/dev/ttyUSB0')
print("Rockblock Initialized")

if USE_XBEE:
    #XBEE_timer = threading.Timer(XBEE_FREQ, xbee.update)
    BALLOON = HABVehicle(imu_internal=IMU, gps=GPS, rockblock=HAB_rock)
#else:
    #PID_controller = PID(kP, kI, kD, interval=1/PID_FREQ)
    #BALLOON = VehicleState(PID_controller, GPS, SERVO)

print("Vehicle Initialized successfully!")


def main(veh):
    """
    if USE_XBEE:
        XBEE_timer.start()

    else:
        PID_timer.start()
    """
    heading = veh.get_imu()
    veh.get_current_time()
    


# while True:
#     loop()

main(BALLOON)