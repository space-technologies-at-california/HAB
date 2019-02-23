EESchema Schematic File Version 4
LIBS:habiv-board-cache
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
Text Label -2250 -1500 0    10   ~ 0
GND
Text Label -1950 -1500 0    10   ~ 0
GND
Wire Wire Line
	-3050 -2450 -3050 -2550
Text Label -3050 -2450 0    10   ~ 0
GND
Wire Wire Line
	-2000 -3050 -2500 -3050
Text Label -2000 -3050 0    10   ~ 0
GND
Wire Wire Line
	-1700 -2950 -2500 -2950
Text Label -1700 -2950 0    10   ~ 0
VCC
Wire Wire Line
	-3050 -3550 -3050 -3350
Text Label -3050 -3550 0    10   ~ 0
VCC
Wire Wire Line
	-3450 -1750 -3750 -1750
Text Label -3750 -1750 0    70   ~ 0
SDA
Wire Wire Line
	-2500 -2850 -1900 -2850
Text Label -2200 -2850 0    70   ~ 0
SDA
Wire Wire Line
	-3450 -1850 -3750 -1850
Text Label -3750 -1850 0    70   ~ 0
SCL
Wire Wire Line
	-2500 -2750 -1900 -2750
Text Label -2200 -2750 0    70   ~ 0
SCL
Wire Wire Line
	-1950 -1850 -2250 -1850
Wire Wire Line
	-2500 -2650 -1900 -2650
Text Label -2200 -2650 0    70   ~ 0
SQW
Wire Wire Line
	-3450 -1950 -3750 -1950
Text Label -3750 -1950 0    70   ~ 0
SQW
Wire Wire Line
	-3450 -2050 -3450 -2850
Wire Wire Line
	-3450 -2850 -3050 -2850
Wire Wire Line
	-3050 -2850 -3050 -2950
$Comp
L habiv-board-rescue:GND-real_time_clock-eagle-import #GND?
U 1 0 12C6E2A1
P -2250 -1400
F 0 "#GND?" H -2250 -1400 50  0001 C CNN
F 1 "GND" H -2350 -1500 59  0000 L BNN
F 2 "" H -2250 -1400 50  0001 C CNN
F 3 "" H -2250 -1400 50  0001 C CNN
	1    -2250 -1400
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:GND-real_time_clock-eagle-import #GND?
U 1 0 CBB20165
P -1950 -1400
F 0 "#GND?" H -1950 -1400 50  0001 C CNN
F 1 "GND" H -2050 -1500 59  0000 L BNN
F 2 "" H -1950 -1400 50  0001 C CNN
F 3 "" H -1950 -1400 50  0001 C CNN
	1    -1950 -1400
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:HEADER-1X576MIL-real_time_clock-eagle-import JP?
U 1 0 BAFA783C
P -2600 -2850
F 0 "JP?" H -2850 -2525 59  0000 L BNN
F 1 "HEADER-1X576MIL" H -3400 -3250 59  0000 L BNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H -2600 -2850 50  0001 C CNN
F 3 "" H -2600 -2850 50  0001 C CNN
	1    -2600 -2850
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:CAP_CERAMIC0805-NOOUTLINE-real_time_clock-eagle-import C?
U 1 0 E7D47EA7
P -3050 -2650
F 0 "C?" V -3140 -2601 50  0000 C CNN
F 1 "10uF" V -2960 -2601 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H -3050 -2650 50  0001 C CNN
F 3 "" H -3050 -2650 50  0001 C CNN
	1    -3050 -2650
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:GND-real_time_clock-eagle-import #GND?
U 1 0 4877C9E2
P -3050 -2350
F 0 "#GND?" H -3050 -2350 50  0001 C CNN
F 1 "GND" H -3150 -2450 59  0000 L BNN
F 2 "" H -3050 -2350 50  0001 C CNN
F 3 "" H -3050 -2350 50  0001 C CNN
	1    -3050 -2350
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:VCC-real_time_clock-eagle-import #P+?
U 1 0 6A081B6E
P -1600 -2950
F 0 "#P+?" H -1600 -2950 50  0001 C CNN
F 1 "VCC" V -1700 -2950 59  0000 R TNN
F 2 "" H -1600 -2950 50  0001 C CNN
F 3 "" H -1600 -2950 50  0001 C CNN
	1    -1600 -2950
	0    1    -1   0   
$EndComp
$Comp
L habiv-board-rescue:GND-real_time_clock-eagle-import #GND?
U 1 0 8DA2BB24
P -1900 -3050
F 0 "#GND?" H -1900 -3050 50  0001 C CNN
F 1 "GND" H -2000 -3150 59  0000 L BNN
F 2 "" H -1900 -3050 50  0001 C CNN
F 3 "" H -1900 -3050 50  0001 C CNN
	1    -1900 -3050
	0    -1   -1   0   
$EndComp
$Comp
L habiv-board-rescue:RTC_PCF8523T-real_time_clock-eagle-import IC?
U 1 0 22F7723E
P -2850 -1950
F 0 "IC?" H -2450 -1650 59  0000 R TNN
F 1 "RTC_PCF8523T" H -2850 -1950 50  0001 C CNN
F 2 "SOIC127P600X175-8N:SOIC127P600X175-8N" H -2850 -1950 50  0001 C CNN
F 3 "" H -2850 -1950 50  0001 C CNN
	1    -2850 -1950
	-1   0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:RESISTOR0805_NOOUTLINE-real_time_clock-eagle-import R?
U 1 0 DF39756A
P -3050 -3150
F 0 "R?" H -3050 -3050 50  0000 C CNN
F 1 "1K" H -3050 -3150 40  0000 C CNB
F 2 "Resistor_SMD:R_0402_1005Metric" H -3050 -3150 50  0001 C CNN
F 3 "" H -3050 -3150 50  0001 C CNN
	1    -3050 -3150
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:VCC-real_time_clock-eagle-import #P+?
U 1 0 637B3A6A
P -3050 -3650
F 0 "#P+?" H -3050 -3650 50  0001 C CNN
F 1 "VCC" V -2950 -3550 59  0000 R TNN
F 2 "" H -3050 -3650 50  0001 C CNN
F 3 "" H -3050 -3650 50  0001 C CNN
	1    -3050 -3650
	-1   0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:CAP_CERAMIC0805-NOOUTLINE-real_time_clock-eagle-import C?
U 1 0 8350CC17
P -3550 -3250
F 0 "C?" V -3640 -3201 50  0000 C CNN
F 1 "10uF" V -3460 -3201 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H -3550 -3250 50  0001 C CNN
F 3 "" H -3550 -3250 50  0001 C CNN
	1    -3550 -3250
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:VCC-real_time_clock-eagle-import #P+?
U 1 0 48C2C5DB
P -3550 -3550
F 0 "#P+?" H -3550 -3550 50  0001 C CNN
F 1 "VCC" V -3450 -3450 59  0000 R TNN
F 2 "" H -3550 -3550 50  0001 C CNN
F 3 "" H -3550 -3550 50  0001 C CNN
	1    -3550 -3550
	-1   0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:GND-real_time_clock-eagle-import #GND?
U 1 0 21137572
P -3550 -3050
F 0 "#GND?" H -3550 -3050 50  0001 C CNN
F 1 "GND" H -3650 -3150 59  0000 L BNN
F 2 "" H -3550 -3050 50  0001 C CNN
F 3 "" H -3550 -3050 50  0001 C CNN
	1    -3550 -3050
	1    0    0    -1  
$EndComp
Connection ~ -3050 -2850
$Comp
L habiv-board-rescue:32.768KHz-ABS07W-32.768KHZ-D-2-T-real_time_clock-rescue Q?
U 1 1 5BBEE255
P -1300 -2200
F 0 "Q?" V -1346 -1970 50  0000 L CNN
F 1 "32.768KHz" V -1255 -1970 50  0000 L CNN
F 2 "XTAL320X150X90" H -1300 -2200 50  0001 L BNN
F 3 "Abracon" H -1300 -2200 50  0001 L BNN
F 4 "SMD-2 Abracon" H -1300 -2200 50  0001 L BNN "Field4"
F 5 "Unavailable" H -1300 -2200 50  0001 L BNN "Field5"
F 6 "ABS07W-32.768KHZ-D-2-T" H -1300 -2200 50  0001 L BNN "Field6"
F 7 "ABS07W Series 32.768 KHz 20 ppm 3 pF -40°C to 85°C 3.20 mm x 1.50 mm Crystal" H -1300 -2200 50  0001 L BNN "Field7"
F 8 "None" H -1300 -2200 50  0001 L BNN "Field8"
	1    -1300 -2200
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:BATTERY-real_time_clock-eagle-import B?
U 1 1 5BBEE532
P -1950 -1600
F 0 "B?" V -1904 -1733 50  0000 R CNN
F 1 "CR1220" V -1995 -1733 50  0000 R CNN
F 2 "Battery:S8411-45R" H -1950 -1600 50  0001 L BNN
F 3 "https://www.mouser.com/datasheet/2/181/S8411R-1136243.pdf" H -1950 -1600 50  0001 L BNN
	1    -1950 -1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	-2250 -2050 -1650 -2050
Wire Wire Line
	-1650 -2050 -1650 -2600
Wire Wire Line
	-1650 -2600 -1300 -2600
Wire Wire Line
	-2250 -1950 -1650 -1950
Wire Wire Line
	-1650 -1950 -1650 -1800
Wire Wire Line
	-1650 -1800 -1300 -1800
Wire Wire Line
	-2250 -1750 -2250 -1500
Wire Wire Line
	-1950 -1850 -1950 -1700
$Comp
L habiv-board-rescue:MAX31855-MAX31855-Hab_thermocoupler-rescue U?
U 1 1 5BB59E3B
P 10550 -1250
F 0 "U?" H 10550 -683 50  0000 C CNN
F 1 "MAX31855" H 10550 -774 50  0000 C CNN
F 2 "MAX31855:SO-8" H 10550 -1250 50  0001 L BNN
F 3 "" H 10550 -1250 50  0001 L BNN
F 4 "Maxim Integrated" H 10550 -1250 50  0001 L BNN "Field4"
F 5 "Unavailable" H 10550 -1250 50  0001 L BNN "Field5"
F 6 "MAX31855" H 10550 -1250 50  0001 L BNN "Field6"
F 7 "SO-8 Maxim Integrated" H 10550 -1250 50  0001 L BNN "Field7"
F 8 "None" H 10550 -1250 50  0001 L BNN "Field8"
	1    10550 -1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BB5A126
