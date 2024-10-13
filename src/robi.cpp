/*
  Ako ovo ne radi
  ja cu se propucat
  - max
*/
#include <NewPing.h>              // UZV senzor
#include <LiquidCrystal_I2C.h>    // LCD
#include <Wire.h>                 // I2C komunikacija
#include <WS2812-SOLDERED.h>      // LED traka
#include <APDS9960-SOLDERED.h>    // senzor boje
#include <Servo.h>                // servo motor

//HC-SR04 - ultrazvučni senzor
const int uzvF = 0;
const int uzvB = 1;
const int uzvL = 2;
const int uzvR = 3;
const int trigPin[] = {31, 33, 35, 37};  
const int echoPin[] = {30, 32, 34, 36};

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400  

// NewPing setup of pins and maximum distance.
NewPing sonarF(trigPin[uzvF], echoPin[uzvF], MAX_DISTANCE);
NewPing sonarB(trigPin[uzvB], echoPin[uzvB], MAX_DISTANCE);
NewPing sonarL(trigPin[uzvL], echoPin[uzvL], MAX_DISTANCE);
NewPing sonarR(trigPin[uzvR], echoPin[uzvR], MAX_DISTANCE);

// TCRT5000 senzor linije
int kal[5] = {200,300,200,200,200};
const int linApin[] = {A0,A1,A2,A3,A4};   // input
const int linDpin[] = {41,43,45,47,49};   // output

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

// inicijalizacija svega
LiquidCrystal_I2C lcd(0x27, 2, 16); // Define LCD object
APDS_9960 apds;
#define PIN       6     // pin na koji je spojena LED traka
#define NUMPIXELS 10
WS2812 pixels(NUMPIXELS, PIN);

#define GRANICA   15;     // duljina kod koje ragira na prepreku
int nprog = 0;            // brojilo programa
int start = 1;            // početak programa
// boje ********************
const int bR=1;
const int bG=2;
const int bB=3;
const int bY=4;
// deklaracija funkcija ****
void P1(void);
void P2(void);
void P3(void);
void P4(void);
void P5(void);
int prati_P1(void);
int prati_P2(void);
int prati_P3(void);
int prati_P4(void);
int boja(void);
void okret_180();
//**************************

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
void reset_display() {
  lcd.clear();
  lcd.setCursor(0, 0);
}
//***************************************************
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
  for (int i = 90; i >= maxN; i--) {
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
  reset_display();
  lcd.print("OKRET!");
  for (int i = 90; i <= maxP; i++) { //prije maxp je bilo 180
    motor_pd.write(i);
    motor_pl.write(i);
    motor_sl.write(i);
    motor_sd.write(i);
  }
  delay(3100);
  motor_stop();
}
//***************************************************
int pracenje() {
  int kasni = 20;
  int rez[5];
  int odstup;
  int n;
  
  for(int i=0;i<5;i++) {
    digitalWrite(linDpin[i], HIGH);
    delay(kasni);
    rez[i] = analogRead(linApin[i]);  
  }
  odstup = 0;
  n = 0;
  for(int i=0;i<5;i++) {
    if(rez[i] > kal[i]) {
      odstup += 2 * (i+1);
      n++;
    }
  }
/*  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(rez[0]);
  lcd.setCursor(5,0);
  lcd.print(rez[2]);
  lcd.setCursor(10,0);
  lcd.print(rez[4]);
  lcd.setCursor(2,1);
  lcd.print(rez[1]);
  lcd.setCursor(7,1);
  lcd.print(rez[3]); */
  if(n==0) odstup=0;                  // odstup==0 - nema linije, sve je bijelo
  else if(n==30) odstup=9;            // 9 - raskršće L i D
  else if(n==24) odstup=1;            // 1 - invertirano područje 
  else if (n>0) odstup = odstup/n;    // 4 - ras L, 5 - D, 6 - sredina, 7 - L, 8 - ras D 
  lcd.setCursor(12,1);
  lcd.print(odstup);
  return odstup;
}
//***************************************************
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  //TCRT5000 inicijalizacija
  for(int i=0;i<5;i++) {
      pinMode(linApin[i], INPUT);
      pinMode(linDpin[i], OUTPUT);
  }
  /*
  //APDS9960 inicijalizacija
  if(!apds.begin()){
    lcd.setCursor(0, 1);
    lcd.print("Senzor boje?");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("Senzor boje OK!");
  }
  //apds.enableColor(true);  //enable color sensing mode
   if (!apds.begin())  //Begin communication with sensor
    {
      lcd.setCursor(0,1);
      lcd.println("Greska APDS-9960."); //Print message if sensor is not available
      while(1); //Loop forever if there is problem with sensor
    }
  delay(1000);
  */
  // test LED trake
  pixels.begin();
