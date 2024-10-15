#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//inicijalizacija
LiquidCrystal_I2C lcd(0x27, 2, 16); // Define LCD object

int kal[5] = {40, 300, 45, 45, 40};
const int linApin[] = {A0,A1,A2,A3,A4};   // input
const int linDpin[] = {41,43,45,47,49};   // output

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
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
      rez[i] = analogRead(linApin[i]) > kal[i] ? 1 : 0;
      digitalWrite(linDpin[i], LOW);
      Serial.print(analogRead(linApin[i]));
      Serial.print(" - ");
  }

  Serial.println();
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