P 9450 -1250
F 0 "C?" H 9565 -1204 50  0000 L CNN
F 1 ".01 uF" H 9565 -1295 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9488 -1400 50  0001 C CNN
F 3 "~" H 9450 -1250 50  0001 C CNN
	1    9450 -1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 -1350 9700 -1350
Wire Wire Line
	9700 -1350 9700 -1400
Wire Wire Line
	9700 -1400 9450 -1400
Wire Wire Line
	9450 -1100 9700 -1100
Wire Wire Line
	9700 -1100 9700 -1150
Wire Wire Line
	9700 -1150 10150 -1150
$Comp
L Device:Ferrite_Bead L?
U 1 1 5BB5A7BF
P 9050 -1400
F 0 "L?" V 8776 -1400 50  0000 C CNN
F 1 "Ferrite_Bead" V 8867 -1400 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 8980 -1400 50  0001 C CNN
F 3 "~" H 9050 -1400 50  0001 C CNN
	1    9050 -1400
	0    1    1    0   
$EndComp
$Comp
L Device:Ferrite_Bead L?
U 1 1 5BB5A820
P 9050 -1100
F 0 "L?" V 8776 -1100 50  0000 C CNN
F 1 "Ferrite_Bead" V 8867 -1100 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 8980 -1100 50  0001 C CNN
F 3 "~" H 9050 -1100 50  0001 C CNN
	1    9050 -1100
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 -1400 9450 -1400
Connection ~ 9450 -1400
Wire Wire Line
	9450 -1100 9200 -1100
Connection ~ 9450 -1100
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 5BB5AAEB
P 8350 -1300
F 0 "J?" H 8456 -1122 50  0000 C CNN
F 1 "Conn_01x02_Male" H 8456 -1213 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8350 -1300 50  0001 C CNN
F 3 "~" H 8350 -1300 50  0001 C CNN
	1    8350 -1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 -1300 8550 -1400
Wire Wire Line
	8550 -1400 8900 -1400
Wire Wire Line
	8550 -1200 8550 -1100
Wire Wire Line
	8550 -1100 8900 -1100
$Comp
L power:GND #PWR?
U 1 1 5BB5C6BA
P 12950 -1050
F 0 "#PWR?" H 12950 -1300 50  0001 C CNN
F 1 "GND" V 12955 -1178 50  0000 R CNN
F 2 "" H 12950 -1050 50  0001 C CNN
F 3 "" H 12950 -1050 50  0001 C CNN
	1    12950 -1050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5BB5DB50
P 10650 -2000
F 0 "C?" H 10750 -2000 50  0000 L CNN
F 1 "0.1 uF" H 10550 -2100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10688 -2150 50  0001 C CNN
F 3 "~" H 10650 -2000 50  0001 C CNN
	1    10650 -2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10150 -2000 10500 -2000
Wire Wire Line
	10150 -2000 10150 -1550
Wire Wire Line
	10150 -950 10150 -200
Wire Wire Line
	10150 -200 12700 -200
Wire Wire Line
	12700 -200 12700 -1050
Wire Wire Line
	12700 -1050 12750 -1050
$Comp
L power:+3V3 #PWR?
U 1 1 5BC03C4E
P 12800 -1150
F 0 "#PWR?" H 12800 -1300 50  0001 C CNN
F 1 "+3V3" V 12800 -1500 50  0000 L CNN
F 2 "" H 12800 -1150 50  0001 C CNN
F 3 "" H 12800 -1150 50  0001 C CNN
	1    12800 -1150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10150 -2000 10150 -2250
Wire Wire Line
	10150 -2250 12550 -2250
Wire Wire Line
	12550 -2250 12550 -1150
Connection ~ 10150 -2000
Wire Wire Line
	12450 -2000 12450 -1050
Wire Wire Line
	12450 -1050 12700 -1050
Connection ~ 12700 -1050
Wire Wire Line
	10800 -2000 12450 -2000
Wire Wire Line
	10950 -750 10950 -1050
Wire Wire Line
	10950 -1250 11050 -1250
Wire Wire Line
	12750 -950 11150 -950
Wire Wire Line
	11150 -950 11150 -1450
Wire Wire Line
	11150 -1450 10950 -1450
$Comp
L Connector:Conn_01x05_Female J?
U 1 1 5BD6D44D
P 12950 -950
F 0 "J?" H 12850 -1250 50  0000 L CNN
F 1 "Conn_01x05_Female" H 12900 -1350 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 12950 -950 50  0001 C CNN
F 3 "~" H 12950 -950 50  0001 C CNN
	1    12950 -950
	1    0    0    -1  
$EndComp
Wire Wire Line
	12550 -1150 12750 -1150
Connection ~ 12750 -1150
Wire Wire Line
	12750 -1150 12800 -1150
Wire Wire Line
	10950 -750 12500 -750
Wire Wire Line
	12500 -750 12500 -850
Wire Wire Line
	12500 -850 12750 -850
Wire Wire Line
	11050 -600 12750 -600
Wire Wire Line
	12750 -600 12750 -750
Wire Wire Line
	11050 -1250 11050 -600
Wire Wire Line
	-6650 5650 -7350 5650
Text Label -7250 5650 0    70   ~ 0
FIX
Wire Wire Line
	-9750 5650 -9150 5650
Text Label -9550 5650 0    70   ~ 0
FIX
Wire Wire Line
	-7650 5650 -7750 5650
Wire Wire Line
	-8150 5650 -8250 5650
Wire Wire Line
	-8250 5650 -8250 5950
Wire Wire Line
	-8250 5950 -8250 6150
Wire Wire Line
	-8250 5350 -8250 5450
Wire Wire Line
	-8250 5450 -8250 5650
Wire Wire Line
	-6650 5950 -8250 5950
Wire Wire Line
	-6650 5450 -8250 5450
Connection ~ -8250 5650
Connection ~ -8250 5950
Connection ~ -8250 5450
Text Label -8150 5650 0    10   ~ 0
GND
Wire Wire Line
	-8850 5950 -8850 6250
Wire Wire Line
	-9750 5950 -8850 5950
Text Label -8850 5950 0    10   ~ 0
GND
Wire Wire Line
	-5450 6050 -4650 6050
Wire Wire Line
	-4650 6050 -4650 6350
Wire Wire Line
	-4650 6350 -4650 6450
Wire Wire Line
	-4650 6450 -4650 6550
Wire Wire Line
	-5450 5350 -4650 5350
Wire Wire Line
	-4650 5350 -4650 6050
Wire Wire Line
	-4950 6450 -4650 6450
Wire Wire Line
	-4950 6350 -4650 6350
Connection ~ -4650 6050
Connection ~ -4650 6450
Connection ~ -4650 6350
Text Label -5450 6050 0    10   ~ 0
GND
Wire Wire Line
	-6050 3950 -5750 3950
Wire Wire Line
	-5750 3950 -5750 4050
Text Label -6050 3950 0    10   ~ 0
GND
Wire Wire Line
	-8950 5350 -8950 5250
Wire Wire Line
	-9750 5350 -8950 5350
Text Label -8950 5350 0    10   ~ 0
3.3V
Wire Wire Line
	-8250 5050 -8250 4950
Wire Wire Line
	-8250 4950 -7250 4950
Wire Wire Line
	-6650 5250 -7250 5250
Wire Wire Line
	-7250 5250 -7250 4950
Connection ~ -7250 4950
Text Label -8250 5050 0    10   ~ 0
3.3V
Wire Wire Line
	-9750 5450 -9150 5450
Text Label -9550 5450 0    70   ~ 0
ENABLE
Wire Wire Line
	-9750 6050 -8650 6050
Wire Wire Line
	-8650 6050 -8650 5250
Text Label -9750 6050 0    10   ~ 0
VIN
Wire Wire Line
	-6650 5550 -7250 5550
Text Label -7250 5550 0    70   ~ 0
VBACKUP
Wire Wire Line
	-9750 5550 -9150 5550
Text Label -9550 5550 0    70   ~ 0
VBACKUP
Wire Wire Line
	-6750 3950 -7450 3950
Text Label -7350 3950 0    70   ~ 0
VBACKUP
Wire Wire Line
	-6650 6050 -7250 6050
Text Label -7250 6050 0    70   ~ 0
TX
Wire Wire Line
	-9750 5750 -9150 5750
Text Label -9550 5750 0    70   ~ 0
TX
Wire Wire Line
	-6650 6150 -7350 6150
Wire Wire Line
	-7350 6150 -7450 6150
Wire Wire Line
	-7350 6150 -7350 6950
Wire Wire Line
	-7350 6950 -7750 6950
Wire Wire Line
	-7750 6950 -7750 6850
Connection ~ -7350 6150
Text Label -7250 6150 0    70   ~ 0
RX_3V
Wire Wire Line
	-7650 6150 -8050 6150
Text Label -8050 6150 0    70   ~ 0
RX
Wire Wire Line
	-9750 5850 -9150 5850
Text Label -9550 5850 0    70   ~ 0
RX
Wire Wire Line
	-5450 6150 -5250 6150
Wire Wire Line
	-5450 5950 -4950 5950
Text Label -5250 5950 0    70   ~ 0
1PPS
Wire Wire Line
	-9750 6150 -9150 6150
Text Label -9550 6150 0    70   ~ 0
1PPS
Wire Wire Line
	-6550 3950 -6250 3950
