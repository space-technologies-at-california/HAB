import time

# import rcpy library
# This automatically initizalizes the robotics cape
import rcpy
import rcpy.mpu9250 as mpu9250


rcpy.set_state(rcpy.RUNNING)


class HAB_IMU_Temp:
    def __init__(self):
        mpu9250.initialize(enable_magnetometer = True)
        print("Press Ctrl-C to exit")

        # header
        print("   Accel XYZ (m/s^2) |"
              "    Gyro XYZ (deg/s) |", end='')
        print("  Mag Field XYZ (uT) |", end='')
        print(' Temp (C)')

    def read(self):
        try:    # keep running
            while True:
                if rcpy.get_state() == rcpy.RUNNING:
                    temp = mpu9250.read_imu_temp()
                    data = mpu9250.read()
                    print(('\r{0[0]:6.2f} {0[1]:6.2f} {0[2]:6.2f} |'
                           '{1[0]:6.1f} {1[1]:6.1f} {1[2]:6.1f} |'
                           '{2[0]:6.1f} {2[1]:6.1f} {2[2]:6.1f} |'
                           '   {3:6.1f}').format(data['accel'],
                                                 data['gyro'],
                                                 data['mag'],
                                                 temp), end='')

                return data
        except KeyboardInterrupt:
            # Catch Ctrl-C
            pass

        finally:
            print("\nBye BeagleBone!")


class HAB_Baro:
    def __init__(self):
        pass

    def read(self):
        pass
