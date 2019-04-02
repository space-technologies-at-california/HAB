EESchema Schematic File Version 4
LIBS:Adafruit Ultimate GPS-cache
EELAYER 26 0
EELAYER END
$Descr User 12296 8268
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
Wire Wire Line
	7250 1800 7550 1800
Wire Wire Line
	7550 1800 7550 1900
Text Label 7250 1800 0    10   ~ 0
GND
Text Label 5950 1800 0    70   ~ 0
VBACKUP
Wire Wire Line
	6750 1800 7050 1800
$Comp
L Adafruit_Ultimate_GPS-eagle-import:BATTERYCR1220_SMT B1
U 1 0 96DDDAD98A000202
P 7150 1800
F 0 "B1" H 7050 1925 42  0000 L BNN
F 1 "CR1220" H 7050 1600 42  0000 L BNN
F 2 "Adafruit Ultimate GPS:CR1220" H 7150 1800 50  0001 C CNN
F 3 "" H 7150 1800 50  0001 C CNN
	1    7150 1800
	-1   0    0    1   
$EndComp
$Comp
L Adafruit_Ultimate_GPS-eagle-import:GND #U$0101
U 1 0 25B093F9D405EDE5
P 7550 2000
F 0 "#U$0101" H 7550 2000 50  0001 C CNN
F 1 "GND" H 7490 1900 42  0000 L BNN
F 2 "" H 7550 2000 50  0001 C CNN
F 3 "" H 7550 2000 50  0001 C CNN
	1    7550 2000
	1    0    0    -1  
$EndComp
$Comp
L Adafruit_Ultimate_GPS-eagle-import:DIODESOD-323 D2
U 1 0 A3EFA98ECB5A3888
P 6650 1800
F 0 "D2" H 6650 1900 42  0000 C CNN
F 1 "CUS520" H 6650 1702 42  0000 C CNN
F 2 "Adafruit Ultimate GPS:SOD-323" H 6650 1800 50  0001 C CNN
F 3 "" H 6650 1800 50  0001 C CNN
	1    6650 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	5350 3500 5200 3500
Text Label 4750 3500 0    70   ~ 0
FIX
Wire Wire Line
	4350 3500 4250 3500
Wire Wire Line
	3850 3500 3750 3500
Wire Wire Line
	3750 3500 3750 3800
Wire Wire Line
	3750 3800 3750 4000
Wire Wire Line
	3750 3200 3750 3300
Wire Wire Line
	3750 3300 3750 3500
Wire Wire Line
	5350 3800 3750 3800
Wire Wire Line
	5350 3300 3750 3300
Connection ~ 3750 3500
Connection ~ 3750 3800
Connection ~ 3750 3300
Text Label 3850 3500 0    10   ~ 0
GND
Wire Wire Line
	6550 3900 7350 3900
Wire Wire Line
	7350 3900 7350 4200
Wire Wire Line
	7350 4200 7350 4300
Wire Wire Line
	7350 4300 7350 4400
Wire Wire Line
	6550 3200 7350 3200
Wire Wire Line
	7350 3200 7350 3900
Wire Wire Line
	7050 4300 7350 4300
Wire Wire Line
	7050 4200 7350 4200
Connection ~ 7350 3900
Connection ~ 7350 4300
Connection ~ 7350 4200
Text Label 6550 3900 0    10   ~ 0
GND
Wire Wire Line
	3750 2900 3750 2800
Wire Wire Line
	3750 2800 4750 2800
Wire Wire Line
	5350 3100 4750 3100
Text Label 3750 2900 0    10   ~ 0
3.3V
Wire Wire Line
	5350 3400 4750 3400
Text Label 4750 3400 0    70   ~ 0
VBACKUP
Wire Wire Line
	5350 3900 5200 3900
Wire Wire Line
	5350 4000 5200 4000
Wire Wire Line
	4250 4900 4250 4800
Connection ~ 4650 4000
Wire Wire Line
	6550 4000 6750 4000
Wire Wire Line
	6550 3800 7050 3800
