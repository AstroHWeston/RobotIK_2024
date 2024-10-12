#include "NewPing.h"
#include <LiquidCrystal_I2C.h>

#define MAX_DISTANCE 400  
const int uzvF = 0;
const int uzvB = 1;
const int uzvL = 2;
const int uzvR = 3;
const int trigPin[] = {31, 33, 35, 37};  
const int echoPin[] = {30, 32, 34, 36};

NewPing sonarF(trigPin[uzvF], echoPin[uzvF], MAX_DISTANCE);
NewPing sonarB(trigPin[uzvB], echoPin[uzvB], MAX_DISTANCE);
NewPing sonarL(trigPin[uzvL], echoPin[uzvL], MAX_DISTANCE);
NewPing sonarR(trigPin[uzvR], echoPin[uzvR], MAX_DISTANCE);

LiquidCrystal_I2C lcd(0x27, 2, 16);

void reset_display() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  reset_display();
  int distanceF = sonarF.ping_cm();
  int distanceB = sonarB.ping_cm();
  int distanceL = sonarL.ping_cm();
  int distanceR = sonarR.ping_cm();

  lcd.setCursor(0, 0);
  lcd.print(distanceL);
  lcd.setCursor(5, 0);
  lcd.print(distanceF);
  lcd.setCursor(10, 0);
  lcd.print(distanceR);
  lcd.setCursor(5, 1);
  lcd.print(distanceB);
  delay(500);
}