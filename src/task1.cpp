#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>
#include <Adafruit_APDS9960.h>
#include <NewPing.h>

#define Servo_sl 9
#define Servo_sd 10
#define Servo_pl 11
#define Servo_pd 12

Servo motor_sl;
Servo motor_sd;
Servo motor_pl;
Servo motor_pd;

int maxP = 120;
int maxN = 180 - maxP;

NewPing sonarF(31, 30, 400);

// Definicija distanca
int minDist = 20;
enum Direction {
  Forward,      // 0
  Backward,     // 1
  Left,         // 2
  Right,        // 3
  None          // 4
};
Direction oldDir = Forward;
Direction currentDir = Forward;
Direction newDir = None;
//***************************************************

void motor_stop() {
  motor_pd.write(90);
  motor_pl.write(90);
  motor_sl.write(90);
  motor_sd.write(90);
}

void move_fw(int d = 0) { // Kretanje naprijed
  currentDir = Forward;
  for (int i = 90; i >= maxN; i--) {
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

void setup() {
  Serial.begin(9600);
  motor_sl.attach(Servo_sl);
  motor_sd.attach(Servo_sd);
  motor_pl.attach(Servo_pl);
  motor_pd.attach(Servo_pd);
  delay(1000);
}

void loop() {
  int distanceF = sonarF.ping_cm();
  while (distanceF > 13) {
    move_fw();
    distanceF = sonarF.ping_cm();
  }
  motor_stop();

}