#include <Arduino.h>
#include <LiquidCrystal_I2C.h>    // displej
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
  for (int i=0; i<5;i++) {
      Serial.print(rez[i]);
      Serial.print(" - ");
  }
  Serial.println("...");
  odstupanje = 0;
  n = 0;
  for(int i=0;i<5;i++) {
      if(rez[i] > kal[i]) {
        odstupanje += 2 * i;
        n++;
      }
  }
  if (n > 0) odstupanje = odstupanje / n;
  // prikaz rezultata na displeju
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("KL   L    S    ");
  for(int i=0;i<3;i++) {
      lcd.setCursor(i*6,1);
      lcd.print(rez[i]);
  }
  delay(10000);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("D   KD         ");
  for(int i=3;i<5;i++) {
    lcd.setCursor((i-3)*6,1);
    lcd.print(rez[i]);
  }
  delay(10000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("odstup=");
  lcd.setCursor(0,8);
  lcd.print(odstupanje);
  delay(10000);
}