#define TRIG_PIN 23 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 22 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#define SOUND_SPEED 0.017
#define LED_PIN 25
#define DIS_THRES 75.00 // centimeters
float duration_us, distance_cm;

void setup() {
  // begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(1000000);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = SOUND_SPEED * duration_us;



  if (distance_cm < DIS_THRES){
    digitalWrite(LED_PIN, LOW); //turn on LED *Illogical statement*
  }
  else {
    digitalWrite(LED_PIN, HIGH);
  }



  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.print(" cm  ");
  Serial.println(DIS_THRES);

  delay(500);
}
