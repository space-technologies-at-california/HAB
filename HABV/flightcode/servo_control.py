#!/usr/bin/env python3
import threading
import time, math
import rcpy
import rcpy.servo as servo
import rcpy.clock as clock

'''
Args are:
duty      define a duty cycle from -1.5 to 1.5
servo     specify a single servo from 1-8, 0 for all servos
sweep     sweep servos back and forward at duty cycle
period    period
'''


class HabServo:
    def __init__(self, rotations, frequency, channel, sweep=False, brk=False, free=False, update_interval=100):

        self.duty = rotations*3/8 - 1.5
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
        self.timer = threading.Timer(update_interval)

    def servo_sweep(self, direction, d=0):
        # keep running
        while rcpy.get_state() != rcpy.EXITING:

            # increment duty
            d = d + direction * self.delta

            # end of range?
            self.duty = math.fabs(self.duty)
            if d > self.duty:
                d = self.duty
                direction = direction * -1
            elif d < -self.duty:
                d = -self.duty
                direction = direction * -1

            self.internal.set(d)
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
                self.servo_sweep(direction)
            else:
                # keep running
                while rcpy.get_state() != rcpy.EXITING:
                    time.sleep(1)

        except KeyboardInterrupt:
            # stop clock
            self.clck.stop()

            # disable servos
            servo.disable()

        finally:

            # stop clock
            self.clck.stop()

            # disable servos
            servo.disable()

            # say bye
            print("\nBye Beaglebone!")
