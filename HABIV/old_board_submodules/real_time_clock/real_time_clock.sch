EESchema Schematic File Version 4
LIBS:real_time_clock-cache
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
Text Label 6150 4850 0    10   ~ 0
GND
Text Label 6450 4850 0    10   ~ 0
GND
Wire Wire Line
	5350 3900 5350 3800
Text Label 5350 3900 0    10   ~ 0
GND
Wire Wire Line
	5350 2800 5350 3000
Text Label 5350 2800 0    10   ~ 0
VCC
Wire Wire Line
	6450 4500 6150 4500
Wire Wire Line
	5350 3500 5350 3400
$Comp
L real_time_clock-rescue:GND-real_time_clock-eagle-import-habiv-board-rescue #GND?
U 1 0 12C6E2A1
P 6150 4950
F 0 "#GND?" H 6150 4950 50  0001 C CNN
F 1 "GND" H 6050 4850 59  0000 L BNN
F 2 "" H 6150 4950 50  0001 C CNN
F 3 "" H 6150 4950 50  0001 C CNN
	1    6150 4950
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:GND-real_time_clock-eagle-import-habiv-board-rescue #GND?
U 1 0 CBB20165
P 6450 4950
F 0 "#GND?" H 6450 4950 50  0001 C CNN
F 1 "GND" H 6350 4850 59  0000 L BNN
F 2 "" H 6450 4950 50  0001 C CNN
F 3 "" H 6450 4950 50  0001 C CNN
	1    6450 4950
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:CAP_CERAMIC0805-NOOUTLINE-real_time_clock-eagle-import-habiv-board-rescue C4
U 1 0 E7D47EA7
P 5350 3700
F 0 "C4" V 5260 3749 50  0000 C CNN
F 1 "10uF" V 5440 3749 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5350 3700 50  0001 C CNN
F 3 "" H 5350 3700 50  0001 C CNN
	1    5350 3700
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:GND-real_time_clock-eagle-import-habiv-board-rescue #GND?
U 1 0 4877C9E2
P 5350 4000
F 0 "#GND?" H 5350 4000 50  0001 C CNN
F 1 "GND" H 5250 3900 59  0000 L BNN
F 2 "" H 5350 4000 50  0001 C CNN
F 3 "" H 5350 4000 50  0001 C CNN
	1    5350 4000
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:RTC_PCF8523T-real_time_clock-eagle-import-habiv-board-rescue IC1
U 1 0 22F7723E
P 5550 4400
F 0 "IC1" H 5950 4700 59  0000 R TNN
F 1 "RTC_PCF8523T" H 5550 4400 50  0001 C CNN
F 2 "SOIC127P600X175-8N:SOIC127P600X175-8N" H 5550 4400 50  0001 C CNN
F 3 "" H 5550 4400 50  0001 C CNN
	1    5550 4400
	-1   0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:RESISTOR0805_NOOUTLINE-real_time_clock-eagle-import-habiv-board-rescue R16
U 1 0 DF39756A
P 5350 3200
F 0 "R16" H 5350 3300 50  0000 C CNN
F 1 "1K" H 5350 3200 40  0000 C CNB
F 2 "Resistor_SMD:R_0805_2012Metric" H 5350 3200 50  0001 C CNN
F 3 "" H 5350 3200 50  0001 C CNN
	1    5350 3200
	0    1    1    0   
$EndComp
$Comp
L real_time_clock-rescue:VCC-real_time_clock-eagle-import-habiv-board-rescue #P+?
U 1 0 637B3A6A
P 5350 2700
F 0 "#P+?" H 5350 2700 50  0001 C CNN
F 1 "VCC" V 5450 2800 59  0000 R TNN
F 2 "" H 5350 2700 50  0001 C CNN
F 3 "" H 5350 2700 50  0001 C CNN
	1    5350 2700
	-1   0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:CAP_CERAMIC0805-NOOUTLINE-real_time_clock-eagle-import-habiv-board-rescue C1
U 1 0 8350CC17
P 4850 3100
F 0 "C1" V 4760 3149 50  0000 C CNN
F 1 "10uF" V 4940 3149 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4850 3100 50  0001 C CNN
F 3 "" H 4850 3100 50  0001 C CNN
	1    4850 3100
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:VCC-real_time_clock-eagle-import-habiv-board-rescue #P+?
U 1 0 48C2C5DB
P 4850 2800
F 0 "#P+?" H 4850 2800 50  0001 C CNN
F 1 "VCC" V 4950 2900 59  0000 R TNN
F 2 "" H 4850 2800 50  0001 C CNN
F 3 "" H 4850 2800 50  0001 C CNN
	1    4850 2800
	-1   0    0    -1  
$EndComp
$Comp
L real_time_clock-rescue:GND-real_time_clock-eagle-import-habiv-board-rescue #GND?
U 1 0 21137572
P 4850 3300
F 0 "#GND?" H 4850 3300 50  0001 C CNN
F 1 "GND" H 4750 3200 59  0000 L BNN
F 2 "" H 4850 3300 50  0001 C CNN
F 3 "" H 4850 3300 50  0001 C CNN
	1    4850 3300
	1    0    0    -1  
