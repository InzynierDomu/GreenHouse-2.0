EESchema Schematic File Version 4
EELAYER 30 0
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
L Memory_EEPROM:CAT24C128 U3
U 1 1 628CA552
P 6800 2600
F 0 "U3" H 6900 2950 50  0000 C CNN
F 1 "CAT24C16" H 7000 2850 50  0000 C CNN
F 2 "" H 6800 2600 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/CAT24C128-D.PDF" H 6800 2600 50  0001 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
$Comp
L 113990105:113990105 U4
U 1 1 628CE409
P 6850 3850
F 0 "U4" H 8400 4115 50  0000 C CNN
F 1 "113990105" H 8400 4024 50  0000 C CNN
F 2 "113990105" H 9800 3950 50  0001 L CNN
F 3 "https://www.seeedstudio.com/NodeMCU-v2-Lua-based-ESP8266-development-kit.html" H 9800 3850 50  0001 L CNN
F 4 "NodeMCU DEVKIT V1.0" H 9800 3750 50  0001 L CNN "Description"
F 5 "7.35" H 9800 3650 50  0001 L CNN "Height"
F 6 "Seeed Studio" H 9800 3550 50  0001 L CNN "Manufacturer_Name"
F 7 "113990105" H 9800 3450 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "713-113990105" H 9800 3350 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Seeed-Studio/113990105?qs=SElPoaY2y5KMx8k1roAIKw%3D%3D" H 9800 3250 50  0001 L CNN "Mouser Price/Stock"
F 10 "113990105" H 9800 3150 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/113990105/seeed-technology-limited?region=nac" H 9800 3050 50  0001 L CNN "Arrow Price/Stock"
	1    6850 3850
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion:MCP23017_SP U1
U 1 1 628D071A
P 1550 4500
F 0 "U1" H 1550 5781 50  0000 C CNN
F 1 "MCP23017_SP" H 1550 5690 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 1750 3500 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf" H 1750 3400 50  0001 L CNN
	1    1550 4500
	1    0    0    -1  
$EndComp
$Comp
L Timer_RTC:DS1307+ U5
U 1 1 628D1D0B
P 10050 2500
F 0 "U5" H 10594 2546 50  0000 L CNN
F 1 "DS1307+" H 10594 2455 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 10050 2000 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1307.pdf" H 10050 2300 50  0001 C CNN
	1    10050 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 628CAB63
P 6300 3050
F 0 "#PWR0101" H 6300 2800 50  0001 C CNN
F 1 "GND" H 6305 2877 50  0000 C CNN
F 2 "" H 6300 3050 50  0001 C CNN
F 3 "" H 6300 3050 50  0001 C CNN
	1    6300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2700 6400 2700
Wire Wire Line
	6300 2700 6300 2600
Wire Wire Line
	6300 2600 6400 2600
Connection ~ 6300 2700
Wire Wire Line
	6300 2600 6300 2500
Wire Wire Line
	6300 2500 6400 2500
Connection ~ 6300 2600
Wire Wire Line
	6300 2700 6300 2950
Wire Wire Line
	6800 2900 6800 2950
Wire Wire Line
	6800 2950 6300 2950
Connection ~ 6300 2950
Wire Wire Line
	6300 2950 6300 3050
$Comp
L power:+3.3V #PWR0102
U 1 1 628CE141
P 6800 2000
F 0 "#PWR0102" H 6800 1850 50  0001 C CNN
F 1 "+3.3V" H 6815 2173 50  0000 C CNN
F 2 "" H 6800 2000 50  0001 C CNN
F 3 "" H 6800 2000 50  0001 C CNN
	1    6800 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2000 6800 2300
$Comp
L power:+BATT #PWR0103
U 1 1 628E3BAA
P 10050 2000
F 0 "#PWR0103" H 10050 1850 50  0001 C CNN
F 1 "+BATT" H 10183 2173 50  0000 C CNN
F 2 "" H 10050 2000 50  0001 C CNN
F 3 "" H 10050 2000 50  0001 C CNN
	1    10050 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0104
U 1 1 628E49DB
P 9950 2000
F 0 "#PWR0104" H 9950 1850 50  0001 C CNN
F 1 "+3.3V" H 9886 2173 50  0000 C CNN
F 2 "" H 9950 2000 50  0001 C CNN
F 3 "" H 9950 2000 50  0001 C CNN
	1    9950 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 628E4C76
P 10050 3050
F 0 "#PWR0105" H 10050 2800 50  0001 C CNN
F 1 "GND" H 10055 2877 50  0000 C CNN
F 2 "" H 10050 3050 50  0001 C CNN
F 3 "" H 10050 3050 50  0001 C CNN
	1    10050 3050
	1    0    0    -1  
