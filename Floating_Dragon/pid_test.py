from pid import PID
import time
import matplotlib.pyplot as plt

pid_x = PID(0.6,0,0, setpoint=100, sample_time=1)
pid_y = PID(0.6,0,0, setpoint=100, sample_time=1)
#pid.output_limits = (-10,10)
heading_x = 0
heading_y = 0
points = []
setpoints = []

for i in range(100):
    output_x = pid_x(heading_x)
    output_y = pid_y(heading_y)
    heading_x += output_x
    heading_y += output_y
    print(f"Output:({output_x},{output_y}), Current heading: ({heading_x},{heading_y}), setpoint: ({pid_x.setpoint}, {pid_y.setpoint})")
    #print(f"Components {pid.components}")
    #print(f"Setpoint {pid.setpoint}")
    points.append((heading_x, heading_y))
    setpoints.append((pid_x.setpoint, pid_y.setpoint))

    plt.plot(points[-1][0], points[-1][1], 'ro')
    plt.plot(setpoints[-1][0], setpoints[-1][1], 'bo')
    plt.pause(0.1)
    time.sleep(1.5)
    if i % 3 == 0:
        pid_x.setpoint = (pid_y.setpoint + i * 2) % 360
        pid_y.setpoint = (pid_y.setpoint / 2) - 100