$Comp
L habiv-board-rescue:GPS_FGPMMOPA6H-Adafruit_Ultimate_GPS-eagle-import U?
U 1 0 2DF3FE209D0AA111
P -6050 5650
F 0 "U?" H -6550 6550 42  0000 L BNN
F 1 "FGPMMOPA6H" H -6550 4650 42  0000 L BNN
F 2 "Adafruit Ultimate GPS:FGPMMOPA6H" H -6050 5650 50  0001 C CNN
F 3 "" H -6050 5650 50  0001 C CNN
	1    -6050 5650
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:LED0805-Adafruit_Ultimate_GPS-eagle-import LED?
U 1 0 B4BDD66162FEDCFC
P -7550 5650
F 0 "LED?" H -7600 5825 42  0000 C CNN
F 1 "RED" H -7600 5540 42  0000 C CNN
F 2 "Adafruit Ultimate GPS:CHIPLED_0805" H -7550 5650 50  0001 C CNN
F 3 "" H -7550 5650 50  0001 C CNN
	1    -7550 5650
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:RESISTOR0805_NOOUTLINE-Adafruit_Ultimate_GPS-eagle-import R?
U 1 0 B82084C643F53746
P -7950 5650
F 0 "R?" H -7950 5750 50  0000 C CNN
F 1 "1K" H -7950 5650 40  0000 C CNB
F 2 "Adafruit Ultimate GPS:0805-NO" H -7950 5650 50  0001 C CNN
F 3 "" H -7950 5650 50  0001 C CNN
	1    -7950 5650
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:GND-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 803D2E8F6197D135
P -8250 6250
F 0 "#U$?" H -8250 6250 50  0001 C CNN
F 1 "GND" H -8310 6150 42  0000 L BNN
F 2 "" H -8250 6250 50  0001 C CNN
F 3 "" H -8250 6250 50  0001 C CNN
	1    -8250 6250
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:3.3V-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 C4F885289A709B56
P -7250 4850
F 0 "#U$?" H -7250 4850 50  0001 C CNN
F 1 "3.3V" H -7310 4890 42  0000 L BNN
F 2 "" H -7250 4850 50  0001 C CNN
F 3 "" H -7250 4850 50  0001 C CNN
	1    -7250 4850
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:CAP_CERAMIC0805-NOOUTLINE-Adafruit_Ultimate_GPS-eagle-import C?
U 1 0 24498BA92B08E60C
P -8250 5250
F 0 "C?" V -8340 5299 50  0000 C CNN
F 1 "0.1uF" V -8160 5299 50  0000 C CNN
F 2 "Adafruit Ultimate GPS:0805-NO" H -8250 5250 50  0001 C CNN
F 3 "" H -8250 5250 50  0001 C CNN
	1    -8250 5250
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:VIN-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 22C351ED3FF9C786
P -8650 5150
F 0 "#U$?" H -8650 5150 50  0001 C CNN
F 1 "VIN" H -8710 5190 42  0000 L BNN
F 2 "" H -8650 5150 50  0001 C CNN
F 3 "" H -8650 5150 50  0001 C CNN
	1    -8650 5150
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:3.3V-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 2CF13A3609ED6043
P -8950 5150
F 0 "#U$?" H -8950 5150 50  0001 C CNN
F 1 "3.3V" H -9010 5190 42  0000 L BNN
F 2 "" H -8950 5150 50  0001 C CNN
F 3 "" H -8950 5150 50  0001 C CNN
	1    -8950 5150
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:GND-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 728101AFEEFC5E8C
P -8850 6350
F 0 "#U$?" H -8850 6350 50  0001 C CNN
F 1 "GND" H -8910 6250 42  0000 L BNN
F 2 "" H -8850 6350 50  0001 C CNN
F 3 "" H -8850 6350 50  0001 C CNN
	1    -8850 6350
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:DIODESOD-323-Adafruit_Ultimate_GPS-eagle-import D?
U 1 0 C049FE434DF527AB
P -7550 6150
F 0 "D?" H -7550 6250 42  0000 C CNN
F 1 "1N4148" H -7550 6052 42  0000 C CNN
F 2 "Adafruit Ultimate GPS:SOD-323" H -7550 6150 50  0001 C CNN
F 3 "" H -7550 6150 50  0001 C CNN
	1    -7550 6150
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:RESISTOR0805_NOOUTLINE-Adafruit_Ultimate_GPS-eagle-import R?
U 1 0 4F14531CD85E66C8
P -7750 6650
F 0 "R?" H -7750 6750 50  0000 C CNN
F 1 "10K" H -7750 6650 40  0000 C CNB
F 2 "Adafruit Ultimate GPS:0805-NO" H -7750 6650 50  0001 C CNN
F 3 "" H -7750 6650 50  0001 C CNN
	1    -7750 6650
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:3.3V-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 C6CA7EF2407A0320
P -7750 6350
F 0 "#U$?" H -7750 6350 50  0001 C CNN
F 1 "3.3V" H -7810 6390 42  0000 L BNN
F 2 "" H -7750 6350 50  0001 C CNN
F 3 "" H -7750 6350 50  0001 C CNN
	1    -7750 6350
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:BATTERYCR1220_SMT-Adafruit_Ultimate_GPS-eagle-import B?
U 1 0 96DDDAD98A000202
P -6150 3950
F 0 "B?" H -6250 4075 42  0000 L BNN
F 1 "CR1220" H -6250 3750 42  0000 L BNN
F 2 "Adafruit Ultimate GPS:CR1220" H -6150 3950 50  0001 C CNN
F 3 "" H -6150 3950 50  0001 C CNN
	1    -6150 3950
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:GND-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 25B093F9D405EDE5
P -5750 4150
F 0 "#U$?" H -5750 4150 50  0001 C CNN
F 1 "GND" H -5810 4050 42  0000 L BNN
F 2 "" H -5750 4150 50  0001 C CNN
F 3 "" H -5750 4150 50  0001 C CNN
	1    -5750 4150
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:GND-Adafruit_Ultimate_GPS-eagle-import #U$?
U 1 0 28B2C22724E1B701
P -4650 6650
F 0 "#U$?" H -4650 6650 50  0001 C CNN
F 1 "GND" H -4710 6550 42  0000 L BNN
F 2 "" H -4650 6650 50  0001 C CNN
F 3 "" H -4650 6650 50  0001 C CNN
	1    -4650 6650
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:U.FL-Adafruit_Ultimate_GPS-eagle-import U$?
U 1 0 14A4E007DC93C178
P -5050 6150
F 0 "U$?" H -5050 6150 50  0001 C CNN
F 1 "U.FL" H -5050 6150 50  0001 C CNN
F 2 "Adafruit Ultimate GPS:U.FL" H -5050 6150 50  0001 C CNN
F 3 "" H -5050 6150 50  0001 C CNN
	1    -5050 6150
	-1   0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:HEADER-1X970MIL-Adafruit_Ultimate_GPS-eagle-import JP?
U 1 0 E5C11E09A75A2B47
P -9850 5750
F 0 "JP?" H -10100 6275 59  0000 L BNN
F 1 "HEADER-1X970MIL" H -10100 5150 59  0000 L BNN
F 2 "Adafruit Ultimate GPS:1X09_ROUND_70" H -9850 5750 50  0001 C CNN
F 3 "" H -9850 5750 50  0001 C CNN
	1    -9850 5750
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:DIODESOD-323-Adafruit_Ultimate_GPS-eagle-import D?
U 1 0 A3EFA98ECB5A3888
P -6650 3950
F 0 "D?" H -6650 4050 42  0000 C CNN
F 1 "CUS520" H -6650 3852 42  0000 C CNN
F 2 "Adafruit Ultimate GPS:SOD-323" H -6650 3950 50  0001 C CNN
F 3 "" H -6650 3950 50  0001 C CNN
	1    -6650 3950
	-1   0    0    1   
$EndComp
Text Notes -7250 6850 0    59   ~ 0
D1+R3 restrict RX input to 3.3V
$Comp
L habiv-board-rescue:MS560702BA03-00-MS560702BA03-00 U?
U 1 1 5BB59AA0
P 18100 5250
F 0 "U?" H 18100 5817 50  0000 C CNN
F 1 "MS560702BA03-00" H 18100 5726 50  0000 C CNN
F 2 "MS560702BA03-00:SON125P500X300X100-8N" H 18100 5250 50  0001 L BNN
F 3 "MS5607-02BA03 Series 3 V 1 to 120 kPa Absolute Barometric Pressure Sensor" H 18100 5250 50  0001 L BNN
F 4 "TE Connectivity" H 18100 5250 50  0001 L BNN "Field4"
F 5 "Unavailable" H 18100 5250 50  0001 L BNN "Field5"
F 6 "http://www.te.com/usa-en/product-MS560702BA03-00.html" H 18100 5250 50  0001 L BNN "Field6"
F 7 "MS560702BA03-00" H 18100 5250 50  0001 L BNN "Field7"
F 8 "SMD-8 TE Connectivity" H 18100 5250 50  0001 L BNN "Field8"
F 9 "Compliant" H 18100 5250 50  0001 L BNN "Field9"
F 10 "None" H 18100 5250 50  0001 L BNN "Field10"
	1    18100 5250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J?
U 1 1 5BB59CF9
P 20300 5200
F 0 "J?" H 20327 5176 50  0000 L CNN
F 1 "Conn_01x04_Female" H 20327 5085 50  0000 L CNN
F 2 "Connector:FanPinHeader_1x04_P2.54mm_Vertical" H 20300 5200 50  0001 C CNN
F 3 "~" H 20300 5200 50  0001 C CNN
	1    20300 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	17500 5350 17300 5350
Wire Wire Line
	17500 5250 17200 5250
Wire Wire Line
	20100 5200 19950 5200
Wire Wire Line
	19950 5200 19950 5900
Wire Wire Line
	20100 5300 20000 5300
Wire Wire Line
	20000 5300 20000 6000
Wire Wire Line
	20100 5400 20050 5400
Wire Wire Line
	20050 5400 20050 6100
Wire Wire Line
	17400 5900 19950 5900
Wire Wire Line
	17300 6000 20000 6000
Wire Wire Line
	17200 6100 20050 6100
Wire Wire Line
	17300 5350 17300 6000
Wire Wire Line
	17200 5250 17200 6100
Wire Wire Line
	18700 5750 16750 5750
Wire Wire Line
	16750 5750 16750 5150
Wire Wire Line
	17500 5150 16750 5150
$Comp
L pspice:CAP C?
U 1 1 5BB5E0FC
P 16350 4700
F 0 "C?" H 16528 4746 50  0000 L CNN
F 1 "100nF" H 16528 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 16350 4700 50  0001 C CNN
F 3 "" H 16350 4700 50  0001 C CNN
	1    16350 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BB5E5DC
