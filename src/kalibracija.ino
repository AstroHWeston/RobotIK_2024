#include "16x2-LCD-SOLDERED.h"    // displej

//TCRT5000 - senzor linije
int kal[5] = {400,400,400,400,400};
const int linApin[] = {A0,A1,A2,A3,A4};   // input
const int linDpin[] = {25,27,29,31,33};   // output

// varijable programa
int dist;

//inicijalizacija
LCD lcd; // Define LCD object

void setup() {
  //TCRT5000 inicijalizacija
  for(int i=0;i<5;i++) {
    pinMode(linApin[i], INPUT);  
    pinMode(linDpin[i], OUTPUT);  
  }
}

void loop() {
  int kasni = 50;
  int rez[5];
  int odstupanje;
  int n;
  
  for(int i=0;i<5;i++) {
    digitalWrite(linDpin[i], HIGH);
    delay(kasni);
    rez[i] = analogRead(linApin[i]);  
    digitalWrite(linDpin[i], LOW);
  }
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
  lcd.print("KL   L    S    ");
  for(int i=0;i<3;i++) {
    lcd.setCursor(i*6,1);
    lcd.print(rez[i]);
  }
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("D   KD    ");
  for(int i=3;i<5;i++) {
    lcd.setCursor((i-3)*6,1);
    lcd.print(rez[i]);
  }
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("odstup=");
  lcd.setCursor(0,8);
  lcd.print(odstupanje);
  delay(1000);  
}
