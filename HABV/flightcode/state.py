import math
import threading
import time


class VehicleState:
    def __init__(self, pid, gps, servo, time_interval=100):
        self.postion = {}  # time: (lat, long)
        self.time = time.time()
        self.servo_pos = 0.0
        self.pid = pid
        self.gps = gps
        self.sevo = servo
        self.timer = threading.Timer(time_interval)

    def update(self):
        pass

    def get_heading(self):
        current_lat
        y =
        return math.atan2(x,y)

    def get_current_position(self):
        pass

    def get_velocity(self):
        pass

    def get_angle(self):
        pass