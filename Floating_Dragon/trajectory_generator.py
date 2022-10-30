from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

initial = np.array([15,19,100]) # x_i = [x,y,z]
final = np.array([35,35,5])
radius = 1
z_offset_loi = 0.2              # percent distance to traverse in the z direction before loitering (random in reality)
z_offset_lan = 0.8              # percent distance to traverse in the z direction (total) before landing

diff = final - initial

# Loiter math
x_offset_loi = 2   # absolute value of x position difference relative to the target before loitering
y_offset_loi = 2   # absolute value of y position difference relative to the target before loitering
z_offset_loi = 0.1

loiter_around = np.array([final[0] + (x_offset_loi * -np.sign(diff[0])),
                          final[1] + (y_offset_loi * -np.sign(diff[1]))])

loiter_height = final[2] + (1-z_offset_loi) * -diff[2]
loiter_height = 71

# Landing math
landing_height = final[2] + (1-z_offset_lan) * -diff[2] # altitude to start landing

# Print findings
print("initial coordinates:", initial)
print("final coordinates", final)
print("difference b/w initial and final", diff)
print("loiter coordinates", loiter_around)
print("loiter height", loiter_height)
print("landing height", landing_height)

fig = plt.figure(figsize=(30,10))
ax = plt.axes(projection='3d')
granularity = 300

#Data for phase 2 (we calc phase 2 first since the start/end of this phase are used in the calc of the other phases)
zline = np.linspace(loiter_height, landing_height, granularity)
xline = radius * np.cos(zline) + loiter_around[0]
yline = radius * np.sin(zline) + loiter_around[1]
ax.plot3D(xline, yline, zline, 'red')
loiter_start = [xline[0], yline[0], zline[0]]
loiter_end = [xline[-1], yline[-1], zline[-1]]

# Data for phase 1
xline = np.linspace(initial[0], loiter_start[0], granularity)
yline = np.linspace(initial[1], loiter_start[1], granularity)
zline = np.linspace(initial[2], loiter_start[2], granularity)
ax.plot3D(xline, yline, zline, 'blue')

# Data for phase 3
xline = np.linspace(loiter_end[0], final[0], granularity)
yline = np.linspace(loiter_end[1], final[1], granularity)
zline = np.linspace(loiter_end[2], final[2], granularity)
ax.plot3D(xline, yline, zline, 'green')

plt.savefig('plot.png', dpi=300, bbox_inches='tight')