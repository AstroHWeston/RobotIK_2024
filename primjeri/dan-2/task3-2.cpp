#include <NewPing.h>              // UZV senzor
#include <LiquidCrystal_I2C.h>    // LCD
#include <Wire.h>                 // I2C komunikacija
#include <WS2812-SOLDERED.h>      // LED traka
#include <Adafruit_APDS9960.h>    // senzor boje
#include <Servo.h>                // servo motor
#include <SPI.h>

// TCRT5000 senzor linije
int kal[5] = {40, 300, 50, 45, 45};
const int linApin[] = {A0, A1, A2, A3, A4};   // input
const int linDpin[] = {41, 43, 45, 47, 49};   // output

// servo motori
#define Servo_sl 9
#define Servo_sd 10
#define Servo_pl 11
#define Servo_pd 12
Servo motor_sl;
Servo motor_sd;
Servo motor_pl;
Servo motor_pd;
int maxP = 120;
int maxN = 180 - maxP;

// Inicijalizacija senzora boje
Adafruit_APDS9960 apds;

// Inicijalizacija LED trake
#define PIN 4
#define NUMPIXELS 10
WS2812 pixels(NUMPIXELS, PIN);
//***************************************************
// Definicija smjerova
int minDist = 20;
enum Direction {
  Forward,      // 0
  Backward,     // 1
  Left,         // 2
  Right,        // 3
  None          // 4
};
Direction oldDir = Forward;
Direction currentDir = Forward;
Direction newDir = None;
//***************************************************
// Motori - Kretanje u smjerovima
void motor_stop() {
  motor_pd.write(90);
  motor_pl.write(90);
  motor_sl.write(90);
  motor_sd.write(90);
}
//***************************************************
void move_fw(int d = 0) { // Kretanje naprijed
  currentDir = Forward;
  for (int i = 90; i >= maxN; i--) {
    motor_pd.write(i);
    motor_pl.write(180 - i);
    motor_sl.write(180 - i);
    motor_sd.write(i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
void move_back(int d = 0) { // Kretanje natrag
  currentDir = Backward;
  for (int i = 90; i >= maxN; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(i);
    motor_sl.write(i);
    motor_sd.write(180 - i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
void move_right(int d = 0) { // Kretanje desno
  currentDir = Right;
  for (int i = 90; i >= maxN; i--) {
    motor_pd.write(180 - i);
    motor_pl.write(180 - i);
    motor_sl.write(i);
    motor_sd.write(i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
void move_left(int d = 0) { // Kretanje lijevo
  currentDir = Left;
  for (int i = 90; i >= maxN; i--) {
    motor_pd.write(i);
    motor_pl.write(i);
    motor_sl.write(180 - i);
    motor_sd.write(180 - i);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
void rotate_right(int d = 0) { // Rotacija desno
  for (int i = 90; i >= maxN; i--) {
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
//***************************************************
void rotate_left(int d = 0) { // Rotacija lijevo
  for (int i = 90; i >= maxN; i--) {
    motor_pd.write(i);
    motor_pl.write(i);
    motor_sl.write(90);
    motor_sd.write(90);
  }
  if(d > 0) {
    delay(d);
    motor_stop();
  }
}
//***************************************************
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
//***************************************************
void okret_180() {
  for (int i = 90; i <= 180; i++) { //prije maxp je bilo 180
    motor_pd.write(i);
    motor_pl.write(i);
    motor_sl.write(i);
    motor_sd.write(i);
  }
  delay(3300);
  motor_stop();
}
//***************************************************
// LED traka - boje
void crvena() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    pixels.show();
    delay(20);
  }
}
//***************************************************
void zelena() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(20);
  }  
}
//***************************************************
void zuta() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 150, 0));
    pixels.show();
    delay(20);
  }  
}
//***************************************************
void plava() {
    for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();
    delay(20);
  }
}
//***************************************************
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
//***************************************************
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
    switch(d) {
      case 0:
        motor_stop();
        break;
      case 6:                 // idi ravno naprijed
        move_fw();           
        break;
      case 5:                 // okreni malo lijevo
        rotate_left(200);
        break;
      case 7:                 // okreni malo desno
        rotate_right(200);
        break;
      default:                // idi ravno naprijed
        move_back();
        break;
    }
  }
  return d;
}
//***************************************************
void setup() {
  Serial.begin(9600);

  if (!apds.begin()) {
    Serial.print("Error initializing color sensor.");
  }
  
  apds.enableColor(true);

  pixels.begin();
  delay(1000);
  pixels.clear();
  motor_sl.attach(Servo_sl);
  motor_sd.attach(Servo_sd);
  motor_pl.attach(Servo_pl);
  motor_pd.attach(Servo_pd);
  delay(1000);
}

void loop() {
  while (!apds.colorDataReady()) {
    delay(20);
  }
  uint16_t r, g, b, c;

  apds.getColorData(&r, &g, &b, &c);
  
  if (r > b && g > b && c > 25) {
    Serial.print("Color is yellow!");
    Serial.println();
    zuta();
  } else if (r > g && r > b) {
    Serial.print("Color is red!");
    Serial.println();
    crvena();
  } else if (g > r && g > b) {
    Serial.print("Color is green!");
    Serial.println();
    zelena();
  } else if (b > r && b > g) {
    Serial.print("Color is blue!");
    Serial.println();
    plava();
  } else {
    move_back();
    delay(2000);
  }
  okret_180();
  

}