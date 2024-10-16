// Include NewPing Library
#include "NewPing.h"
#include <Servo.h>
#include <SPI.h>

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
//#define TRIGGER_PIN 9
//#define ECHO_PIN 10

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400  
int L;
int R;

// NewPing setup of pins and maximum distance.
NewPing sonarL(35, 34, MAX_DISTANCE);
NewPing sonarR(37, 36, MAX_DISTANCE);

#define Servo_sl 9
#define Servo_sd 10
#define Servo_pl 11
#define Servo_pd 12

Servo motor_sl;
Servo motor_sd;
Servo motor_pl;
Servo motor_pd;

void motor_stop() {
  motor_pd.write(90);
  motor_pl.write(90);
  motor_sl.write(90);
  motor_sd.write(90);
}
//***************************************************

void move_fw(int d = 0) { // Kretanje naprijed
  for (int i = 90; i >= 180; i--) {
    motor_pd.write(i);
    motor_pl.write(180 - i);
    motor_sl.write(180 - i);
    motor_sd.write(i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
void move_back(int d = 0) { // Kretanje natrag
  for (int i = 90; i >= 180; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(i);
    motor_sl.write(i);
    motor_sd.write(180 - i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
void move_right(int d = 0) { // Kretanje desno
  for (int i = 90; i >= 180; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(180 - i);
    motor_sl.write(i);
    motor_sd.write(i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
void move_left(int d = 0) { // Kretanje lijevo
  for (int i = 90; i >= 180; i--) {
    motor_pd.write(i);
    motor_pl.write(i);
    motor_sl.write(180 - i);
    motor_sd.write(180 - i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}

void setup() {
  Serial.begin(9600);
  motor_sl.attach(Servo_sl);
  motor_sd.attach(Servo_sd);
  motor_pl.attach(Servo_pl);
  motor_pd.attach(Servo_pd);
}

void loop() {
  L = sonarL.ping_cm();
  R = sonarR.ping_cm();
  if (L > R + 2) {
    move_left(1000);
  } else if (R > L) {
    move_right(1000);
  }
  Serial.print("L = ");
  Serial.print(sonarL.ping_cm());
  Serial.println(" cm");
  Serial.print("R = ");
  Serial.print(sonarR.ping_cm());
  Serial.println(" cm");
  delay(250);
}