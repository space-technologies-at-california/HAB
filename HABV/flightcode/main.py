from flightcode.servo_control import HabServo
import pid
import rockblock_v2
import servo_control
import time, threading

# Global Variables / datastructures


# PID Coefficients
kP = 0 # update
kI = 0 # update
kD = 0 # update
PID_controller = None
PID_FREQ = 0.0
PID_timer = None

# Servos
Servo_1 = None
Servo_2 = None

# RockBLOCK
Rock_BLOCK = None

# Controls
USE_XBEE = False
timer = None

servo_output = 0

# XBEE
XBEE_FREQ = 0.0
XBEE_timer = None

def init():

    if USE_XBEE:
        XBEE_timer = threading.Timer(XBEE_FREQ, xbee.update)
    else:
        PID_controller = pid.PID(kP, kI, kD)
        PID_timer = threading.Timer(PID_FREQ, pid.update)

    
    Servo_1 = HabServo()
    Servo_2 = HabServo()

    Servo_timer = threading.Timer(Serv, pid.update)

    Rock_BLOCK = rockblock_v2.RockTest()


def main():

    if USE_XBEE:
        XBEE_timer.start()

    else:
        PID_timer.start()

    Rock_BLOCK.send_data(0) # update


init()

# while True:
#     loop()

main()

