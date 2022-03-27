import math
import threading
from threading import Timer
import time


class WatchDog(Exception):  # Handles exceptions if certain parts of the code take too long to run
    def __init__(self, period, userHandle):
        self.period = period
        self.handler = userHandle
        self.timer = Timer(self.period, self.handler)

    def reset(self):
        self.timer.cancel()
        self.timer = Timer(self.period, self.handler)

    def stop(self):
        self.timer.cancel()

    def start(self):
        self.timer.start()


class HABVehicle:
    def __init__(self, pid=None, gps=None, servo: []=None, rockblock=None, imu_internal=None, time_interval=10):
        self.postion = {}  # time: (lat, long)
        self.current_heading = 0.0
        self.servo_pos = 0.0
        self.pid = pid
        self.gps = gps
        self.rockblock = rockblock
        self.sevo1 = servo[0]
        #self.servo2 = servo[1]
        #self.timer = WatchDog(time_interval, self.get_imu)
        self.timer = Timer(time_interval, self.get_imu)
        self.data_history = {}
        self.imu = imu_internal

    def update_heading(self, heading):
        self.current_heading = heading

    def get_internal_status(self):  # Method to constantly check that the components are in working order
        pass

    def get_heading(self):
        print("Reading Heading...")
        return gps.read()
    

    def get_current_time(self):
        print("TIME:", time.time())
        return time.time()

    def get_imu(self):
        print("Reading IMU...")
        self.imu.read()
        self.timer.cancel()
        return

    def checkStability(self):
        if gps.altitude < 50feet:
            return False
        elif imu.read_accel_data()[0] < 0:
            return False
        for elem in imu.read_accel_data():
            if elem > :
                return False
        for elem in imu.read_gyro_data():
            if elem > :
                return False
        for elem in imu.read().get('tb'):
            if elem > :
                return False
    
    def adjustStability(self):
        if gps.altitude < 50feet:
            servo1.setServo(1.5)
            servo2.setServo(-1.5)
        elif imu.read_accel_data()[0] < 0:
            servo1.setServo(servo1.duty - 0.000868)
            servo2.setServo(servo2.duty + 0.000868)
        for elem in imu.read_accel_data():
            if elem > :
                return False
        for elem in imu.read_gyro_data():
            if elem > :
                return False
        for elem in imu.read().get('tb'):
            if elem > :
                return False

    def get_current_position(self):
        pass

    def get_velocity(self):
        pass

    def fetch_data(self, num_data_soruce):  # Gets all the required data to send over via RockBlock
        new_data = []
        status = [0 for i in range(num_data_soruce)]  # 1 is success, 0 is fail
        gps_data = self.gps.fetch()  # Have a function in GPS method that can fetch data
        new_data.append(gps_data)

    def send_data(self):
        self.fetch_data()
        x = 1
        package_success = False
        while not package_success:
            try:
                self.rockblock.package_data()
                package_success = True
            except:
                print("Unable to Package data! Tried {x} times!")
                
                
    
    
    
    
    

    '''def get_heading(self, time_now, time_prev):
        current_lat = self.postion[time_now][0]
        current_long = self.postion[time_now][1]

        prev_lat = self.postion[time_prev][0]
        prev_long = self.postion[time_prev][1]

        x = math.cos(current_lat) * math.sin(current_long - prev_long)
        y = math.cos(prev_lat) * math.sin(current_lat) - math.sin(prev_lat)*math.cos(current_lat)*math.cos(current_long - prev_long)

        return math.atan2(x, y)
        '''
