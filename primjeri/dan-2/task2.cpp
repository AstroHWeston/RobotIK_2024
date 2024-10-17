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

void move_fw(int d = 0) { // Kretanje naprijed
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(i);
    motor_pl.write(180 - i);
    motor_sl.write(180 - i);
    motor_sd.write(i);
  }
  if (d > 0) {
    delay(d);
    motor_stop();
  }
}

void rotate_right(int d = 0) { // Rotacija desno
  for (int i = 90; i >= 60; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(180 - i);
    motor_sl.write(90);
    motor_sd.write(90);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}

void okret_90() {
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(180 - i);
    motor_sl.write(180 - i);
    motor_sd.write(180 - i);
  }
  delay(1550);
  motor_stop();
}

void okret_45() {
  for (int i = 90; i >= 0; i--) {
    motor_pd.write(90);
    motor_pl.write(90);
    motor_sl.write(180 - i);
    motor_sd.write(180 - i);
  }
  delay(2000);
  motor_stop();
}

int pracenje() {
  int kasni = 200;
  int rez[5];
  int odstup = 0;
  int n = 0;
  
  for(int i = 0; i < 5; i++) {
    digitalWrite(linDpin[i], HIGH);
  }
  delay(kasni);

  for(int i = 0; i < 5; i++) {
    //rez[i] = analogRead(linApin[i]);
    rez[i] = analogRead(linApin[i]) > kal[i] ? 1 : 0;
    digitalWrite(linDpin[i], LOW);
  }
/*
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(rez[0]);
  lcd.setCursor(6,0);
  lcd.print(rez[2]);
  lcd.setCursor(12,0);
  lcd.print(rez[4]);
  lcd.setCursor(3,1);
  lcd.print(rez[1]);
  lcd.setCursor(9,1);
  lcd.print(rez[3]);
  delay(100);*/

  for(int i = 0; i < 5; i++) {
    if(rez[i] != 0) {
      odstup += 2 * (i+1);
      n++;
    }
  }

  if(n == 0) odstup = 0;                        // odstup == 0 - nema linije, sve je bijelo
  else if(odstup == 30) odstup = 9;             // 9 - raskršće L i D
  else if(odstup == 24) odstup = 1;             // 1 - invertirano područje 
  else if (n > 0) odstup = odstup / n;          // 4 - ras L, 5 - D, 6 - sredina, 7 - L, 8 - ras D 
  return odstup;
}

int prati_P1() {
  int d;
  //**************************
  int start = 0;      // testiranje
  //***************************
  while (start == 1) {             // izađi iz startnog polja
    move_fw(1000);
    d = pracenje();
    if(d != 0 && d != 9) start = 0;
  }

  if (start == 0) {
    d = pracenje();
    //reset_display();
    //lcd.print(d);
    switch(d) {
      case 0:
        okret_45();
        break;
      case 6:                 // idi ravno naprijed
        move_fw();           
        break;
      case 5:                 // okreni malo lijevo
        okret_45();
        break;
      case 7:                 // okreni malo desno
        rotate_right(200);
        break;
      case 9:
        motor_stop();
        okret_45();
        delay(1500);
        motor_stop();
        delay(10000);
      default:                // idi ravno naprijed
        break;
    }
  }
  return d;
}

void setup() {
  Serial.begin(9600);
  motor_sl.attach(Servo_sl);
  motor_sd.attach(Servo_sd);
  motor_pl.attach(Servo_pl);
  motor_pd.attach(Servo_pd);
}

void loop() {
  int res = prati_P1();
  switch (res) {
    case 0:
      motor_stop();
      break;
    case 6:
      move_fw();
      break;
    case 5:
      okret_45();
      break;
    case 7:
      rotate_right(200);
      break;
    default:
      break;
  }
}