import numpy as np
import serial
import time

ser = serial.Serial('/dev/cu.usbmodem1421', 115200)
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
	
	if (press < 1000):
		press = 1000;
	elif ( press > 120000):
		press = 120000;

	if (temp < -4000): 
		temp = -4000
	elif (temp > 8500):
		temp = 8500

	return temp, press


time.sleep(2)
count_wrong = 0
for count in range (0, 1000):
	dt = np.random.randint(0, 2**24)
	dp = np.random.randint(0, 2**24)
	
	ser.write(str(dt).encode())
	while(ser.inWaiting() == 0):
		pass
	ser.read(1)

	ser.write(str(dp).encode())
	while(ser.inWaiting() == 0):
		pass	
		
	temp = ser.read(ser.inWaiting())
	temp = temp.decode()
	temp = temp.replace('\r', '')
	temp = temp.replace('\n', '')
	ser.write(b'a')

	while(ser.inWaiting() == 0 ):
		pass
		
	press = ser.read(ser.inWaiting()).decode()
	press = press.replace('\r', '')
	press = press.replace('\n', '')
	ser.write(b'a')
	
	py_temp =  calc_temp_press_2(dt, dp)[0]
	py_press =  calc_temp_press_2(dt, dp)[1]	
	
	error_t = abs((int(temp) - py_temp)/py_temp)
	error_p = abs((int(press) - py_press)/py_press)
	if(error_t > 0.05 or error_p > 0.05):
		print("\nInput: " + str(count) + ": " + str(dt) + ", " + str(dp))
		print("Expected: " + str(py_temp) + ", " + str(py_press))
		print("Arduino: " + str(temp) + ", " + str(press))
		print("Error: " + str(error_t) + ", " + str(error_p))
		count_wrong += 1	
ser.close()
print(count_wrong)
print("Exiting...")
