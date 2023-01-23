#define TRIG_PIN 32 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define TRIG_PIN2 15
#define ECHO_PIN 33 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#define ECHO_PIN2 2
#define SOUND_SPEED 0.017
#define LED_PIN 25
#define LED_PIN2 27
//#define SDA 21 // Sending and recieving data for LCD display (Send Data with Acknowledge)
//#define SCL 22 // Used for the Clock signal (Serial Clock Line)
#define DIS_THRES 125.00 
#define DIS_THRES2 125.00 // centimeters
//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
int numPeople = 0;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <iostream>
#include <string>

float duration_us, distance_cm;
float duration_us2, distance_cm2;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 2);

void setup() {
  // begin serial port
  Serial.begin (115200);

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  pinMode(ECHO_PIN2, INPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);

  /*f(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x32
    Serial.println("SSD1306 alloction failed");
    for(;;); // Don't proceed, loop forever
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
}

void loop() {

  char first[] = "";  
  
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(1);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = SOUND_SPEED * duration_us;
  
  // generate 10-microsecond pulse to TRIG pin 2
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(1);
  digitalWrite(TRIG_PIN2, LOW);

  // measure duration of pulse from ECHO pin 2
  duration_us2 = pulseIn(ECHO_PIN2, HIGH);

  // calculate the second distance
  distance_cm2 = SOUND_SPEED * duration_us2;

  
  if (distance_cm < DIS_THRES){
    digitalWrite(LED_PIN, LOW); //turn on LED 1*Illogical statement*      
  }
  else {
    digitalWrite(LED_PIN, HIGH);
  }
  //if else {
    
 // }
  if (distance_cm2 < DIS_THRES2) {
    digitalWrite(LED_PIN2, LOW);  //trun on LED 2
  }
  else {
    digitalWrite(LED_PIN2, HIGH);
  }  
  

  // print the value to Serial Monitor
  Serial.print("distance1: ");
  Serial.print(distance_cm);
  Serial.print(" cm  ");
  Serial.println(DIS_THRES);
  // print the value to Serial Monitor
  Serial.print("distance2: ");
  Serial.print(distance_cm2);
  Serial.print(" cm  ");
  Serial.println(DIS_THRES2);
  Serial.println("-----------------------");
  delay(50);
}
