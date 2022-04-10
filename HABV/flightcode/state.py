import math
import threading
from threading import Timer
import time
from pid import PID


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
    MIN_ALT = 2 #km
    MAXFWD_ACCEL = 0
    MAXDWN_ACCEL = 0
    MAXLR_ACCEL = 0
    MAXFWD_ANGVEL = 0
    MAXDWN_ANGVEL = 0
    MAXLR_ANGVEL = 0
    MAX_PITCH = 0
    MAX_ROLL = 0
    MAX_YAW = 0
    MAX_TURN = 0.0052

    def __init__(self, pid=None, gps=None, servo = [], rockblock=None, imu_internal=None, time_interval=10):
        self.postion = {}  # time: (lat, long)
        self.current_heading = 0.0
        self.servo_pos = 0.0
        self.pid = pid
        self.gps = gps
        self.rockblock = rockblock
        self.servo1 = servo[0]
        self.servo2 = servo[1]
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
        return self.gps.read()
    

    def get_current_time(self):
        print("TIME:", time.time())
        return time.time()

    def get_imu(self):
        print("Reading IMU...")
        self.imu.read()
        self.timer.cancel()
        return self.imu.read_data()

    def checkStability(self):
        if (self.rockblock.geolocation()[0] - 6376) < self.MIN_ALT:
            return False
        elif self.imu.read_accel_data()[0] < 0:
            return False
        if self.imu.read_accel_data()[0] > self.MAXFWD_ACCEL:
            return False
        if self.imu.read_accel_data()[1] > self.MAXLR_ACCEL:
            return False
        if self.imu.read_accel_data()[2] > self.MAXDWN_ACCEL:
            return False
        if self.imu.read_gyro_data()[0] > self.MAXFWD_ANGVEL:
            return False
        if self.imu.read_gyro_data()[1] > self.MAXLR_ANGVEL:
            return False
        if self.imu.read_gyro_data()[2] > self.MAXDWN_ANGVEL:
            return False
        if self.imu.read().get('tb')[0] > self.MAX_PITCH:
            return False
        if self.imu.read().get('tb')[1] > self.MAX_ROLL:
            return False
        if self.imu.read().get('tb')[2] > self.MAX_YAW:
            return False
    
    def adjustStability(self):
        assigned_angle2 = self.servo2.duty
        assigned_angle1 = self.servo1.duty
        while not self.checkStability():
            if (self.rockblock.geolocation()[0] - 6376) < self.MIN_ALT:
                self.servo1.setServo(1.5)
                self.servo2.setServo(-1.5)
            elif self.imu.read_accel_data()[0] < 0:
                self.servo1.setServo(self.servo1.duty - 0.000868)
                self.servo2.setServo(self.servo2.duty + 0.000868)
            if self.imu.read_accel_data()[0] > self.MAXFWD_ACCEL:
                self.pid.reset(kP, 0, 0, time.time())
                self.pid.P_update(self.imu.read_accel_data()[0], self.MAXFWD_ACCEL, self.MAXFWD_ACCEL, time.time())
                servo_adjustment = self.pid.PID_adjust(self.MAX_TURN)
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
                time.sleep(10)
            if self.imu.read_accel_data()[1] > self.MAXLR_ACCEL:
                self.pid.reset(kP, 0, 0, time.time())
                self.pid.P_update(self.imu.read_accel_data()[1], self.MAXLR_ACCEL, self.MAXLR_ACCEL, time.time())
                servo_adjustment = self.pid.PID_adjust(self.MAX_TURN)
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
                time.sleep(10)
            if self.imu.read_accel_data()[2] > self.MAXDWN_ACCEL:
                self.pid.reset(kP, 0, 0, time.time())
                self.pid.P_update(self.imu.read_accel_data()[2], self.MAXDWN_ACCEL, self.MAXDWN_ACCEL, time.time())
                servo_adjustment = self.pid.PID_adjust(self.MAX_TURN)
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
                time.sleep(10)
            if self.imu.read_gyro_data()[0] > self.MAXFWD_ANGVEL:
                self.pid.reset(kP, 0, 0, time.time())
                self.pid.P_update(self.imu.read_gyro_data()[0], self.MAXFWD_ANGVEL, self.MAXFWD_ANGVEL, time.time())
                servo_adjustment = self.pid.PID_adjust(self.MAX_TURN)
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
                time.sleep(10)
            if self.imu.read_gyro_data()[1] > self.MAXLR_ANGVEL:
                servo_adjustment = self.pid.PID_adjust(self.imu.read_accel_data()[0], self.MAXFWD_ACCEL, self.MAXFWD_ACCEL, time.time())
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
            if self.imu.read_gyro_data()[2] > self.MAXDWN_ANGVEL:
                servo_adjustment = self.pid.PID_adjust(self.imu.read_accel_data()[0], self.MAXFWD_ACCEL, self.MAXFWD_ACCEL, time.time())
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
            if self.imu.read().get('tb')[0] > self.MAX_PITCH:
                self.pid.reset(kP, 0, 0, time.time())
                self.pid.P_update(self.imu.read().get('tb')[0], self.MAX_PITCH, self.MAX_PITCH, time.time())
                servo_adjustment = self.pid.PID_adjust(self.MAX_TURN)
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
                time.sleep(10)
            if self.imu.read().get('tb')[1] > self.MAX_ROLL:
                self.pid.reset(kP, 0, 0, time.time())
                self.pid.P_update(self.imu.read().get('tb')[1], self.MAX_ROLL, self.MAX_ROLL, time.time())
                servo_adjustment = self.pid.PID_adjust(self.MAX_TURN)
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
                time.sleep(10)
            if self.imu.read().get('tb')[2] > self.MAX_YAW:
                self.pid.reset(kP, 0, 0, time.time())
                self.pid.P_update(self.imu.read().get('tb')[2], self.MAX_YAW, self.MAX_YAW, time.time())
                servo_adjustment = self.pid.PID_adjust(self.MAX_TURN)
                assigned_angle1 += min(servo_adjustment, self.MAX_TURN)
                assigned_angle2 -= min(servo_adjustment, self.MAX_TURN)
                self.servo2.setServo(assigned_angle2)
                self.servo1.setServo(assigned_angle1)
                time.sleep(10)

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