$EndComp
Text GLabel 7300 2500 2    50   Input ~ 0
SDA
Text GLabel 7300 2600 2    50   Input ~ 0
SCL
Text GLabel 9450 2400 0    50   Input ~ 0
SDA
Text GLabel 9450 2300 0    50   Input ~ 0
SCL
Text GLabel 10050 4050 2    50   Input ~ 0
SDA
Text GLabel 10050 3950 2    50   Input ~ 0
SCL
$Comp
L SSD1306-128x64_OLED:SSD1306 Brd1
U 1 1 628E587B
P 8050 2650
F 0 "Brd1" V 7635 2708 50  0000 C CNN
F 1 "SSD1306" V 7726 2708 50  0000 C CNN
F 2 "" H 8050 2900 50  0001 C CNN
F 3 "" H 8050 2900 50  0001 C CNN
	1    8050 2650
	0    1    1    0   
$EndComp
Text GLabel 8500 2800 2    50   Input ~ 0
SDA
Text GLabel 8500 2700 2    50   Input ~ 0
SCL
Wire Wire Line
	8400 2700 8500 2700
Wire Wire Line
	8400 2800 8500 2800
Wire Wire Line
	7200 2500 7300 2500
Wire Wire Line
	7200 2600 7300 2600
Wire Wire Line
	9950 2000 9950 2100
Wire Wire Line
	10050 2000 10050 2100
Wire Wire Line
	9450 2300 9550 2300
Wire Wire Line
	9450 2400 9550 2400
Wire Wire Line
	9250 2500 9450 2500
Wire Wire Line
	9450 2500 9450 2600
Wire Wire Line
	9450 2600 9550 2600
Wire Wire Line
	9550 2700 9450 2700
Wire Wire Line
	9450 2700 9450 2800
Wire Wire Line
	9450 2800 9250 2800
$Comp
L power:GND #PWR0106
U 1 1 628EC3A6
P 8450 3050
F 0 "#PWR0106" H 8450 2800 50  0001 C CNN
F 1 "GND" H 8455 2877 50  0000 C CNN
F 2 "" H 8450 3050 50  0001 C CNN
F 3 "" H 8450 3050 50  0001 C CNN
	1    8450 3050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0107
U 1 1 628EC79F
P 8450 2000
F 0 "#PWR0107" H 8450 1850 50  0001 C CNN
F 1 "+3.3V" H 8465 2173 50  0000 C CNN
F 2 "" H 8450 2000 50  0001 C CNN
F 3 "" H 8450 2000 50  0001 C CNN
	1    8450 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2500 8450 2500
Wire Wire Line
	8400 2600 8450 2600
Wire Wire Line
	9950 3950 10050 3950
Wire Wire Line
	10050 4050 9950 4050
$Comp
L power:GND #PWR0108
U 1 1 628EEE86
P 10150 5300
F 0 "#PWR0108" H 10150 5050 50  0001 C CNN
F 1 "GND" H 10155 5127 50  0000 C CNN
F 2 "" H 10150 5300 50  0001 C CNN
F 3 "" H 10150 5300 50  0001 C CNN
	1    10150 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 5150 10150 5150
Wire Wire Line
	10150 5150 10150 5300
$Comp
L power:+3.3V #PWR0109
U 1 1 628EFE0D
P 10250 5100
F 0 "#PWR0109" H 10250 4950 50  0001 C CNN
F 1 "+3.3V" H 10265 5273 50  0000 C CNN
F 2 "" H 10250 5100 50  0001 C CNN
F 3 "" H 10250 5100 50  0001 C CNN
	1    10250 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 5250 10250 5250
Wire Wire Line
	10250 5250 10250 5100
Wire Wire Line
	8450 2000 8450 2500
Wire Wire Line
	8450 2600 8450 3050
Wire Wire Line
	10050 2900 10050 3050
$Comp
L Connector:SD_Card J1
U 1 1 629124D4
P 4500 3950
F 0 "J1" H 4500 3285 50  0000 C CNN
F 1 "SD_Card" H 4500 3376 50  0000 C CNN
F 2 "" H 4500 3950 50  0001 C CNN
F 3 "http://portal.fciconnect.com/Comergent//fci/drawing/10067847.pdf" H 4500 3950 50  0001 C CNN
	1    4500 3950
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0110
U 1 1 62915451
P 5950 3900
F 0 "#PWR0110" H 5950 3750 50  0001 C CNN
F 1 "+3.3V" H 5965 4073 50  0000 C CNN
F 2 "" H 5950 3900 50  0001 C CNN
F 3 "" H 5950 3900 50  0001 C CNN
	1    5950 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 6291860E
P 5950 4100
F 0 "#PWR0111" H 5950 3850 50  0001 C CNN
F 1 "GND" H 5955 3927 50  0000 C CNN
F 2 "" H 5950 4100 50  0001 C CNN
F 3 "" H 5950 4100 50  0001 C CNN
	1    5950 4100
	1    0    0    -1  
$EndComp
Text GLabel 10100 4850 2    50   Input ~ 0
SD_CS
Wire Wire Line
	9950 4850 10100 4850
Text GLabel 5500 4250 2    50   Input ~ 0
SD_CS
Wire Wire Line
	5400 4250 5500 4250
Wire Wire Line
	5950 4050 5950 4100
