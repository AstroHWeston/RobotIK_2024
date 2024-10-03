#include <Arduino.h>
#include <Servo.h>

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

void move_fw() { // Kretanje naprijed
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(180 - i);
    motor_sl.write(i);
    motor_sd.write(180 - i);
  }
}

void move_back() { // Kretanje natrag
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(i);
    motor_sl.write(180 - i);
    motor_sd.write(i);
  }
}

void move_right() { // Kretanje desno
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(180 - i);
    motor_sl.write(180 - i);
    motor_sd.write(i);
  }
}

void move_left() { // Kretanje lijevo
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(i);
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

void rotate_left() { // Rotacija lijevo 
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(90);
    motor_sl.write(90);
    motor_sd.write(i);
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
  return;
  move_fw();
  delay(3000);
  move_back();
  delay(3000);
  move_left();
  delay(3000);
  move_right();
  delay(3000);
  rotate_right();
  delay(3000);
  rotate_left();
  delay(3000);
}