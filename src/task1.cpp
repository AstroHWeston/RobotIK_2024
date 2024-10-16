#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>
#include <Adafruit_APDS9960.h>
#include <WS2812-SOLDERED.h>
#include <NewPing.h>

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

NewPing sonarF(31, 30, 400);

Adafruit_APDS9960 apds;

WS2812 pixels(4, 10);

// Definicija distanca
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

void motor_stop() {
  motor_pd.write(90);
  motor_pl.write(90);
  motor_sl.write(90);
  motor_sd.write(90);
}

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
// LED traka - boje
void crvena() {
  for (int i = 0; i < 10; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    pixels.show();
    delay(20);
  }
}
//***************************************************
void zelena() {
  for (int i = 0; i < 10; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(20);
  }  
}
//***************************************************
void zuta() {
  for (int i = 0; i < 10; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 150, 0));
    pixels.show();
    delay(20);
  }  
}
//***************************************************
void plava() {
    for (int i = 0; i < 10; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();
    delay(20);
  }
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
  /*int distanceF = sonarF.ping_cm();
  while (distanceF > 13) {
    move_fw();
    distanceF = sonarF.ping_cm();
  }

  motor_stop();*/

  while (!apds.colorDataReady()) {
    delay(20);
  }
  uint16_t r, g, b, c;

  apds.getColorData(&r, &g, &b, &c);

  //Serial.print("R: "); Serial.print(r); Serial.print(" G: "); Serial.print(g); Serial.print(" B: "); Serial.print(b); Serial.print(" C: "); Serial.println(c);

  if (r > g && r > b) {
    Serial.print("Color is red!");
    Serial.println();
    crvena();
  } else if (r > b && g > b && c > 25) {
    Serial.print("Color is yellow!");
    Serial.println();
    zuta();
  } else if (g > r && g > b) {
    Serial.print("Color is green!");
    Serial.println();
    zelena();
  } else if (b > r && b > g) {
    Serial.print("Color is blue!");
    Serial.println();
    plava();
  } else {
    Serial.print("Color is unknown!");
    Serial.println();
  }

  delay(1000);
  pixels.clear();
  delay(1000);
}