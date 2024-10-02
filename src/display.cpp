#include <LiquidCrystal_I2C.h>    // displej
#include <Wire.h>

//inicijalizacija
LiquidCrystal_I2C lcd(0x27, 2, 16); // Define LCD object

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("0123");
  lcd.setCursor(6, 0);
  lcd.print("1234");
  lcd.setCursor(12, 0);
  lcd.print("2345");
  lcd.setCursor(3, 1);
  lcd.print("3456");
  lcd.setCursor(9, 1);
  lcd.print("4567");
}

void loop() {
  
}