#define TRIG_PIN 32  // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define TRIG_PIN2 15
#define ECHO_PIN 33
// ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#define ECHO_PIN2 2
#define SOUND_SPEED 0.017
#define LED_PIN 25
#define LED_PIN2 27
//#define SDA 21          // Sending and recieving data for LCD display (Send Data with
// Acknowledge)
//#define SCL 22  // Used for the Clock signal (Serial Clock Line)
#define DIS_THRES 25
#define DIS_THRES2 125.00  // centimeters
/*#define SCREEN_WIDTH 128   // OLED display width, in pixels
#define SCREEN_HEIGHT 64   // OLED display height, in pixels*/
int numPeople = 0;

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include <iostream>
#include <string>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 2);

enum Direction {
  EnterRoom,
  ExitRoom,
  Neither,
};

class Sensor {
public:
  Sensor(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    this->hasTriggered = false;
    this->lastTriggered = 0;
  }

  bool sensorHasTriggered() {
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(this->triggerPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(this->triggerPin, LOW);

    // measure duration of pulse from ECHO pin
    float duration_us = pulseIn(this->echoPin, HIGH);

    // calculate the distance
    float distance_cm = SOUND_SPEED * duration_us;

    bool trigger = distance_cm < DIS_THRES;

    // print the value to Serial Monitor
    if (trigger) {
      Serial.print(this->triggerPin);
      Serial.print(" has triggered: ");
      Serial.print(distance_cm);
      Serial.print(" cm < ");
      Serial.println(DIS_THRES);
    }
    return trigger;
  }

  void detect() {
    if (this->sensorHasTriggered()) {
      lastTriggered = millis();
      hasTriggered = true;
    }
  }

  Direction compare(Sensor& other) {
    if (this->hasTriggered && other.hasTriggered) {
      this->hasTriggered = false;  // do not detect next time
      other.hasTriggered = false;

      if (this->lastTriggered > other.lastTriggered) {
        return Direction::EnterRoom;
      } else {
        return Direction::ExitRoom;
      }
    } else {
      return Direction::Neither;
    }
  }

  bool hasTriggered;
  unsigned long lastTriggered;
  int triggerPin;
  int echoPin;
};

void setup() {
  // begin serial port
  Serial.begin(9600);

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  pinMode(ECHO_PIN2, INPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);

  /*if (!display.begin(SSD1306_SWITCHCAPVCC,
                       0x3C)) {  // Address 0x3D for 128x32
        Serial.println("SSD1306 alloction failed");
        for (;;)
            ;  // Don't proceed, loop forever
    }
    delay(2000);
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    // display static text

    display.println("Number of People: \n");
    display.println(numPeople);
    display.display();*/

  Sensor sensor1(LED_PIN, ECHO_PIN);
  Sensor sensor2(LED_PIN2, ECHO_PIN2);

  while (true) {  // loop
    sensor1.detect();
    sensor2.detect();
    // Serial.println("Number of People: \n");
    // Serial.println(numPeople);

    switch (sensor1.compare(sensor2)) {
EnterRoom:
      Serial.println("EnterRoom");
      numPeople++;
      break;
ExitRoom:
      Serial.println("ExitRoom");
      numPeople--;
      break;
Neither:
      // Serial.println("Neither");
      break;
    }
  }
}

void loop() {}