P 16350 4400
F 0 "#PWR?" H 16350 4250 50  0001 C CNN
F 1 "+3V3" H 16365 4573 50  0000 C CNN
F 2 "" H 16350 4400 50  0001 C CNN
F 3 "" H 16350 4400 50  0001 C CNN
	1    16350 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BB5E65F
P 16350 5000
F 0 "#PWR?" H 16350 4750 50  0001 C CNN
F 1 "GND" H 16355 4827 50  0000 C CNN
F 2 "" H 16350 5000 50  0001 C CNN
F 3 "" H 16350 5000 50  0001 C CNN
	1    16350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	17500 4600 20100 4600
Text Label 19950 5200 0    50   ~ 0
SDO
Text Label 20000 5300 0    50   ~ 0
SDI
Text Label 20050 5550 0    50   ~ 0
SCLK
Wire Wire Line
	18700 4450 16350 4450
Wire Wire Line
	18700 4450 18700 4950
Wire Wire Line
	16750 5150 16750 4950
Wire Wire Line
	16750 4950 16350 4950
Connection ~ 16750 5150
Wire Wire Line
	16350 4950 16350 5000
Wire Wire Line
	17500 4600 17500 5050
Wire Wire Line
	20100 4600 20100 5100
Text Label 20100 4850 0    50   ~ 0
CSB
Wire Wire Line
	17500 5450 17400 5450
Wire Wire Line
	17400 5450 17400 5900
Wire Wire Line
	18700 5550 18700 5750
Connection ~ 16350 4950
Wire Wire Line
	16350 4400 16350 4450
Connection ~ 16350 4450
Text Label 16600 4450 0    50   ~ 0
VDD
Text Label 16750 5400 0    50   ~ 0
GND
Text Label 16850 5150 0    50   ~ 0
PS
$Comp
L Connector_Generic:Conn_02x01 J?
U 1 1 5BBAC4EB
P 15500 4650
F 0 "J?" V 15504 4730 50  0000 L CNN
F 1 "Conn_02x01" V 15595 4730 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x01_P2.54mm_Vertical" H 15500 4650 50  0001 C CNN
F 3 "~" H 15500 4650 50  0001 C CNN
	1    15500 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	16350 4300 15500 4300
Wire Wire Line
	15500 4300 15500 4450
Wire Wire Line
	16350 5100 15500 5100
Wire Wire Line
	15500 5100 15500 4950
Wire Wire Line
	16350 4300 16350 4400
Connection ~ 16350 4400
Wire Wire Line
	16350 5100 16350 5000
Connection ~ 16350 5000
$Comp
L habiv-board-rescue:STM32F401RET6-STM32-rescue U?
U 1 1 5BB18215
P 7400 13300
F 0 "U?" H 7400 13300 50  0000 L BNN
F 1 "STM32F401RET6" H 7100 12700 50  0000 L BNN
F 2 "STM32F401RET6:QFP50P1200X1200X160-64N" H 7400 13300 50  0001 L BNN
F 3 "None" H 7400 13300 50  0001 L BNN
F 4 "STMicroelectronics" H 7400 13300 50  0001 L BNN "Field4"
F 5 "LQFP-64 STMicroelectronics" H 7400 13300 50  0001 L BNN "Field5"
F 6 "Unavailable" H 7400 13300 50  0001 L BNN "Field6"
F 7 "MCU 32-Bit STM32 ARM Cortex M4 RISC 512KB Flash 1.8V/2.5V/3.3V 64-Pin LQFP Tray" H 7400 13300 50  0001 L BNN "Field7"
F 8 "STM32F401RET6" H 7400 13300 50  0001 L BNN "Field8"
	1    7400 13300
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 100nF?
U 1 1 5BB5A0DB
P 4450 14350
F 0 "100nF?" H 4475 14450 50  0000 L CNN
F 1 "C5" H 4475 14250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4488 14200 50  0001 C CNN
F 3 "" H 4450 14350 50  0001 C CNN
	1    4450 14350
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BB5A20D
P 6150 12450
F 0 "#PWR?" H 6150 12300 50  0001 C CNN
F 1 "+3V3" H 6150 12590 50  0000 C CNN
F 2 "" H 6150 12450 50  0001 C CNN
F 3 "" H 6150 12450 50  0001 C CNN
	1    6150 12450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BB5A23B
P 5300 13900
F 0 "#PWR?" H 5300 13750 50  0001 C CNN
F 1 "+3V3" H 5300 14040 50  0000 C CNN
F 2 "" H 5300 13900 50  0001 C CNN
F 3 "" H 5300 13900 50  0001 C CNN
	1    5300 13900
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BB5A748
P 4150 12700
F 0 "C?" H 4175 12800 50  0000 L CNN
F 1 "4.3pF" H 4175 12600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4188 12550 50  0001 C CNN
F 3 "" H 4150 12700 50  0001 C CNN
	1    4150 12700
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BB5A7DC
P 4150 12950
F 0 "C?" H 4175 13050 50  0000 L CNN
F 1 "4.3pF" H 4175 12850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4188 12800 50  0001 C CNN
F 3 "" H 4150 12950 50  0001 C CNN
	1    4150 12950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BB5AAE7
P 4000 13200
F 0 "#PWR?" H 4000 12950 50  0001 C CNN
F 1 "GND" H 4000 13050 50  0000 C CNN
F 2 "" H 4000 13200 50  0001 C CNN
F 3 "" H 4000 13200 50  0001 C CNN
	1    4000 13200
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Conn_ARM_JTAG_SWD_20-STM32-rescue J?
U 1 1 5BC4298C
P 700 17600
F 0 "J?" H 500 18450 50  0000 R CNN
F 1 "Conn_ARM_JTAG_SWD_20" H 500 18350 50  0000 R BNN
F 2 "Pin_Headers:Pin_Header_Straight_2x10_Pitch2.54mm" H 1150 16550 50  0001 L TNN
F 3 "" V 350 16350 50  0001 C CNN
	1    700  17600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC43A22
P 4250 14400
F 0 "#PWR?" H 4250 14150 50  0001 C CNN
F 1 "GND" H 4250 14250 50  0000 C CNN
F 2 "" H 4250 14400 50  0001 C CNN
F 3 "" H 4250 14400 50  0001 C CNN
	1    4250 14400
	1    0    0    -1  
$EndComp
Text GLabel 4750 13950 2    60   Input ~ 0
RST
$Comp
L habiv-board-rescue:L-STM32-rescue 22uH?
U 1 1 5BC43B12
P 5300 14050
F 0 "22uH?" V 5250 14050 50  0000 C CNN
F 1 "L1" V 5375 14050 50  0000 C CNN
F 2 "Inductors_SMD:L_0603_HandSoldering" H 5300 14050 50  0001 C CNN
F 3 "" H 5300 14050 50  0001 C CNN
	1    5300 14050
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 1uF?
U 1 1 5BC43DE9
P 5300 14400
F 0 "1uF?" H 5325 14500 50  0000 L CNN
F 1 "C6" H 5325 14300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5338 14250 50  0001 C CNN
F 3 "" H 5300 14400 50  0001 C CNN
	1    5300 14400
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 10nF?
U 1 1 5BC43E5D
P 5550 14400
F 0 "10nF?" H 5575 14500 50  0000 L CNN
F 1 "C7" H 5575 14300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5588 14250 50  0001 C CNN
F 3 "" H 5550 14400 50  0001 C CNN
	1    5550 14400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC43FFE
P 5550 14600
F 0 "#PWR?" H 5550 14350 50  0001 C CNN
F 1 "GND" H 5550 14450 50  0000 C CNN
F 2 "" H 5550 14600 50  0001 C CNN
F 3 "" H 5550 14600 50  0001 C CNN
	1    5550 14600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR?
U 1 1 5BC44633
P 5550 13750
F 0 "#PWR?" H 5550 13600 50  0001 C CNN
F 1 "+3.3VA" H 5550 13890 50  0000 C CNN
F 2 "" H 5550 13750 50  0001 C CNN
F 3 "" H 5550 13750 50  0001 C CNN
	1    5550 13750
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue 0k?
U 1 1 5BC449A1
P 4950 12700
F 0 "0k?" V 5030 12700 50  0000 C CNN
F 1 "R1" V 4950 12700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4880 12700 50  0001 C CNN
F 3 "" H 4950 12700 50  0001 C CNN
	1    4950 12700
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue 0k?
U 1 1 5BC44ABA
P 4950 13000
F 0 "0k?" V 5030 13000 50  0000 C CNN
F 1 "R2" V 4950 13000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4880 13000 50  0001 C CNN
F 3 "" H 4950 13000 50  0001 C CNN
	1    4950 13000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC45CED
P 6750 14450
F 0 "#PWR?" H 6750 14200 50  0001 C CNN
F 1 "GND" H 6750 14300 50  0000 C CNN
F 2 "" H 6750 14450 50  0001 C CNN
F 3 "" H 6750 14450 50  0001 C CNN
	1    6750 14450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC45D37
P 8050 14450
F 0 "#PWR?" H 8050 14200 50  0001 C CNN
F 1 "GND" H 8050 14300 50  0000 C CNN
F 2 "" H 8050 14450 50  0001 C CNN
F 3 "" H 8050 14450 50  0001 C CNN
	1    8050 14450
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 1uF?
U 1 1 5BC46049
P 8800 12150
F 0 "1uF?" H 8825 12250 50  0000 L CNN
F 1 "C10" H 8825 12050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8838 12000 50  0001 C CNN
F 3 "" H 8800 12150 50  0001 C CNN
	1    8800 12150
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 100nF?
U 1 1 5BC4604F
P 9050 12150
F 0 "100nF?" H 9075 12250 50  0000 L CNN
F 1 "C11" H 9075 12050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9088 12000 50  0001 C CNN
F 3 "" H 9050 12150 50  0001 C CNN
	1    9050 12150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC46055
P 9050 12350
F 0 "#PWR?" H 9050 12100 50  0001 C CNN
F 1 "GND" H 9050 12200 50  0000 C CNN
F 2 "" H 9050 12350 50  0001 C CNN
F 3 "" H 9050 12350 50  0001 C CNN
	1    9050 12350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BC462B3
