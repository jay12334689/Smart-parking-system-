# Smart-parking-system-
# Automated Smart Parking System (Arduino Nano)

A working prototype of an automated parking system built on an ATmega328P-based Arduino Nano controller (STEMROBO Tinker Orbits). It controls an entry barrier and detects whether the parking slot is free or occupied.

## Features
- Automatic boom barrier using an IR proximity sensor and a PWM-driven SG90 servo
- Real-time slot occupancy detection using an ultrasonic sensor (occupied below 10 cm)
- Red LED for slot full, green LED for slot empty
- Status messages on a 0.96 inch I2C OLED display
- Powered and programmed from a smartphone through USB-OTG

## Hardware
- Arduino Nano (ATmega328P), STEMROBO Tinker Orbits
- IR sensor module
- Ultrasonic sensor
- SG90 servo motor
- Red and green LED modules
- 0.96 inch I2C OLED display
- USB-OTG cable and smartphone

## Pin connections

| Module | Pin on Arduino Nano |
|---|---|
| Red LED module | D6 |
| Green LED module | D7 |
| SG90 servo (PWM) | D9 |
| Ultrasonic sensor | TRIG = D3, ECHO = D2 |
| IR sensor module | A3 (analog input) |
| I2C OLED display | SDA = A4, SCL = A5 |

All modules use 5V and GND.





## How it works
1. The IR sensor detects a vehicle at the entrance, and the servo lifts the barrier (0° to 90°).
2. The ultrasonic sensor measures the distance in the parking slot.
3. If the distance is below 10 cm, the slot is occupied: the red LED turns on and the OLED shows the status.
4. Otherwise the slot is empty: the green LED turns on and the OLED shows the status.

## Code
`smart_parking.ino` is the Arduino sketch. Open it in the Arduino IDE, select Arduino Nano (ATmega328P), and upload.

Libraries used: Servo, plus the OLED library used in the sketch.

## Result
Tested live in the lab. Fixed pin-mapping conflicts during testing and scored 10/10 in the evaluation.

## Author
Jayesh Thokal, First-Year Electrical Engineering Student
