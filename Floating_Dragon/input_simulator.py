import time
import math
import numpy as np
from matplotlib import pyplot as plt
from pid import PID


class Simulator:
    def __init__(self, slat, slong, endlat, endlong, launch_alt, end_alt, pid_lst, traj, env=None):  # pid_lst is [P,I,D]
        self.state = {"timestep": [0], "position": [[slat, slong, launch_alt]], "servo": [[0.0, 0.0]]} # for servo negative means pull, positive means extend
        self.end = np.asarray([endlat, endlong, end_alt])
        self.env = env
        self.world_timer = None
        self.controller = PID(pid_lst[0], pid_lst[1], pid_lst[2])  # 2D PID Controller
        self.planner = traj

    def start(self, csv=None):
        if self.world_timer is None:
            self.world_timer = 0
        self.run(csv)

    def announce(self):
        print(f"============ Time: {self.world_timer} =================")
        print(f"Currently at {self.current}. Servo position is {self.servo_pos}")
        #print(f"Flight params -> pitch:{self.pitch}, yaw:{self.yaw}, roll:{self.roll}")
        print(f"Distance to target: {self.dist_to_target()}")
        print("============== end ======================================")

    def course_deviation(self):
        # Positive value is clockwise turn (right turn), negative value is left turn
        course_vec = np.asarray([self.end[0] - self.current[0], self.end[1] - self.current[1]])
        dir_vec = self.dir_vec
        det = np.linalg.det(np.column_stack((course_vec, dir_vec)))
        dot = np.dot(course_vec, dir_vec)
        out = math.atan2(det, dot)

        return (out / (2 * math.pi)) * 360

    def dist_to_target(self):
        return round(math.sqrt(pow(self.current[0] - self.end[0], 2) + pow(self.current[1] - self.end[1], 2)), 2)

    def rotate(self, vector, angle):
        # Rotates a vector in the clockwise direction by angle in degrees
        angle = (angle / 360) * 2 * math.pi
        newX = vector[0] * math.cos(-angle) - vector[1] * math.sin(-angle)
        newY = vector[0] * math.sin(-angle) + vector[1] * math.cos(-angle)
        return [round(newX, 3), round(newY, 3)]

    def sigmoid(self, x, c1=1.2, c2=1):
        # Get an output given a input. c1 and c2 are tunable hyper-parameters. c2 is midpoint.
        # Y range is from -1 to 1 which is percentage of servo input
        y = ((2 / (1 + math.exp(-c1 * (x - c2)))) - 0.53788) / 1.462
        return y

    def error(self, deviation):
        err = 6 * math.tanh(0.5 * deviation * 0.0025 * deviation)
        return err

    def transfer_function(self, deviation):
        # Get a servo input given an error in heading.
        output = self.sigmoid(self.error(deviation))
        return round(output, 2)

    def plot_transfer(self):
        points = [(x, self.transfer_function(x)) for x in range(0,90)]
        zip_pts = zip(*points)
        plt.plot(*zip_pts)
        plt.show()

    def servo_movement(self, rotations, max_rot=3, pulley_radius=10, canopy_length=150):
        # all measurements are in cm
        if abs(rotations) > max_rot:
            if rotations < 0:
                rotations = -max_rot
            else:
                rotations = max_rot
        dist = math.pi * 2 * pulley_radius/100 * rotations
        angle = math.acos(1-(pow(dist,2)/(2*pow(canopy_length/100, 2)))) * 8

        return angle

    def update(self):
        pass

    def plot_movement(self):
        pass

    def read_gps(self):
        return self.state.get("position")[-1]  # reads the last entry

    def update_state(self, timestep, gps_coor, servo_pos):
        self.state.get("position").append(gps_coor)
        self.state.get("timestep").append(timestep)
        self.state.get("servo").append(servo_pos)

    def run(self, csv):
        if csv is None:  # add some csv functionality later
            pass

        gps_vec = self.read_gps()

        target, current = self.planner.update(gps_vec)

        self.controller.clear()
        self.controller.set(target)
        self.controller.update(current)

        servo_input = self.controller.out()

        turn_left = 1

        if turn_left:
            servo_pos = [-servo_input, servo_input]
        else:
            servo_pos = [servo_input, -servo_input]


        delta_movement = self.sigmoid(servo_input)

        if self.env is not None:
            delta_movement = delta_movement + self.env.get()  # assumes that env has a way to get disturbance

        self.update_state(self.world_timer+1, gps_vec+delta_movement)


"""
sim = Simulator(0,0,100,100,10, [1.0,1.0])
exit()
print(sim.course_deviation([0,0]))
print(sim.dist_to_target())
sim.plot_transfer()
"""
