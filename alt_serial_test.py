import numpy as np
import serial
import time

ser = serial.Serial('/dev/cu.usbmodem1421', 96000)
print(ser.name)


coeff = [42512, 38208, 27127, 24461, 28157, 32001]
def calc_temp_press_2(digi_temp, digi_press):
	t2 = 0
	off2 = 0
	sens2 = 0

	dT = digi_temp - coeff[4]*2**8
	temp = 2000 + dT*coeff[5]/2**23
	
	if(temp < 2000):
		t2 = dT**2/2**31
		off2 = 61*(temp-2000)**2/2**4
		sens = 2*(temp-2000)**2
		if(temp < -1500):
			off2 = off2 + 15*(temp+1500)**2
			sens2 = sens2+8*(temp+1500)**2	
	off = coeff[1]*2**17 + (coeff[3]*dT)/2**6
	sens = coeff[0]*2**16 + (coeff[2]*dT)/2**7

	temp = temp-t2
	off = off-off2
	sens = sens-sens2
	press = (digi_press*sens/2**21 - off)/2**15
	return temp, press


time.sleep(1)

for count in range (0, 100):
	dt = np.random.randint(0, 2**24)
	dp = np.random.randint(0, 2**4)

	while(not ser.inWaiting()):
		pass
	print(str(count) + ": " + str(dt) + ", " + str(dp))
	print("writing to arduino...")
	print(str(dt).encode())
	ser.write(str(dt).encode("utf-8"))
	while (not ser.inWaiting()):
		pass
	print(ser.readline())
	ser.write(str(dp).encode("utf-8"))
	while (not ser.inWaiting()):
		pass
	print(ser.readline())
	
	while(not ser.inWaiting()):
		pass
	temp = ser.readline()
	press = ser.readline()

	print("checking output...")
	print(str(temp) + ", " + str(press))
	py_temp =  calc_temp_press_2(dt, dp)[0]
	py_press =  calc_temp_press_2(dt, dp)[1]
	
	assert(temp == py_temp)
	assert(press == py_press)
ser.close()