Text Label 6750 3800 0    70   ~ 0
1PPS
$Comp
L Adafruit-Ultimate-GPS-rescue:GPS_FGPMMOPA6H-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue U3
U 1 0 2DF3FE209D0AA111
P 5950 3500
F 0 "U3" H 5450 4400 42  0000 L BNN
F 1 "FGPMMOPA6H" H 5450 2500 42  0000 L BNN
F 2 "Adafruit Ultimate GPS:FGPMMOPA6H" H 5950 3500 50  0001 C CNN
F 3 "" H 5950 3500 50  0001 C CNN
	1    5950 3500
	1    0    0    -1  
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:LED0805-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue LED1
U 1 0 5CA3FB4A
P 4450 3500
F 0 "LED1" H 4400 3675 42  0000 C CNN
F 1 "RED" H 4400 3390 42  0000 C CNN
F 2 "Adafruit Ultimate GPS:CHIPLED_0805" H 4450 3500 50  0001 C CNN
F 3 "" H 4450 3500 50  0001 C CNN
	1    4450 3500
	-1   0    0    1   
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:RESISTOR0805_NOOUTLINE-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue R23
U 1 0 5CA3FB47
P 4050 3500
F 0 "R23" H 4050 3600 50  0000 C CNN
F 1 "1K" H 4050 3500 40  0000 C CNB
F 2 "Resistor_SMD:R_0805_2012Metric" H 4050 3500 50  0001 C CNN
F 3 "" H 4050 3500 50  0001 C CNN
	1    4050 3500
	1    0    0    -1  
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:GND-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue #U$0102
U 1 0 803D2E8F6197D135
P 3750 4100
F 0 "#U$0102" H 3750 4100 50  0001 C CNN
F 1 "GND" H 3690 4000 42  0000 L BNN
F 2 "" H 3750 4100 50  0001 C CNN
F 3 "" H 3750 4100 50  0001 C CNN
	1    3750 4100
	1    0    0    -1  
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:3.3V-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue #U$0103
U 1 0 C4F885289A709B56
P 4750 2300
F 0 "#U$0103" H 4750 2300 50  0001 C CNN
F 1 "3.3V" H 4690 2340 42  0000 L BNN
F 2 "" H 4750 2300 50  0001 C CNN
F 3 "" H 4750 2300 50  0001 C CNN
	1    4750 2300
	1    0    0    -1  
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:CAP_CERAMIC0805-NOOUTLINE-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue C7
U 1 0 5CA3FB45
P 3750 3100
F 0 "C7" V 3660 3149 50  0000 C CNN
F 1 "0.1uF" V 3840 3149 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3750 3100 50  0001 C CNN
F 3 "" H 3750 3100 50  0001 C CNN
	1    3750 3100
	1    0    0    -1  
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:DIODESOD-323-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue D1
U 1 0 5CA3FB48
P 4300 4000
F 0 "D1" H 4300 4100 42  0000 C CNN
F 1 "1N4148" H 4300 3902 42  0000 C CNN
F 2 "Adafruit Ultimate GPS:SOD-323" H 4300 4000 50  0001 C CNN
F 3 "" H 4300 4000 50  0001 C CNN
	1    4300 4000
	-1   0    0    1   
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:RESISTOR0805_NOOUTLINE-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue R24
U 1 0 4F14531CD85E66C8
P 4250 4600
F 0 "R24" H 4250 4700 50  0000 C CNN
F 1 "10K" H 4250 4600 40  0000 C CNB
F 2 "Resistor_SMD:R_0805_2012Metric" H 4250 4600 50  0001 C CNN
F 3 "" H 4250 4600 50  0001 C CNN
	1    4250 4600
	0    1    1    0   
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:3.3V-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue #U$0104
U 1 0 5CA3FB46
P 4250 4300
F 0 "#U$0104" H 4250 4300 50  0001 C CNN
F 1 "3.3V" H 4190 4340 42  0000 L BNN
F 2 "" H 4250 4300 50  0001 C CNN
F 3 "" H 4250 4300 50  0001 C CNN
	1    4250 4300
	1    0    0    -1  
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:GND-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue #U$0105
U 1 0 5CA3FB44
P 7350 4500
F 0 "#U$0105" H 7350 4500 50  0001 C CNN
F 1 "GND" H 7290 4400 42  0000 L BNN
F 2 "" H 7350 4500 50  0001 C CNN
F 3 "" H 7350 4500 50  0001 C CNN
	1    7350 4500
	1    0    0    -1  
$EndComp
$Comp
L Adafruit-Ultimate-GPS-rescue:U.FL-Adafruit_Ultimate_GPS-eagle-import-habiv-board-rescue U$1
U 1 0 14A4E007DC93C178
P 6950 4000
F 0 "U$1" H 6950 4000 50  0001 C CNN
F 1 "U.FL" H 6950 4000 50  0001 C CNN
F 2 "Adafruit Ultimate GPS:U.FL" H 6950 4000 50  0001 C CNN
F 3 "" H 6950 4000 50  0001 C CNN
	1    6950 4000
	-1   0    0    -1  
$EndComp
Text Notes 4750 4700 0    59   ~ 0
D1+R3 restrict RX input to 3.3V
Text GLabel 4750 3900 0    50   Input ~ 0
PA10
Wire Wire Line
	4400 4000 4650 4000
Wire Wire Line
	4200 4000 4050 4000
Text GLabel 4050 4000 0    50   Input ~ 0
PB6
Wire Wire Line
	4650 4900 4250 4900
Wire Wire Line
	4650 4000 4650 4900
Wire Notes Line
	21500 13150 21500 13200
$Comp
L Device:R R25
U 1 1 5D048A73
P 4750 2550
F 0 "R25" H 4820 2596 50  0000 L CNN
F 1 "0" V 4750 2500 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4680 2550 50  0001 C CNN
F 3 "~" H 4750 2550 50  0001 C CNN
	1    4750 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2700 4750 2800
Wire Wire Line
	4750 2800 4750 3100
Connection ~ 4750 2800
$Comp
L Device:R R27
U 1 1 5D392E5B
P 5050 3900
F 0 "R27" H 5250 3950 50  0000 L CNN
F 1 "0" V 5050 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4980 3900 50  0001 C CNN
F 3 "~" H 5050 3900 50  0001 C CNN
	1    5050 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 3900 4750 3900
$Comp
L Device:R R28
U 1 1 5D394D2A
P 5050 4000
F 0 "R28" H 5150 3950 50  0000 L CNN
F 1 "0" V 5050 3950 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4980 4000 50  0001 C CNN
F 3 "~" H 5050 4000 50  0001 C CNN
	1    5050 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 4000 4650 4000
Text GLabel 4800 3650 0    60   Input ~ 0
PB15
$Comp
L Device:R R26
U 1 1 5D73E76D
P 5050 3650
F 0 "R26" H 5100 3700 50  0000 L CNN
F 1 "0" V 5050 3600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4980 3650 50  0001 C CNN
F 3 "~" H 5050 3650 50  0001 C CNN
	1    5050 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 3650 4900 3650
Wire Wire Line
	5200 3650 5200 3500
Connection ~ 5200 3500
Wire Wire Line
	5200 3500 4650 3500
Wire Wire Line
	6550 1800 5950 1800
$EndSCHEMATC