P 9050 11950
F 0 "#PWR?" H 9050 11800 50  0001 C CNN
F 1 "+3V3" H 9050 12090 50  0000 C CNN
F 2 "" H 9050 11950 50  0001 C CNN
F 3 "" H 9050 11950 50  0001 C CNN
	1    9050 11950
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 1uF?
U 1 1 5BC464D1
P 6850 15400
F 0 "1uF?" H 6875 15500 50  0000 L CNN
F 1 "C8" H 6875 15300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6888 15250 50  0001 C CNN
F 3 "" H 6850 15400 50  0001 C CNN
	1    6850 15400
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 100nF?
U 1 1 5BC464D7
P 7100 15400
F 0 "100nF?" H 7125 15500 50  0000 L CNN
F 1 "C9" H 7125 15300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7138 15250 50  0001 C CNN
F 3 "" H 7100 15400 50  0001 C CNN
	1    7100 15400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC464DD
P 7100 15600
F 0 "#PWR?" H 7100 15350 50  0001 C CNN
F 1 "GND" H 7100 15450 50  0000 C CNN
F 2 "" H 7100 15600 50  0001 C CNN
F 3 "" H 7100 15600 50  0001 C CNN
	1    7100 15600
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BC464E9
P 7100 15200
F 0 "#PWR?" H 7100 15050 50  0001 C CNN
F 1 "+3V3" H 7100 15340 50  0000 C CNN
F 2 "" H 7100 15200 50  0001 C CNN
F 3 "" H 7100 15200 50  0001 C CNN
	1    7100 15200
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 4.7uF?
U 1 1 5BC46836
P 7950 14900
F 0 "4.7uF?" H 7975 15000 50  0000 L CNN
F 1 "C21" H 7975 14800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7988 14750 50  0001 C CNN
F 3 "" H 7950 14900 50  0001 C CNN
	1    7950 14900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC468DC
P 7950 15050
F 0 "#PWR?" H 7950 14800 50  0001 C CNN
F 1 "GND" H 7950 14900 50  0000 C CNN
F 2 "" H 7950 15050 50  0001 C CNN
F 3 "" H 7950 15050 50  0001 C CNN
	1    7950 15050
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 1uF?
U 1 1 5BC46E30
P 8150 15400
F 0 "1uF?" H 8175 15500 50  0000 L CNN
F 1 "C12" H 8175 15300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8188 15250 50  0001 C CNN
F 3 "" H 8150 15400 50  0001 C CNN
	1    8150 15400
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 100nF?
U 1 1 5BC46E36
P 8400 15400
F 0 "100nF?" H 8425 15500 50  0000 L CNN
F 1 "C13" H 8425 15300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8438 15250 50  0001 C CNN
F 3 "" H 8400 15400 50  0001 C CNN
	1    8400 15400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC46E3C
P 8400 15600
F 0 "#PWR?" H 8400 15350 50  0001 C CNN
F 1 "GND" H 8400 15450 50  0000 C CNN
F 2 "" H 8400 15600 50  0001 C CNN
F 3 "" H 8400 15600 50  0001 C CNN
	1    8400 15600
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BC46E48
P 8400 15200
F 0 "#PWR?" H 8400 15050 50  0001 C CNN
F 1 "+3V3" H 8400 15340 50  0000 C CNN
F 2 "" H 8400 15200 50  0001 C CNN
F 3 "" H 8400 15200 50  0001 C CNN
	1    8400 15200
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 1uF?
U 1 1 5BC4730D
P 6150 11850
F 0 "1uF?" H 6175 11950 50  0000 L CNN
F 1 "C14" H 6175 11750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6188 11700 50  0001 C CNN
F 3 "" H 6150 11850 50  0001 C CNN
	1    6150 11850
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue 100nF?
U 1 1 5BC47313
P 6400 11850
F 0 "100nF?" H 6425 11950 50  0000 L CNN
F 1 "C15" H 6425 11750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6438 11700 50  0001 C CNN
F 3 "" H 6400 11850 50  0001 C CNN
	1    6400 11850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC47319
P 6400 12050
F 0 "#PWR?" H 6400 11800 50  0001 C CNN
F 1 "GND" H 6400 11900 50  0000 C CNN
F 2 "" H 6400 12050 50  0001 C CNN
F 3 "" H 6400 12050 50  0001 C CNN
	1    6400 12050
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BC47325
P 6400 11650
F 0 "#PWR?" H 6400 11500 50  0001 C CNN
F 1 "+3V3" H 6400 11790 50  0000 C CNN
F 2 "" H 6400 11650 50  0001 C CNN
F 3 "" H 6400 11650 50  0001 C CNN
	1    6400 11650
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue 10k?
U 1 1 5BC475E1
P 7050 11600
F 0 "10k?" V 7130 11600 50  0000 C CNN
F 1 "R5" V 7050 11600 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6980 11600 50  0001 C CNN
F 3 "" H 7050 11600 50  0001 C CNN
	1    7050 11600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC47B02
P 6900 11150
F 0 "#PWR?" H 6900 10900 50  0001 C CNN
F 1 "GND" H 6900 11000 50  0000 C CNN
F 2 "" H 6900 11150 50  0001 C CNN
F 3 "" H 6900 11150 50  0001 C CNN
	1    6900 11150
	1    0    0    -1  
$EndComp
Text GLabel 8550 12750 2    60   Input ~ 0
PA13
Text GLabel 8550 12850 2    60   Input ~ 0
PA12
Text GLabel 8550 12950 2    60   Input ~ 0
PA11
Text GLabel 8550 13050 2    60   Input ~ 0
PA10
Text GLabel 8550 13150 2    60   Input ~ 0
PA9
Text GLabel 8550 13250 2    60   Input ~ 0
PA8
Text GLabel 8550 13350 2    60   Input ~ 0
PC9
Text GLabel 8550 13450 2    60   Input ~ 0
PC8
Text GLabel 8550 13550 2    60   Input ~ 0
PC7
Text GLabel 8550 13650 2    60   Input ~ 0
PC6
Text GLabel 8550 13750 2    60   Input ~ 0
PB15
Text GLabel 8550 13850 2    60   Input ~ 0
PB14
Text GLabel 8550 13950 2    60   Input ~ 0
PB13
Text GLabel 8550 14050 2    60   Input ~ 0
PB12
Text GLabel 6250 12650 0    60   Input ~ 0
PC13
Text GLabel 6250 13250 0    60   Input ~ 0
PC0
Text GLabel 6250 13350 0    60   Input ~ 0
PC1
Text GLabel 6250 13450 0    60   Input ~ 0
PC2
Text GLabel 6250 13550 0    60   Input ~ 0
PC3
Text GLabel 6250 13850 0    60   Input ~ 0
PA0
Text GLabel 6250 13950 0    60   Input ~ 0
PA1
Text GLabel 6250 14050 0    60   Input ~ 0
PA2
Text GLabel 6650 14450 3    60   Input ~ 0
PA3
Text GLabel 6950 14450 3    60   Input ~ 0
PA4
Text GLabel 7050 14450 3    60   Input ~ 0
PA5
Text GLabel 7150 14450 3    60   Input ~ 0
PA6
Text GLabel 7250 14450 3    60   Input ~ 0
PA7
Text GLabel 7350 14450 3    60   Input ~ 0
PC4
Text GLabel 7450 14450 3    60   Input ~ 0
PC5
Text GLabel 7550 14450 3    60   Input ~ 0
PB0
Text GLabel 7650 14450 3    60   Input ~ 0
PB1
Text GLabel 7750 14450 3    60   Input ~ 0
PB2
Text GLabel 7850 14450 3    60   Input ~ 0
PB10
Text GLabel 8150 12150 1    60   Input ~ 0
PA14
Text GLabel 8050 12150 1    60   Input ~ 0
PA15
Text GLabel 7950 12150 1    60   Input ~ 0
PC10
Text GLabel 7850 12150 1    60   Input ~ 0
PC11
Text GLabel 7750 12150 1    60   Input ~ 0
PC12
Text GLabel 7650 12150 1    60   Input ~ 0
PD2
Text GLabel 7550 12150 1    60   Input ~ 0
PB3
Text GLabel 7450 12150 1    60   Input ~ 0
PB4
Text GLabel 7350 12150 1    60   Input ~ 0
PB5
Text GLabel 7250 12150 1    60   Input ~ 0
PB6
Text GLabel 7150 12150 1    60   Input ~ 0
PB7
Text GLabel 6950 12150 1    60   Input ~ 0
PB8
Text GLabel 6850 12150 1    60   Input ~ 0
PB9
$Comp
L habiv-board-rescue:Micro_SD_Card_Det-STM32-rescue J?
U 1 1 5BC49DC0
P -50 11350
F 0 "J?" H -700 12050 50  0000 C CNN
F 1 "Micro_SD_Card_Det" H 600 12050 50  0000 R CNN
F 2 "Connectors_Card:Hirose_DM3BT-DSF-PEJS" H 2000 12050 50  0001 C CNN
F 3 "" H -50 11450 50  0001 C CNN
	1    -50  11350
	1    0    0    -1  
$EndComp
Text GLabel 1300 17100 2    60   Input ~ 0
PB4
Text GLabel 1300 17800 2    60   Input ~ 0
PA15
Text GLabel 1300 17600 2    60   Input ~ 0
PA13
Text GLabel 1300 17500 2    60   Input ~ 0
PA14
Text GLabel 1300 17700 2    60   Input ~ 0
PB3
Text GLabel 1300 17200 2    60   Input ~ 0
RST
$Comp
L habiv-board-rescue:R-STM32-rescue 10k?
U 1 1 5BC4A25B
P 1750 17400
F 0 "10k?" V 1830 17400 50  0000 C CNN
F 1 "R6" V 1750 17400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1680 17400 50  0001 C CNN
F 3 "" H 1750 17400 50  0001 C CNN
	1    1750 17400
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue 10k?
U 1 1 5BC4A5C9
P 1750 18000
F 0 "10k?" V 1830 18000 50  0000 C CNN
F 1 "R7" V 1750 18000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1680 18000 50  0001 C CNN
F 3 "" H 1750 18000 50  0001 C CNN
	1    1750 18000
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue 10k?
U 1 1 5BC4A665
P 1750 18150
F 0 "10k?" V 1830 18150 50  0000 C CNN
F 1 "R8" V 1750 18150 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1680 18150 50  0001 C CNN
F 3 "" H 1750 18150 50  0001 C CNN
	1    1750 18150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC4ABA6