$EndComp
Connection ~ 5350 3500
$Comp
L real_time_clock-rescue:32.768KHz-ABS07W-32.768KHZ-D-2-T-real_time_clock-rescue-habiv-board-rescue Q1
U 1 1 5BBEE255
P 7100 4150
F 0 "Q1" V 7054 4380 50  0000 L CNN
F 1 "32.768KHz" V 7145 4380 50  0000 L CNN
F 2 "ABS07W-32.768KHZ-D-2-T:XTAL320X150X90" H 7100 4150 50  0001 L BNN
F 3 "Abracon" H 7100 4150 50  0001 L BNN
F 4 "SMD-2 Abracon" H 7100 4150 50  0001 L BNN "Field4"
F 5 "Unavailable" H 7100 4150 50  0001 L BNN "Field5"
F 6 "ABS07W-32.768KHZ-D-2-T" H 7100 4150 50  0001 L BNN "Field6"
F 7 "ABS07W Series 32.768 KHz 20 ppm 3 pF -40°C to 85°C 3.20 mm x 1.50 mm Crystal" H 7100 4150 50  0001 L BNN "Field7"
F 8 "None" H 7100 4150 50  0001 L BNN "Field8"
	1    7100 4150
	0    1    1    0   
$EndComp
$Comp
L real_time_clock-rescue:BATTERY-real_time_clock-eagle-import-habiv-board-rescue B2
U 1 1 5BBEE532
P 6450 4750
F 0 "B2" V 6496 4617 50  0000 R CNN
F 1 "CR1220" V 6405 4617 50  0000 R CNN
F 2 "S8411-45R:S8411-45R" H 6450 4750 50  0001 L BNN
F 3 "https://www.mouser.com/datasheet/2/181/S8411R-1136243.pdf" H 6450 4750 50  0001 L BNN
	1    6450 4750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6150 4300 6750 4300
Wire Wire Line
	6750 4300 6750 3750
Wire Wire Line
	6750 3750 7100 3750
Wire Wire Line
	6150 4400 6750 4400
Wire Wire Line
	6750 4400 6750 4550
Wire Wire Line
	6750 4550 7100 4550
Wire Wire Line
	6150 4600 6150 4850
Wire Wire Line
	6450 4500 6450 4650
Wire Wire Line
	4000 4300 4100 4300
Wire Wire Line
	4100 4300 4100 4350
Connection ~ 4100 4300
Wire Wire Line
	4100 4300 4250 4300
Connection ~ 4250 4300
Wire Wire Line
	4250 4300 4950 4300
$Comp
L Device:R_Small R2
U 1 1 5C80B31B
P 4100 4450
F 0 "R2" H 3900 4500 50  0000 L CNN
F 1 "8.2k" H 3850 4400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4100 4450 50  0001 C CNN
F 3 "~" H 4100 4450 50  0001 C CNN
	1    4100 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4550 4100 4600
Wire Wire Line
	4250 4300 4250 4350
$Comp
L Device:R_Small R3
U 1 1 5C849D22
P 4250 4450
F 0 "R3" H 4300 4500 50  0000 L CNN
F 1 "8.2k" H 4400 4500 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4250 4450 50  0001 C CNN
F 3 "~" H 4250 4450 50  0001 C CNN
	1    4250 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4550 4600 4550
Wire Wire Line
	4000 3500 5350 3500
Wire Wire Line
	4000 3500 4000 3750
Text GLabel 4500 4500 0    50   Input ~ 0
PB8
Text GLabel 4450 4700 0    50   Input ~ 0
PB9
$Comp
L Device:R R1
U 1 1 5D15FA0F
P 4000 3900
F 0 "R1" H 4070 3946 50  0000 L CNN
F 1 "0" V 4000 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3930 3900 50  0001 C CNN
F 3 "~" H 4000 3900 50  0001 C CNN
	1    4000 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4050 4000 4300
Wire Wire Line
	4500 4500 4600 4500
Wire Wire Line
	4600 4500 4600 4550
Connection ~ 4600 4500
Wire Wire Line
	4600 4500 4650 4500
Wire Wire Line
	4450 4700 4600 4700
Wire Wire Line
	4600 4700 4600 4600
Connection ~ 4600 4600
Wire Wire Line
	4600 4600 4100 4600
Wire Wire Line
	4600 4600 4650 4600
$Comp
L Device:R R12
U 1 1 5D6F92C2
P 4800 4600
F 0 "R12" H 4870 4646 50  0000 L CNN
F 1 "0" V 4800 4550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4730 4600 50  0001 C CNN
F 3 "~" H 4800 4600 50  0001 C CNN
	1    4800 4600
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 5D6F9447
P 4800 4500
F 0 "R11" H 4650 4500 50  0000 L CNN
F 1 "0" V 4800 4450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4730 4500 50  0001 C CNN
F 3 "~" H 4800 4500 50  0001 C CNN
	1    4800 4500
	0    1    1    0   
$EndComp
NoConn ~ 4950 4400
$EndSCHEMATC
