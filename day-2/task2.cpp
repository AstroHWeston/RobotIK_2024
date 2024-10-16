#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>

#define Servo_sl 9
#define Servo_sd 10
#define Servo_pl 11
#define Servo_pd 12

int kal[5] = {500, 800, 500, 500, 300};
const int linApin[] = {A0,A1,A2,A3,A4};   // input
const int linDpin[] = {41,43,45,47,49};   // output

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

void move_fw() { // Kretanje naprijed
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(180 - i);
    motor_sl.write(i);
    motor_sd.write(180 - i);
  }
}
void rotate_right() { // Rotacija desno 
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(90);
    motor_pl.write(180 - i);
    motor_sl.write(180 - i);
    motor_sd.write(90);
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
    if(analogRead(A2) < 500) {
        move_fw();
    }
    if(analogRead(A4) < 300) {
    rotate_right();
    }
    if(analogRead(A0) < 500) {
        motor_stop();
    }
}