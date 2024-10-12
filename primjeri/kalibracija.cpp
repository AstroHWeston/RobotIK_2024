#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//inicijalizacija
LiquidCrystal_I2C lcd(0x27, 2, 16); // Define LCD object

int kal[5] = {400,400,400,400,400};
const int linApin[] = {A0,A1,A2,A3,A4};   // input
const int linDpin[] = {41,43,45,47,49};   // output

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(115200);
    //TCRT5000 inicijalizacija
  for(int i=0;i<5;i++) {
      pinMode(linApin[i], INPUT);
      pinMode(linDpin[i], OUTPUT);
  }

}

void loop() {
  int kasni = 250;
  int rez[5];
  int odstupanje;
  int n;

  for(int i=0;i<5;i++) {
      digitalWrite(linDpin[i], HIGH);
      delay(kasni);
      rez[i] = analogRead(linApin[i]);
      digitalWrite(linDpin[i], LOW);
  }
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
  delay(100);
 }