from flightcode.servo_control import HabServo
import pid
import rockblock_v2
import servo_control

# Global Variables / datastructures


# PID Coefficients
kP = 0 # update
kI = 0 # update
kD = 0 # update

PID_controller = None
Servo_1 = None
Servo_2 = None

def init():
    PID_controller = pid.PID(kP, kI, kD)
    Servo_1 = HabServo()
    Servo_2 = HabServo()


def loop():
    pass


init()

while True:
    loop()




