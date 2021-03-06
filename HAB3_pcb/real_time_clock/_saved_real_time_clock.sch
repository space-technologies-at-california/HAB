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
Text Label 5900 4850 0    10   ~ 0
GND
Text Label 6200 4850 0    10   ~ 0
GND
Wire Wire Line
	5100 3900 5100 3800
Text Label 5100 3900 0    10   ~ 0
GND
Wire Wire Line
	6150 3300 5650 3300
Text Label 6150 3300 0    10   ~ 0
GND
Wire Wire Line
	6450 3400 5650 3400
Text Label 6450 3400 0    10   ~ 0
VCC
Wire Wire Line
	5100 2800 5100 3000
Text Label 5100 2800 0    10   ~ 0
VCC
Wire Wire Line
	4700 4600 4400 4600
Text Label 4400 4600 0    70   ~ 0
SDA
Wire Wire Line
	5650 3500 6250 3500
Text Label 5950 3500 0    70   ~ 0
SDA
Wire Wire Line
	4700 4500 4400 4500
Text Label 4400 4500 0    70   ~ 0
SCL
Wire Wire Line
	5650 3600 6250 3600
Text Label 5950 3600 0    70   ~ 0
SCL
Wire Wire Line
	6200 4500 5900 4500
Wire Wire Line
	5650 3700 6250 3700
Text Label 5950 3700 0    70   ~ 0
SQW
Wire Wire Line
	4700 4400 4400 4400
Text Label 4400 4400 0    70   ~ 0
SQW
Wire Wire Line
	4700 4300 4700 3500
Wire Wire Line
	4700 3500 5100 3500
Wire Wire Line
	5100 3500 5100 3400
$Comp
L real_time_clock-eagle-import:GND #GND016
U 1 0 12C6E2A1
P 5900 4950
F 0 "#GND016" H 5900 4950 50  0001 C CNN
F 1 "GND" H 5800 4850 59  0000 L BNN
F 2 "" H 5900 4950 50  0001 C CNN
F 3 "" H 5900 4950 50  0001 C CNN
	1    5900 4950
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:GND #GND017
U 1 0 CBB20165
P 6200 4950
F 0 "#GND017" H 6200 4950 50  0001 C CNN
F 1 "GND" H 6100 4850 59  0000 L BNN
F 2 "" H 6200 4950 50  0001 C CNN
F 3 "" H 6200 4950 50  0001 C CNN
	1    6200 4950
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:HEADER-1X576MIL JP2
U 1 0 BAFA783C
P 5550 3500
F 0 "JP2" H 5300 3825 59  0000 L BNN
F 1 "HEADER-1X576MIL" H 4750 3100 59  0000 L BNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 5550 3500 50  0001 C CNN
F 3 "" H 5550 3500 50  0001 C CNN
	1    5550 3500
	-1   0    0    1   
$EndComp
$Comp
L real_time_clock-eagle-import:CAP_CERAMIC0805-NOOUTLINE C1
U 1 0 E7D47EA7
P 5100 3700
F 0 "C1" V 5010 3749 50  0000 C CNN
F 1 "10uF" V 5190 3749 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5100 3700 50  0001 C CNN
F 3 "" H 5100 3700 50  0001 C CNN
	1    5100 3700
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:GND #GND02
U 1 0 4877C9E2
P 5100 4000
F 0 "#GND02" H 5100 4000 50  0001 C CNN
F 1 "GND" H 5000 3900 59  0000 L BNN
F 2 "" H 5100 4000 50  0001 C CNN
F 3 "" H 5100 4000 50  0001 C CNN
	1    5100 4000
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:VCC #P+01
U 1 0 6A081B6E
P 6550 3400
F 0 "#P+01" H 6550 3400 50  0001 C CNN
F 1 "VCC" V 6450 3400 59  0000 R TNN
F 2 "" H 6550 3400 50  0001 C CNN
F 3 "" H 6550 3400 50  0001 C CNN
	1    6550 3400
	0    1    -1   0   
$EndComp
$Comp
L real_time_clock-eagle-import:GND #GND01
U 1 0 8DA2BB24
P 6250 3300
F 0 "#GND01" H 6250 3300 50  0001 C CNN
F 1 "GND" H 6150 3200 59  0000 L BNN
F 2 "" H 6250 3300 50  0001 C CNN
F 3 "" H 6250 3300 50  0001 C CNN
	1    6250 3300
	0    -1   -1   0   
