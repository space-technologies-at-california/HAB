#!/usr/bin/env python3
# import python libraries
import time, math
import getopt, sys

# import rcpy library
# This automatically initizalizes the robotics cape
import rcpy
import rcpy.servo as servo
import rcpy.clock as clock

'''
def usage():
    print("""usage: python rcpy_test_servos [options] ...
Options are:
-d duty     define a duty cycle from -1.5 to 1.5
-c servo    specify a single servo from 1-8, 0 for all servos
-s          sweep servos back and forward at duty cycle
-t period   period
-h          print this help message""")
'''


class HabServo:
    def __init__(self, duty, frequency, channel, sweep=False, brk=False, free=False):
        self.duty = math.fabs(duty)  # calculate frequency to duty
        self.period = 1/frequency
        self.channel = channel
        self.sweep = sweep
        self.brk = brk
        self.free = free

        # set state to rcpy.RUNNING
        rcpy.set_state(rcpy.RUNNING)

        # set servo duty (only one option at a time)
        self.internal = servo.Servo(self.channel)
        self.clck = clock.Clock(self.internal, self.period)
        self.delta = self.duty/100

    def servo_sweep(self, direction, delta, d=0):
        # keep running
        while rcpy.get_state() != rcpy.EXITING:

            # increment duty
            d = d + direction * delta

            # end of range?
            if d > self.duty:
                d = self.duty
                direction = direction * -1
            elif d < -self.duty:
                d = -self.duty
                direction = direction * -1

            self.internal.set(d)

            # sleep some
            time.sleep(.02)

    def run(self, direction):
        if self.duty != 0:
            if not self.sweep:
                print('Setting servo {} to {} duty'.format(self.channel, self.duty))
                self.internal.set(self.duty)
            else:
                print('Sweeping servo {} to {} duty'.format(self.channel, self.duty))
        else:
            self.sweep = False

        try:
            # enable servos
            servo.enable()

            # start clock
            self.clck.start()

            # sweep
            if self.sweep:
                self.servo_sweep(direction, self.delta)
            # or do nothing
            else:
                # keep running
                while rcpy.get_state() != rcpy.EXITING:
                    # sleep some
                    time.sleep(1)

        except KeyboardInterrupt:
            # handle what to do when Ctrl-C was pressed
            pass

        finally:

            # stop clock
            self.clck.stop()

            # disable servos
            servo.disable()

            # say bye
            print("\nBye Beaglebone!")


test_servo = HabServo(1.5, 50, 8)
test_servo.run(1)