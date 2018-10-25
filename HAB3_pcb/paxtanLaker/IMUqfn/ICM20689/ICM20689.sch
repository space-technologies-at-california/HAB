EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ICM-20689:ICM-20689 U1
U 1 1 5BD15253
P 5850 4050
F 0 "U1" H 5850 4815 50  0000 C CNN
F 1 "ICM-20689" H 5850 4724 50  0000 C CNN
F 2 "ICM-20689:QFN50P400X400X95-25N" H 5850 4050 50  0001 L BNN
F 3 "TDK InvenSense" H 5850 4050 50  0001 L BNN
F 4 "None" H 5850 4050 50  0001 L BNN "Field4"
F 5 "QFN-24 InvenSense" H 5850 4050 50  0001 L BNN "Field5"
F 6 "Unavailable" H 5850 4050 50  0001 L BNN "Field6"
F 7 "ICM-20689" H 5850 4050 50  0001 L BNN "Field7"
F 8 "6-Axis Drone/Vr/Iot Solution _Pi" H 5850 4050 50  0001 L BNN "Field8"
	1    5850 4050
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C1
U 1 1 5BD15313
P 7550 3850
F 0 "C1" V 7750 3850 50  0000 C CNN
F 1 "10nF" V 7850 3850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7550 3850 50  0001 C CNN
F 3 "" H 7550 3850 50  0001 C CNN
	1    7550 3850
	0    1    1    0   
$EndComp
$Comp
L pspice:CAP C2
U 1 1 5BD153A7
P 6750 2600
F 0 "C2" H 6572 2554 50  0000 R CNN
F 1 "10nF" H 6572 2645 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6750 2600 50  0001 C CNN
F 3 "" H 6750 2600 50  0001 C CNN
	1    6750 2600
	-1   0    0    1   
$EndComp
$Comp
L pspice:CAP C3
U 1 1 5BD153CB
P 7200 3150
F 0 "C3" H 7378 3196 50  0000 L CNN
F 1 "2.2uF" H 7378 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7200 3150 50  0001 C CNN
F 3 "" H 7200 3150 50  0001 C CNN
	1    7200 3150
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C4
U 1 1 5BD1540B
P 7700 2450
F 0 "C4" H 7878 2496 50  0000 L CNN
F 1 "CAP" H 7878 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7700 2450 50  0001 C CNN
F 3 "" H 7700 2450 50  0001 C CNN
	1    7700 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 5BD17662
P 6750 5800
F 0 "J1" H 6723 5730 50  0000 R CNN
F 1 "Conn_01x03_Male" H 6723 5821 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6750 5800 50  0001 C CNN
F 3 "~" H 6750 5800 50  0001 C CNN
	1    6750 5800
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 5BD1776D
P 8650 3100
F 0 "J2" H 8756 3478 50  0000 C CNN
F 1 "Conn_01x06_Male" H 8756 3387 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 8650 3100 50  0001 C CNN
F 3 "~" H 8650 3100 50  0001 C CNN
	1    8650 3100
	1    0    0    -1  
$EndComp
Text GLabel 6550 5700 0    50   Input ~ 0
VDDIO
Text GLabel 6250 2850 0    50   Input ~ 0
VDDIO
Text GLabel 6550 5800 0    50   Input ~ 0
VDD
Text GLabel 6650 4450 2    50   Input ~ 0
GND
Text GLabel 6550 5900 0    50   Input ~ 0
GND
Wire Wire Line
	6650 3850 7300 3850
Text GLabel 7800 3850 2    50   Input ~ 0
GND
Text GLabel 8850 2900 2    50   Input ~ 0
INT
Text GLabel 6650 3950 2    50   Input ~ 0
INT
Text GLabel 6650 4550 2    50   Input ~ 0
GND
Text GLabel 8850 3000 2    50   Input ~ 0
FSYNC
Text GLabel 5050 3850 0    50   Input ~ 0
FSYNC
Text GLabel 8850 3100 2    50   Input ~ 0
nCS
Text GLabel 5050 3950 0    50   Input ~ 0
nCS
Text GLabel 6750 2350 1    50   Input ~ 0
GND
Wire Wire Line
	6650 3550 6750 3550
Wire Wire Line
	6750 3550 6750 2850
Wire Wire Line
	6750 2850 6250 2850
Connection ~ 6750 2850
Wire Wire Line
	6650 3650 7200 3650
Wire Wire Line
	7200 3650 7200 3400
Wire Wire Line
	7200 3650 7700 3650
Connection ~ 7200 3650
Wire Wire Line
	7700 3650 7700 2700
Text GLabel 7200 2900 1    50   Input ~ 0
GND
Text GLabel 7700 2200 1    50   Input ~ 0
GND
Wire Wire Line
	7700 3650 8000 3650
Connection ~ 7700 3650
Text GLabel 8000 3650 2    50   Input ~ 0
VDD
Text GLabel 8850 3200 2    50   Input ~ 0
SCL
Text GLabel 5050 4050 0    50   Input ~ 0
SCL
Text GLabel 5050 4150 0    50   Input ~ 0
SDA
Text GLabel 8850 3300 2    50   Input ~ 0
SDA
Text GLabel 8850 3400 2    50   Input ~ 0
AD0
Text GLabel 5050 4250 0    50   Input ~ 0
AD0
$EndSCHEMATC