$EndComp
$Comp
L real_time_clock-eagle-import:RTC_PCF8523T IC1
U 1 0 22F7723E
P 5300 4400
F 0 "IC1" H 5700 4700 59  0000 R TNN
F 1 "RTC_PCF8523T" H 5300 4400 50  0001 C CNN
F 2 "SOIC127P600X175-8N:SOIC127P600X175-8N" H 5300 4400 50  0001 C CNN
F 3 "" H 5300 4400 50  0001 C CNN
	1    5300 4400
	-1   0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:RESISTOR0805_NOOUTLINE R3
U 1 0 DF39756A
P 5100 3200
F 0 "R3" H 5100 3300 50  0000 C CNN
F 1 "1K" H 5100 3200 40  0000 C CNB
F 2 "Resistor_SMD:R_0402_1005Metric" H 5100 3200 50  0001 C CNN
F 3 "" H 5100 3200 50  0001 C CNN
	1    5100 3200
	0    1    1    0   
$EndComp
$Comp
L real_time_clock-eagle-import:VCC #P+02
U 1 0 637B3A6A
P 5100 2700
F 0 "#P+02" H 5100 2700 50  0001 C CNN
F 1 "VCC" V 5200 2800 59  0000 R TNN
F 2 "" H 5100 2700 50  0001 C CNN
F 3 "" H 5100 2700 50  0001 C CNN
	1    5100 2700
	-1   0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:CAP_CERAMIC0805-NOOUTLINE C2
U 1 0 8350CC17
P 4600 3100
F 0 "C2" V 4510 3149 50  0000 C CNN
F 1 "10uF" V 4690 3149 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4600 3100 50  0001 C CNN
F 3 "" H 4600 3100 50  0001 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:VCC #P+03
U 1 0 48C2C5DB
P 4600 2800
F 0 "#P+03" H 4600 2800 50  0001 C CNN
F 1 "VCC" V 4700 2900 59  0000 R TNN
F 2 "" H 4600 2800 50  0001 C CNN
F 3 "" H 4600 2800 50  0001 C CNN
	1    4600 2800
	-1   0    0    -1  
$EndComp
$Comp
L real_time_clock-eagle-import:GND #GND03
U 1 0 21137572
P 4600 3300
F 0 "#GND03" H 4600 3300 50  0001 C CNN
F 1 "GND" H 4500 3200 59  0000 L BNN
F 2 "" H 4600 3300 50  0001 C CNN
F 3 "" H 4600 3300 50  0001 C CNN
	1    4600 3300
	1    0    0    -1  
$EndComp
Connection ~ 5100 3500
$Comp
L ABS07W-32.768KHZ-D-2-T:32.768KHz Q1
U 1 1 5BBEE255
P 6850 4150
F 0 "Q1" V 6804 4380 50  0000 L CNN
F 1 "32.768KHz" V 6895 4380 50  0000 L CNN
F 2 "XTAL320X150X90" H 6850 4150 50  0001 L BNN
F 3 "Abracon" H 6850 4150 50  0001 L BNN
F 4 "SMD-2 Abracon" H 6850 4150 50  0001 L BNN "Field4"
F 5 "Unavailable" H 6850 4150 50  0001 L BNN "Field5"
F 6 "ABS07W-32.768KHZ-D-2-T" H 6850 4150 50  0001 L BNN "Field6"
F 7 "ABS07W Series 32.768 KHz 20 ppm 3 pF -40°C to 85°C 3.20 mm x 1.50 mm Crystal" H 6850 4150 50  0001 L BNN "Field7"
F 8 "None" H 6850 4150 50  0001 L BNN "Field8"
	1    6850 4150
	0    1    1    0   
$EndComp
$Comp
L real_time_clock-eagle-import:BATTERY B1
U 1 1 5BBEE532
P 6200 4750
F 0 "B1" V 6246 4617 50  0000 R CNN
F 1 "CR1220" V 6155 4617 50  0000 R CNN
F 2 "Battery:S8411-45R" H 6200 4750 50  0001 L BNN
F 3 "https://www.mouser.com/datasheet/2/181/S8411R-1136243.pdf" H 6200 4750 50  0001 L BNN
	1    6200 4750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5900 4300 6500 4300
Wire Wire Line
	6500 4300 6500 3750
Wire Wire Line
	6500 3750 6850 3750
Wire Wire Line
	5900 4400 6500 4400
Wire Wire Line
	6500 4400 6500 4550
Wire Wire Line
	6500 4550 6850 4550
Wire Wire Line
	5900 4600 5900 4850
Wire Wire Line
	6200 4500 6200 4650
$EndSCHEMATC