P 1900 18450
F 0 "#PWR?" H 1900 18200 50  0001 C CNN
F 1 "GND" H 1900 18300 50  0000 C CNN
F 2 "" H 1900 18450 50  0001 C CNN
F 3 "" H 1900 18450 50  0001 C CNN
	1    1900 18450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BC4AECA
P 600 16650
F 0 "#PWR?" H 600 16500 50  0001 C CNN
F 1 "+3V3" H 600 16790 50  0000 C CNN
F 2 "" H 600 16650 50  0001 C CNN
F 3 "" H 600 16650 50  0001 C CNN
	1    600  16650
	1    0    0    -1  
$EndComp
Text GLabel 10850 10900 2    60   Input ~ 0
PA0
Text GLabel 10850 11000 2    60   Input ~ 0
PA1
Text GLabel 10850 11100 2    60   Input ~ 0
PA2
Text GLabel 10850 11200 2    60   Input ~ 0
PA3
Text GLabel 10850 11300 2    60   Input ~ 0
PA4
Text GLabel 10850 11400 2    60   Input ~ 0
PA5
Text GLabel 10850 11500 2    60   Input ~ 0
PA6
Text GLabel 10850 11600 2    60   Input ~ 0
PA7
Text GLabel 10850 12200 2    60   Input ~ 0
PA13
Text GLabel 10850 12100 2    60   Input ~ 0
PA12
Text GLabel 10850 12000 2    60   Input ~ 0
PA11
Text GLabel 10850 11900 2    60   Input ~ 0
PA10
Text GLabel 10850 11800 2    60   Input ~ 0
PA9
Text GLabel 10850 11700 2    60   Input ~ 0
PA8
Text GLabel 10850 12300 2    60   Input ~ 0
PA14
$Comp
L habiv-board-rescue:Conn_01x16_Male-STM32-rescue J?
U 1 1 5BC4EB19
P 10650 11600
F 0 "J?" H 10650 12400 50  0000 C CNN
F 1 "Conn_01x16_Male" H 10650 10700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16_Pitch2.54mm" H 10650 11600 50  0001 C CNN
F 3 "" H 10650 11600 50  0001 C CNN
	1    10650 11600
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Conn_01x16_Male-STM32-rescue J?
U 1 1 5BC4EE03
P 11450 11600
F 0 "J?" H 11450 12400 50  0000 C CNN
F 1 "Conn_01x16_Male" H 11450 10700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16_Pitch2.54mm" H 11450 11600 50  0001 C CNN
F 3 "" H 11450 11600 50  0001 C CNN
	1    11450 11600
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Conn_01x16_Male-STM32-rescue J?
U 1 1 5BC4EEC1
P 12200 11600
F 0 "J?" H 12200 12400 50  0000 C CNN
F 1 "Conn_01x16_Male" H 12200 10700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16_Pitch2.54mm" H 12200 11600 50  0001 C CNN
F 3 "" H 12200 11600 50  0001 C CNN
	1    12200 11600
	1    0    0    -1  
$EndComp
Text GLabel 10850 12400 2    60   Input ~ 0
PA15
Text GLabel 11650 10900 2    60   Input ~ 0
PB0
Text GLabel 11650 11000 2    60   Input ~ 0
PB1
Text GLabel 11650 11100 2    60   Input ~ 0
PB2
Text GLabel 11650 11200 2    60   Input ~ 0
PB3
Text GLabel 11650 11300 2    60   Input ~ 0
PB4
Text GLabel 11650 11500 2    60   Input ~ 0
PB6
Text GLabel 11650 11600 2    60   Input ~ 0
PB7
Text GLabel 11650 11700 2    60   Input ~ 0
PB8
Text GLabel 11650 11800 2    60   Input ~ 0
PB9
Text GLabel 11650 12300 2    60   Input ~ 0
PB14
Text GLabel 11650 12400 2    60   Input ~ 0
PB15
Text GLabel 11650 11900 2    60   Input ~ 0
PB10
Text GLabel 11650 12100 2    60   Input ~ 0
PB12
Text GLabel 11650 12200 2    60   Input ~ 0
PB13
Text GLabel 11650 11400 2    60   Input ~ 0
PB5
Text GLabel 12400 10900 2    60   Input ~ 0
PC0
Text GLabel 12400 11000 2    60   Input ~ 0
PC1
Text GLabel 12400 11100 2    60   Input ~ 0
PC2
Text GLabel 12400 11200 2    60   Input ~ 0
PC3
Text GLabel 12400 11300 2    60   Input ~ 0
PC4
Text GLabel 12400 11400 2    60   Input ~ 0
PC5
Text GLabel 12400 11500 2    60   Input ~ 0
PC6
Text GLabel 12400 11600 2    60   Input ~ 0
PC7
Text GLabel 12400 11700 2    60   Input ~ 0
PC8
Text GLabel 12400 11800 2    60   Input ~ 0
PC9
Text GLabel 12400 11900 2    60   Input ~ 0
PC10
Text GLabel 12400 12000 2    60   Input ~ 0
PC11
Text GLabel 12400 12100 2    60   Input ~ 0
PC12
Text GLabel 12400 12200 2    60   Input ~ 0
PC13
$Comp
L habiv-board-rescue:Conn_01x02_Male-STM32-rescue J?
U 1 1 5BC51264
P 11100 13150
F 0 "J?" H 11100 13250 50  0000 C CNN
F 1 "Conn_01x02_Male" H 11100 12950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 11100 13150 50  0001 C CNN
F 3 "" H 11100 13150 50  0001 C CNN
	1    11100 13150
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5BC5139A
P 10700 13050
F 0 "#PWR?" H 10700 12900 50  0001 C CNN
F 1 "+3V3" H 10700 13190 50  0000 C CNN
F 2 "" H 10700 13050 50  0001 C CNN
F 3 "" H 10700 13050 50  0001 C CNN
	1    10700 13050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BC51625
P 10700 13150
F 0 "#PWR?" H 10700 12900 50  0001 C CNN
F 1 "GND" H 10700 13000 50  0000 C CNN
F 2 "" H 10700 13150 50  0001 C CNN
F 3 "" H 10700 13150 50  0001 C CNN
	1    10700 13150
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Conn_01x11_Male-STM32-rescue J?
U 1 1 5BC51A5C
P -1200 11450
F 0 "J?" H -1200 12050 50  0000 C CNN
F 1 "Conn_01x11_Male" H -1200 10850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x11_Pitch2.54mm" H -1200 11450 50  0001 C CNN
F 3 "" H -1200 11450 50  0001 C CNN
	1    -1200 11450
	1    0    0    -1  
$EndComp
Text GLabel 12400 12400 2    60   Input ~ 0
PD2
$Comp
L habiv-board-rescue:SW_DPST_x2-STM32-rescue SW?
U 1 1 5BC53F65
P 4450 13900
F 0 "SW?" H 4450 14025 50  0000 C CNN
F 1 "SW_DPST_x2" H 4450 13800 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-1000P" H 4450 13900 50  0001 C CNN
F 3 "" H 4450 13900 50  0001 C CNN
	1    4450 13900
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Crystal_GND23-STM32-rescue Y?
U 1 1 5BC559FA
P 4600 12850
F 0 "Y?" H 4650 13050 50  0000 L CNN
F 1 "32.768MHz" V 4400 12650 50  0000 L CNN
F 2 "Crystals:Crystal_SMD_0603-4pin_6.0x3.5mm_HandSoldering" H 4600 12850 50  0001 C CNN
F 3 "" H 4600 12850 50  0001 C CNN
	1    4600 12850
	0    1    1    0   
$EndComp
Text GLabel 8300 14700 2    60   Input ~ 0
PB11
Text GLabel 11650 12000 2    60   Input ~ 0
PB11
$Comp
L habiv-board-rescue:TPS564208-STM32-rescue U?
U 1 1 5BCD475A
P 14300 15850
F 0 "U?" H 14300 16150 60  0000 C CNN
F 1 "TPS564208" H 14300 15450 60  0000 C CNN
F 2 "TPS564208:TPS564208" H 14450 15900 60  0001 C CNN
F 3 "" H 14450 15900 60  0001 C CNN
	1    14300 15850
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Conn_01x02_Male-STM32-rescue J?
U 1 1 5BCD4B6E
P 13150 15700
F 0 "J?" H 13150 15800 50  0000 C CNN
F 1 "Conn_01x02_Male" H 13150 15500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 13150 15700 50  0001 C CNN
F 3 "" H 13150 15700 50  0001 C CNN
	1    13150 15700
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BCD6316
P 13700 16150
F 0 "C?" H 13725 16250 50  0000 L CNN
F 1 "10uF" H 13725 16050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 13738 16000 50  0001 C CNN
F 3 "" H 13700 16150 50  0001 C CNN
	1    13700 16150
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue R?
U 1 1 5BCD6F1F
P 15650 16250
F 0 "R?" V 15730 16250 50  0000 C CNN
F 1 "10k" V 15550 16250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 15580 16250 50  0001 C CNN
F 3 "" H 15650 16250 50  0001 C CNN
	1    15650 16250
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue R?
U 1 1 5BCD718B
P 15650 15850
F 0 "R?" V 15730 15850 50  0000 C CNN
F 1 "33.2k" V 15550 15850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 15580 15850 50  0001 C CNN
F 3 "" H 15650 15850 50  0001 C CNN
	1    15650 15850
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BCD7B55
P 15000 15800
F 0 "C?" H 15025 15900 50  0000 L CNN
F 1 "100nF" V 15050 15550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 15038 15650 50  0001 C CNN
F 3 "" H 15000 15800 50  0001 C CNN
	1    15000 15800
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:L-STM32-rescue L?
U 1 1 5BCD823C
P 15350 15650
F 0 "L?" V 15300 15650 50  0000 C CNN
F 1 "2.2uH" V 15425 15650 50  0000 C CNN
F 2 "TPS564208:INDC7070X450" H 15350 15650 50  0001 C CNN
F 3 "" H 15350 15650 50  0001 C CNN
	1    15350 15650
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BCD929B
P 16000 16050
F 0 "C?" H 16025 16150 50  0000 L CNN
F 1 "47uF" H 16025 15950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 16038 15900 50  0001 C CNN
F 3 "" H 16000 16050 50  0001 C CNN
	1    16000 16050
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Conn_01x02_Male-STM32-rescue J?
U 1 1 5BCD9ABE
P 16600 15750
F 0 "J?" H 16600 15850 50  0000 C CNN
F 1 "Conn_01x02_Male" H 16600 15550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 16600 15750 50  0001 C CNN
F 3 "" H 16600 15750 50  0001 C CNN
	1    16600 15750
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BCDEC97
P 13700 17250
F 0 "C?" H 13725 17350 50  0000 L CNN
F 1 "10uF" H 13725 17150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 13738 17100 50  0001 C CNN
F 3 "" H 13700 17250 50  0001 C CNN
	1    13700 17250
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue R?
U 1 1 5BCDECA8
P 15650 17350
F 0 "R?" V 15730 17350 50  0000 C CNN
F 1 "10k" V 15550 17350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 15580 17350 50  0001 C CNN
F 3 "" H 15650 17350 50  0001 C CNN
	1    15650 17350
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue R?
U 1 1 5BCDECAE
P 15650 16950
F 0 "R?" V 15730 16950 50  0000 C CNN
F 1 "56.2k" V 15550 16950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 15580 16950 50  0001 C CNN
F 3 "" H 15650 16950 50  0001 C CNN
	1    15650 16950
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BCDECB5
P 15000 16900
F 0 "C?" H 15025 17000 50  0000 L CNN
F 1 "100nF" V 15050 16650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 15038 16750 50  0001 C CNN
F 3 "" H 15000 16900 50  0001 C CNN
	1    15000 16900
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:L-STM32-rescue L?
U 1 1 5BCDECBD
P 15350 16750
F 0 "L?" V 15300 16750 50  0000 C CNN
F 1 "3.3uH" V 15425 16750 50  0000 C CNN
F 2 "TPS564208:INDC7070X450" H 15350 16750 50  0001 C CNN
F 3 "" H 15350 16750 50  0001 C CNN
	1    15350 16750
	0    1    1    0   
