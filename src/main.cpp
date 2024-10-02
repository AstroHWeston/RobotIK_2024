#include <Arduino.h>
#include "NewPing.h"
#include <Wire.h>

#define TRIGGER_PIN 31
#define ECHO_PIN 30
#define MAX_DISTANCE 400 // Centimeters.

NewPing sonar0(31, 30, MAX_DISTANCE);
NewPing sonar1(33, 32, MAX_DISTANCE);
NewPing sonar2(35, 34, MAX_DISTANCE);
NewPing sonar3(37, 36, MAX_DISTANCE);


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Distance = ");
  Serial.print(sonar0.ping_cm());
  Serial.print(" - ");
  Serial.print(sonar1.ping_cm());
  Serial.print(" - ");
  Serial.print(sonar2.ping_cm());
  Serial.print(" - ");
  Serial.print(sonar3.ping_cm());
  Serial.println(" cm");
  delay(500);
}