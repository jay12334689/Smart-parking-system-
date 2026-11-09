#include <Wire.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Exact Single-Pin Definitions Matching Circuit Schematic
#define IR_PIN      A3   // Entrance IR Sensor (Analog Input)
#define SERVO_PIN   6    // Boom Barrier Servo (D6 SERVO Header)
#define TRIG_PIN    3    // Ultrasonic Trigger (Digital Pin D3)
#define ECHO_PIN    2    // Ultrasonic Echo    (Digital Pin D2)
#define GREEN_LED   7    // Slot Empty LED     (Digital Pin D7)
#define RED_LED     8    // Slot Full LED      (Digital Pin D8)
// I2C OLED uses hardware A4 (SDA) and A5 (SCL)

Servo gateServo;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

long readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 999; 
  return duration * 0.034 / 2;
}

void showOLED(const char* text) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(text);
  display.display();
}

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(0);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  // 1. Entrance Gate Control (IR on A3 -> Servo on D6)
  if (analogRead(IR_PIN) < 255) {
    gateServo.write(90);
    showOLED("WELCOME");
    delay(3000);
  } else {
    gateServo.write(0);
  }

  // 2. Parking Bay Occupancy (Ultrasonic D3/D2 -> LEDs on D8/D7)
  long distance = readDistanceCm();
  if (distance < 10) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    showOLED("parking slot is full");
  } else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    showOLED("parking slot is empty");
  }
}