//  lcd.setCursor(0, 1);
//  lcd.print("                ");
//  lcd.print("LED traka");
  pixels.clear();
//  lcd.setCursor(10, 1);
//  lcd.print("Crvena");
  crvena();
//  lcd.setCursor(10, 1);
//  lcd.print("Zelena");
  zelena();
//  lcd.setCursor(10, 1);
//  lcd.print("Plava ");
  plava();
  // spoji motore
  motor_sl.attach(Servo_sl);
  motor_sd.attach(Servo_sd);
  motor_pl.attach(Servo_pl);
  motor_pd.attach(Servo_pd);
  reset_display();
}


void loop() {
  // Initialize the distance variables.
  int distanceF = sonarF.ping_cm();
  int distanceB = sonarB.ping_cm();
  int distanceL = sonarL.ping_cm();
  int distanceR = sonarR.ping_cm();
  lcd.setCursor(10, 1);
  
  if (distanceR > minDist) { // If the distance to the right is greater than the minimum distance, turn right.
    lcd.print("R");
    newDir = Right;
  } else if (distanceF > minDist) { // If the distance in front is greater than the minimum distance, move forward.
    lcd.print("F");
    newDir = Forward;
  } else if (distanceL > minDist) { // If the distance to the left is greater than the minimum distance, turn left.
    lcd.print("L");
    newDir = Left;
  } else { // If the distance behind is greater than the minimum distance, move backward.
    lcd.print("B");
    newDir = Backward;
  }
  
  if (newDir == oldDir) { // If the direction is the same as the previous one, continue moving in that direction.
    currentDir = newDir;
    switch (currentDir) {
      case Right:
        move_right();
        break;
      case Forward:
        move_fw();
        break;
      case Left:
        move_left();
        break;
      case Backward:
        move_back();
        break;
    }
  } else { // If the direction is different, stop the motors, reset the display, and turn the robot in the new direction.
    oldDir = newDir;
    motor_stop();
    reset_display();
    delay(1500);
    switch (currentDir) { 
      case Right:
        move_right(1000);
        break;
      case Forward:
        move_fw(1000);
        break;
      case Left:
        move_left(1000);
        break;
      case Backward:
        move_back(1000);
        break;
    }
  }
  delay(100);
}

void P1() {
  int X;
  int bojica;
  
  X=prati_P1();
  bojica=boja();
  if(boja()>0) {
    if(bojica==bR) crvena();
    if(bojica==bG) zelena();
    if(bojica==bB) plava();
    if(bojica==bY) zuta();
    delay(1000);
    pixels.clear();
  }
  if(X==0) {
    motor_stop();
    delay(500);
    okret_180();
    reset_display();
    lcd.print("STAO SAM");
    for(;;);
    nprog=1;
  }
}

void P2() {
  int d;
  int bojica;

  d=pracenje();
  switch(d) {
    case 6:
      move_fw(0);       // idi ravno naprijed
      break;
    case 4:           // okreni lijevo 90
      break;
    default:
      move_fw(0);       // idi ravno naprijed
      break;
  }
  if(d==1) {
    motor_stop();
    bojica=boja();
    if(bojica==bG) motor_stop();
    else move_fw(0);
  }
}

int prati_P1() {
  int d;
  //**************************
  start=0;      // testiranje
  //***************************
  while(start==1) {             // izađi iz startnog polja
    move_fw(0);
    delay(2000);
    d=pracenje();
    if(d!=0 && d!=9) start=0;
  }
  if(start==0) {
    d=pracenje();
    switch(d) {
      case 0:
        motor_stop();
        break;
      case 6:
        move_fw(0);           // idi ravno naprijed
        break;
      case 5:                 // okreni malo lijevo
        rotate_left(200);
        break;
      case 7:                 // okreni malo desno
      rotate_right(200);
        break;
      default:
        move_fw(0);           // idi ravno naprijed
        break;
    }
  }
  return d;
}

int boja() {
  int r, g, b;
  int boja;
  
  return bG;

  while(!apds.colorAvailable()) {      //wait for color data to be ready
    delay(5);
  }
  apds.readColor(r, g, b);  //get the data
  // odredi boju
  boja=bR;
  return boja;
}

/*
void crossing_F() {
  if(sonarR.ping_cm()>granica) {
    move_right(0,0);
  } else {
      if(sonarF.ping_cm()>granica) {
      move_fw(0,0);
    }
  } else {
    if(sonarL.ping_cm()>granica) {
      move_left(0,0);
    }
  }
  else move_back();
}

void crossing_L() {
  if(sonarF.ping_cm()>granica) {
    move_fw();
  } else {
      if(sonarL.ping_cm()>granica) {
      move_left();
    }
  } else {
    if(sonarB.ping_cm()>granica) {
      move_back();
    }
  }
  else move_right();
}
*/