$EndComp
$Comp
L habiv-board-rescue:C-STM32-rescue C?
U 1 1 5BCDECCD
P 16000 17150
F 0 "C?" H 16025 17250 50  0000 L CNN
F 1 "47uF" H 16025 17050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 16038 17000 50  0001 C CNN
F 3 "" H 16000 17150 50  0001 C CNN
	1    16000 17150
	1    0    0    -1  
$EndComp
$Comp
L habiv-board-rescue:Conn_01x02_Male-STM32-rescue J?
U 1 1 5BCDECD7
P 16600 16850
F 0 "J?" H 16600 16950 50  0000 C CNN
F 1 "Conn_01x02_Male" H 16600 16650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 16600 16850 50  0001 C CNN
F 3 "" H 16600 16850 50  0001 C CNN
	1    16600 16850
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:TPS564208-STM32-rescue U?
U 1 1 5BCDEC8B
P 14300 16950
F 0 "U?" H 14300 17250 60  0000 C CNN
F 1 "TPS564208" H 14300 16550 60  0000 C CNN
F 2 "TPS564208:TPS564208" H 14450 17000 60  0001 C CNN
F 3 "" H 14450 17000 60  0001 C CNN
	1    14300 16950
	1    0    0    -1  
$EndComp
Text Notes 16750 16800 0    60   ~ 0
5V
Text Notes 16700 15700 0    60   ~ 0
3v3
$Comp
L habiv-board-rescue:LED-STM32-rescue D?
U 1 1 5BCE56BB
P 16250 16950
F 0 "D?" H 16250 17050 50  0000 C CNN
F 1 "LED" H 16250 16850 50  0000 C CNN
F 2 "LEDs:LED_0603_HandSoldering" H 16250 16950 50  0001 C CNN
F 3 "" H 16250 16950 50  0001 C CNN
	1    16250 16950
	0    -1   -1   0   
$EndComp
$Comp
L habiv-board-rescue:LED-STM32-rescue D?
U 1 1 5BCE5851
P 16250 15850
F 0 "D?" H 16250 15950 50  0000 C CNN
F 1 "LED" H 16250 15750 50  0000 C CNN
F 2 "LEDs:LED_0603_HandSoldering" H 16250 15850 50  0001 C CNN
F 3 "" H 16250 15850 50  0001 C CNN
	1    16250 15850
	0    -1   -1   0   
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue R?
U 1 1 5BCE59FC
P 16250 16250
F 0 "R?" V 16330 16250 50  0000 C CNN
F 1 "4.7k" V 16150 16250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 16180 16250 50  0001 C CNN
F 3 "" H 16250 16250 50  0001 C CNN
	1    16250 16250
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:R-STM32-rescue R?
U 1 1 5BCE5FC3
P 16250 17350
F 0 "R?" V 16330 17350 50  0000 C CNN
F 1 "4.7k" V 16150 17350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 16180 17350 50  0001 C CNN
F 3 "" H 16250 17350 50  0001 C CNN
	1    16250 17350
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:Conn_01x05_Male-STM32-rescue J?
U 1 1 5BCE79FC
P 17100 17000
F 0 "J?" H 17100 17300 50  0000 C CNN
F 1 "Conn_01x05_Male" H 17100 16700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 17100 17000 50  0001 C CNN
F 3 "" H 17100 17000 50  0001 C CNN
	1    17100 17000
	-1   0    0    1   
$EndComp
$Comp
L habiv-board-rescue:Conn_01x04_Male-STM32-rescue J?
U 1 1 5BCE8043
P 16750 16250
F 0 "J?" H 16750 16450 50  0000 C CNN
F 1 "Conn_01x04_Male" H 16750 15950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 16750 16250 50  0001 C CNN
F 3 "" H 16750 16250 50  0001 C CNN
	1    16750 16250
	-1   0    0    1   
$EndComp
Wire Wire Line
	6150 12450 6150 12550
Wire Wire Line
	6150 12550 6250 12550
Wire Wire Line
	5200 12850 5200 13000
Wire Wire Line
	4300 12950 4400 12950
Wire Wire Line
	4400 12950 4400 13000
Connection ~ 4600 13000
Connection ~ 4600 12700
Connection ~ 4000 12950
Wire Wire Line
	5200 12700 5200 12750
Wire Wire Line
	5200 12750 6250 12750
Wire Wire Line
	5200 12850 6250 12850
Wire Wire Line
	4650 13900 4700 13900
Connection ~ 4700 13900
Wire Wire Line
	4700 14350 4600 14350
Wire Wire Line
	4250 14350 4300 14350
Wire Wire Line
	4250 13900 4250 14350
Connection ~ 4250 14350
Wire Wire Line
	4700 13950 4750 13950
Connection ~ 4700 13950
Wire Wire Line
	5550 14550 5550 14600
Wire Wire Line
	5300 14550 5550 14550
Connection ~ 5300 14250
Wire Wire Line
	5800 14550 5800 13650
Connection ~ 5550 14550
Wire Wire Line
	5300 14250 5300 14200
Wire Wire Line
	5300 14250 5550 14250
Wire Wire Line
	5200 12700 5100 12700
Wire Wire Line
	4300 12700 4600 12700
Wire Wire Line
	4400 13000 4600 13000
Wire Wire Line
	5200 13000 5100 13000
Wire Wire Line
	5100 13550 5100 13650
Wire Wire Line
	5100 13650 4700 13650
Wire Wire Line
	4700 13650 4700 13900
Wire Wire Line
	5550 13750 6250 13750
Wire Wire Line
	5800 13650 6250 13650
Wire Wire Line
	6250 13150 5400 13150
Wire Wire Line
	5400 13150 5400 13550
Wire Wire Line
	5400 13550 5100 13550
Wire Wire Line
	5550 14250 5550 13750
Wire Wire Line
	9050 12300 9050 12350
Connection ~ 8800 12000
Connection ~ 9050 12300
Wire Wire Line
	8550 12000 8800 12000
Wire Wire Line
	8800 12300 8900 12300
Wire Wire Line
	9050 12000 9050 11950
Wire Wire Line
	7100 15550 7100 15600
Connection ~ 6850 15250
Connection ~ 7100 15550
Wire Wire Line
	6850 14450 6850 15250
Wire Wire Line
	6850 15250 7100 15250
Wire Wire Line
	6850 15550 7100 15550
Wire Wire Line
	7100 15250 7100 15200
Wire Wire Line
	7950 14450 7950 14700
Wire Wire Line
	8550 12000 8550 12550
Wire Wire Line
	8550 12650 8900 12650
Wire Wire Line
	8900 12650 8900 12300
Connection ~ 8900 12300
Wire Wire Line
	8400 15550 8400 15600
Connection ~ 8150 15250
Connection ~ 8400 15550
Wire Wire Line
	8150 14450 8150 15250
Wire Wire Line
	8150 15250 8400 15250
Wire Wire Line
	8150 15550 8400 15550
Wire Wire Line
	8400 15250 8400 15200
Wire Wire Line
	6400 12000 6400 12050
Connection ~ 6400 12000
Wire Wire Line
	6150 11700 6400 11700
Wire Wire Line
	6150 12000 6400 12000
Wire Wire Line
	6400 11700 6400 11650
Wire Wire Line
	6650 11700 6650 12150
Connection ~ 6400 11700
Wire Wire Line
	7050 11750 7050 12150
Wire Wire Line
	6750 12000 6750 12150
Wire Wire Line
	7050 11100 6900 11100
Wire Wire Line
	6900 11100 6900 11150
Wire Wire Line
	7050 11100 7050 11450
Wire Wire Line
	1300 17400 1600 17400
Wire Wire Line
	1300 18000 1600 18000
Wire Wire Line
	1300 18100 1500 18100
Wire Wire Line
	1500 18100 1500 18150
Wire Wire Line
	1500 18150 1600 18150
Wire Wire Line
	1900 17400 1900 18000
