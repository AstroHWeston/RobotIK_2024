#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define Servo_sl 9
#define Servo_sd 10
#define Servo_pl 11
#define Servo_pd 12

Servo motor_sl;
Servo motor_sd;
Servo motor_pl;
Servo motor_pd;

char smjer;

LiquidCrystal_I2C lcd(0x27, 2, 16);

void reset_display() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

void motor_stop() {
  motor_pd.write(90);
  motor_pl.write(90);
  motor_sl.write(90);
  motor_sd.write(90);
}

void move_fw() { // Kretanje naprijed
  reset_display();
  lcd.print("Forward.");
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(180 - i);
    motor_sl.write(180 - i);
    motor_sd.write(i);
  }
}

void move_back() { // Kretanje natrag
  reset_display();
  lcd.print("Back.");
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(i);
    motor_sl.write(i);
    motor_sd.write(180 - i);
  }
}

void move_right() { // Kretanje desno
  reset_display();
  lcd.print("Right.");
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(180 - i);
    motor_sl.write(i);
    motor_sd.write(i);
  }
}

void move_left() { // Kretanje lijevo
  reset_display();
  lcd.print("Left.");
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(i);
    motor_sl.write(180 - i);
    motor_sd.write(180 - i);
  }
}

void rotate_right() { // Rotacija desno
  reset_display();
  lcd.print("Rot R.");
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(180 - i);
    motor_sl.write(90);
    motor_sd.write(90);
  }
}

void rotate_left() { // Rotacija lijevo
  reset_display();
  lcd.print("Rot L.");
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(i);
    motor_sl.write(90);
    motor_sd.write(90);
  }
}

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  lcd.init();
  lcd.backlight();
  reset_display();
  motor_sl.attach(Servo_sl);
  motor_sd.attach(Servo_sd);
  motor_pl.attach(Servo_pl);
  motor_pd.attach(Servo_pd);
  lcd.print("Setup done.");
}

void loop() {
  if(Serial3.available() > 0) {
    smjer = Serial3.read();
    switch (smjer) {
      case 'F':
        move_fw();
      case 'B':
        move_back();
      case 'R':
      move_right();
      case 'L':
        move_left();
      case 'S':
      motor_stop();
    }
  }
}

/*
void loop() {
  move_fw();
  delay(3000);
  motor_stop();
  delay(1500);
  move_back();
  delay(3000);
  motor_stop();
  delay(1500);
  move_left();
  delay(3000);
  motor_stop();
  delay(1500);
  move_right();
  delay(3000);
  motor_stop();
  delay(1500);
  rotate_right();
  delay(3000);
  motor_stop();
  delay(1500);
  rotate_left();
  delay(3000);
  motor_stop();
  delay(5000);
}*/