Text GLabel 6750 4550 0    50   Input ~ 0
SD_D0
Text GLabel 6750 4450 0    50   Input ~ 0
SD_CMD
Text GLabel 6750 4650 0    50   Input ~ 0
SD_CLK
Wire Wire Line
	6750 4450 6850 4450
Wire Wire Line
	6750 4550 6850 4550
Wire Wire Line
	6750 4650 6850 4650
Text GLabel 5500 3650 2    50   Input ~ 0
SD_D0
Text GLabel 5500 4150 2    50   Input ~ 0
SD_CMD
Text GLabel 5500 3850 2    50   Input ~ 0
SD_CLK
Wire Wire Line
	5400 4050 5450 4050
Wire Wire Line
	5400 3850 5500 3850
Wire Wire Line
	5400 3650 5500 3650
Wire Wire Line
	5400 3950 5950 3950
Wire Wire Line
	5950 3950 5950 3900
Wire Wire Line
	5400 3750 5450 3750
Wire Wire Line
	5450 3750 5450 4050
Connection ~ 5450 4050
Wire Wire Line
	5450 4050 5950 4050
$Comp
L Sensor:DHT11 U2
U 1 1 6293B917
P 5650 5550
F 0 "U2" H 5406 5596 50  0000 R CNN
F 1 "DHT22" H 5406 5505 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 5650 5150 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 5800 5800 50  0001 C CNN
	1    5650 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 6293F028
P 5650 2650
F 0 "BT1" H 5768 2746 50  0000 L CNN
F 1 "Battery_Cell" H 5768 2655 50  0000 L CNN
F 2 "" V 5650 2710 50  0001 C CNN
F 3 "~" V 5650 2710 50  0001 C CNN
	1    5650 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 62943181
P 5650 3050
F 0 "#PWR0112" H 5650 2800 50  0001 C CNN
F 1 "GND" H 5655 2877 50  0000 C CNN
F 2 "" H 5650 3050 50  0001 C CNN
F 3 "" H 5650 3050 50  0001 C CNN
	1    5650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2750 5650 3050
Wire Wire Line
	5650 2000 5650 2450
$Comp
L Device:R R1
U 1 1 6293C82F
P 6050 5350
F 0 "R1" H 6120 5396 50  0000 L CNN
F 1 "1k" H 6120 5305 50  0000 L CNN
F 2 "" V 5980 5350 50  0001 C CNN
F 3 "~" H 6050 5350 50  0001 C CNN
	1    6050 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 5550 6050 5550
Wire Wire Line
	6050 5550 6050 5500
Wire Wire Line
	6050 5200 6050 5150
Wire Wire Line
	6050 5150 5650 5150
Wire Wire Line
	5650 5150 5650 5250
$Comp
L power:+BATT #PWR0113
U 1 1 62953DD8
P 5650 2000
F 0 "#PWR0113" H 5650 1850 50  0001 C CNN
F 1 "+BATT" H 5665 2173 50  0000 C CNN
F 2 "" H 5650 2000 50  0001 C CNN
F 3 "" H 5650 2000 50  0001 C CNN
	1    5650 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0114
U 1 1 62955279
P 5650 5100
F 0 "#PWR0114" H 5650 4950 50  0001 C CNN
F 1 "+3.3V" H 5665 5273 50  0000 C CNN
F 2 "" H 5650 5100 50  0001 C CNN
F 3 "" H 5650 5100 50  0001 C CNN
	1    5650 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 629563FF
P 5650 5900
F 0 "#PWR0115" H 5650 5650 50  0001 C CNN
F 1 "GND" H 5655 5727 50  0000 C CNN
F 2 "" H 5650 5900 50  0001 C CNN
F 3 "" H 5650 5900 50  0001 C CNN
	1    5650 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5850 5650 5900
Wire Wire Line
	5650 5100 5650 5150
Connection ~ 5650 5150
Text GLabel 6150 5550 2    50   Input ~ 0
DHT_D
Wire Wire Line
	6050 5550 6150 5550
Connection ~ 6050 5550
Text GLabel 10050 4150 2    50   Input ~ 0
DHT_D
Wire Wire Line
	9950 4150 10050 4150
$Comp
L power:+5V #PWR?
U 1 1 6295E6F1
P 6600 5150
F 0 "#PWR?" H 6600 5000 50  0001 C CNN
F 1 "+5V" H 6615 5323 50  0000 C CNN
F 2 "" H 6600 5150 50  0001 C CNN
F 3 "" H 6600 5150 50  0001 C CNN
	1    6600 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 5150 6600 5250
Wire Wire Line
	6600 5250 6850 5250
Wire Wire Line
	5400 4150 5500 4150
$Comp
L Device:Crystal Y1
U 1 1 628EA181
P 9250 2650
F 0 "Y1" V 9100 2750 50  0000 R CNN
F 1 "32.788" V 9000 2750 50  0000 R CNN
F 2 "" H 9250 2650 50  0001 C CNN
F 3 "~" H 9250 2650 50  0001 C CNN
	1    9250 2650
	0    -1   -1   0   
$EndComp
$EndSCHEMATC