Connection ~ 1900 18000
Connection ~ 1900 18150
Wire Wire Line
	600  18400 1900 18400
Connection ~ 1900 18400
Wire Wire Line
	600  16650 600  16700
Wire Wire Line
	700  16800 700  16700
Wire Wire Line
	700  16700 600  16700
Connection ~ 600  16700
Wire Wire Line
	10700 13050 10900 13050
Wire Wire Line
	10700 13150 10900 13150
Wire Wire Line
	-950 11950 -950 12150
Wire Wire Line
	-950 12150 750  12150
Wire Wire Line
	750  12150 750  11850
Wire Wire Line
	-1000 10950 -950 10950
Wire Wire Line
	-1000 11050 -950 11050
Wire Wire Line
	-1000 11150 -950 11150
Wire Wire Line
	-1000 11250 -950 11250
Wire Wire Line
	-1000 11350 -950 11350
Wire Wire Line
	-1000 11450 -950 11450
Wire Wire Line
	-1000 11550 -950 11550
Wire Wire Line
	-1000 11650 -950 11650
Wire Wire Line
	-1000 11750 -950 11750
Wire Wire Line
	-1000 11850 -950 11850
Wire Wire Line
	-1000 11950 -950 11950
Wire Wire Line
	4000 12700 4000 12950
Wire Wire Line
	7950 14700 8300 14700
Connection ~ 7950 14700
Wire Wire Line
	13350 15700 13450 15700
Wire Wire Line
	13700 15700 13700 15850
Wire Wire Line
	13700 15850 13850 15850
Connection ~ 13700 15700
Wire Wire Line
	13350 15800 13400 15800
Wire Wire Line
	13500 15800 13500 16500
Connection ~ 13700 15850
Wire Wire Line
	13700 16300 13700 16500
Connection ~ 13700 16500
Wire Wire Line
	14800 16500 14800 16100
Connection ~ 14800 16500
Wire Wire Line
	15650 16000 15650 16050
Wire Wire Line
	14800 15800 14850 15800
Connection ~ 15650 16050
Wire Wire Line
	14800 15650 15150 15650
Wire Wire Line
	15150 15800 15150 15650
Connection ~ 15150 15650
Wire Wire Line
	14800 15950 15250 15950
Wire Wire Line
	15250 15950 15250 16050
Wire Wire Line
	15250 16050 15650 16050
Wire Wire Line
	15650 16500 15650 16400
Connection ~ 15650 16500
Wire Wire Line
	15500 15650 15650 15650
Wire Wire Line
	15650 15650 15650 15700
Wire Wire Line
	16000 15650 16000 15900
Connection ~ 15650 15650
Wire Wire Line
	16000 16500 16000 16200
Connection ~ 16000 16500
Connection ~ 16000 15650
Wire Wire Line
	13500 16500 13700 16500
Wire Wire Line
	16400 16500 16400 16050
Wire Wire Line
	13700 16800 13700 16950
Wire Wire Line
	13700 16950 13850 16950
Connection ~ 13700 16800
Wire Wire Line
	13500 16900 13500 17600
Connection ~ 13700 16950
Wire Wire Line
	13700 17400 13700 17600
Connection ~ 13700 17600
Wire Wire Line
	14800 17600 14800 17200
Connection ~ 14800 17600
Wire Wire Line
	15650 17100 15650 17150
Wire Wire Line
	14800 16900 14850 16900
Connection ~ 15650 17150
Wire Wire Line
	14800 16750 15150 16750
Wire Wire Line
	15150 16900 15150 16750
Connection ~ 15150 16750
Wire Wire Line
	14800 17050 15250 17050
Wire Wire Line
	15250 17050 15250 17150
Wire Wire Line
	15250 17150 15650 17150
Wire Wire Line
	15650 17600 15650 17500
Connection ~ 15650 17600
Wire Wire Line
	15500 16750 15650 16750
Wire Wire Line
	15650 16750 15650 16800
Wire Wire Line
	16000 16750 16000 17000
Connection ~ 15650 16750
Wire Wire Line
	16000 17600 16000 17300
Connection ~ 16000 17600
Connection ~ 16000 16750
Wire Wire Line
	13500 17600 13700 17600
Wire Wire Line
	16400 17600 16400 17050
Wire Wire Line
	13450 16800 13700 16800
Wire Wire Line
	13450 16800 13450 15700
Connection ~ 13450 15700
Wire Wire Line
	13500 16900 13400 16900
Wire Wire Line
	13400 16900 13400 15800
Connection ~ 13400 15800
Wire Wire Line
	16250 15650 16250 15700
Connection ~ 16250 15650
Wire Wire Line
	16250 16000 16250 16100
Wire Wire Line
	16250 16400 16250 16500
Connection ~ 16250 16500
Wire Wire Line
	16250 16750 16250 16800
Connection ~ 16250 16750
Wire Wire Line
	16250 17100 16250 17200
Wire Wire Line
	16250 17500 16250 17600
Connection ~ 16250 17600
Wire Wire Line
	16550 16050 16550 16150
Connection ~ 16550 16150
Connection ~ 16550 16250
Connection ~ 16450 15350
Connection ~ 16450 15250
Connection ~ 16450 15150
Connection ~ 16450 15050
Connection ~ 16500 17050
Connection ~ 16500 17150
Wire Wire Line
	16400 17050 16500 17050
Connection ~ 16400 17050
Wire Wire Line
	16400 16750 16400 16600
Wire Wire Line
	16400 16600 16900 16600
Wire Wire Line
	16900 16600 16900 16800
Connection ~ 16900 16800
Connection ~ 16900 16900
Connection ~ 16900 17000
Connection ~ 16900 17100
Wire Wire Line
	16400 16050 16550 16050
Connection ~ 16400 16050
Wire Wire Line
	16400 15650 16400 15350
Wire Wire Line
	16400 15350 16450 15350
Wire Wire Line
	16450 15350 16450 15250
$Comp
L habiv-board-rescue:Conn_01x08_Male-STM32-rescue J?
U 1 1 5BCEBE6C
P 16650 15050
F 0 "J?" H 16650 15450 50  0000 C CNN
F 1 "Conn_01x08_Male" H 16650 14550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 16650 15050 50  0001 C CNN
F 3 "" H 16650 15050 50  0001 C CNN
	1    16650 15050
	-1   0    0    1   
$EndComp
Connection ~ 16450 14950
Connection ~ 16450 14850
Connection ~ 16450 14750
$Comp
L habiv-board-rescue:Conn_01x03_Male-STM32-rescue J?
U 1 1 5BCEC4E6
P 16700 17150
F 0 "J?" H 16700 17350 50  0000 C CNN
F 1 "Conn_01x03_Male" H 16700 16950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 16700 17150 50  0001 C CNN
F 3 "" H 16700 17150 50  0001 C CNN
	1    16700 17150
	-1   0    0    1   
$EndComp
Wire Wire Line
	16500 17050 16500 17150
Wire Wire Line
	4600 13000 4800 13000
Wire Wire Line
	4600 12700 4800 12700
Wire Wire Line
	4000 12950 4000 13200
Wire Wire Line
	4700 13900 4700 13950
Wire Wire Line
	4250 14350 4250 14400
Wire Wire Line
	4700 13950 4700 14350
Wire Wire Line
	5550 14550 5800 14550
Wire Wire Line
	8800 12000 9050 12000
Wire Wire Line
	8900 12300 9050 12300
Wire Wire Line
	6400 12000 6750 12000
Wire Wire Line
	6400 11700 6650 11700
Wire Wire Line
	1900 18000 1900 18150
Wire Wire Line
	1900 18150 1900 18400
Wire Wire Line
	1900 18400 1900 18450
Wire Wire Line
	600  16700 600  16800
Wire Wire Line
	7950 14700 7950 14750
Wire Wire Line
	13700 15700 13850 15700
Wire Wire Line
	13700 15850 13700 16000
Wire Wire Line
	13700 16500 14800 16500
Wire Wire Line
	14800 16500 15650 16500
Wire Wire Line
	15650 16050 15650 16100
Wire Wire Line
	15150 15650 15200 15650
Wire Wire Line
	15650 16500 16000 16500
Wire Wire Line
	15650 15650 16000 15650
Wire Wire Line
	16000 16500 16250 16500
Wire Wire Line
	16000 15650 16250 15650
Wire Wire Line
	13700 16800 13850 16800
Wire Wire Line
	13700 16950 13700 17100
Wire Wire Line
	13700 17600 14800 17600
Wire Wire Line
	14800 17600 15650 17600
Wire Wire Line
	15650 17150 15650 17200
Wire Wire Line
	15150 16750 15200 16750
Wire Wire Line
	15650 17600 16000 17600
Wire Wire Line
	15650 16750 16000 16750
Wire Wire Line
	16000 17600 16250 17600
Wire Wire Line
	16000 16750 16250 16750
Wire Wire Line
	13450 15700 13700 15700
Wire Wire Line
	13400 15800 13500 15800
Wire Wire Line
	16250 15650 16400 15650
Wire Wire Line
	16250 16500 16400 16500
Wire Wire Line
	16250 16750 16400 16750
Wire Wire Line
	16250 17600 16400 17600
Wire Wire Line
	16550 16150 16550 16250
Wire Wire Line
	16550 16250 16550 16350
Wire Wire Line
	16450 15250 16450 15150
Wire Wire Line
	16450 15150 16450 15050
Wire Wire Line
	16450 15050 16450 14950
Wire Wire Line
	16500 17150 16500 17250
Wire Wire Line
	16400 17050 16400 16850
Wire Wire Line
	16900 16800 16900 16900
Wire Wire Line
	16900 16900 16900 17000
Wire Wire Line
	16900 17000 16900 17100
Wire Wire Line
	16900 17100 16900 17200
Wire Wire Line
	16400 16050 16400 15750
Wire Wire Line
	16450 14950 16450 14850
Wire Wire Line
	16450 14850 16450 14750
Wire Wire Line
	16450 14750 16450 14650
Connection ~ 5550 13750
Connection ~ 5550 14250
Connection ~ 7100 15250
Connection ~ 8400 15250
Connection ~ 9050 12000
Connection ~ 16400 15650
Connection ~ 16400 16750
Connection ~ 16550 16050
$EndSCHEMATC
