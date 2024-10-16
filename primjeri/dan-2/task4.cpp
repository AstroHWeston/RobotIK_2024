#include <Arduino.h>
#include <Servo.h>
 
#define Servo_FL 11
#define Servo_FR 12
#define Servo_BL 9
#define Servo_BR 10
 
#define Trig_Left 35
#define Echo_Left 34
#define Trig_Right 37
#define Echo_Right 36
 
Servo servoFL, servoFR, servoBL, servoBR;
 
void setup() {
  Serial.begin(9600);
  servoFL.attach(Servo_FL);
  servoFR.attach(Servo_FR);
  servoBL.attach(Servo_BL);
  servoBR.attach(Servo_BR);
  pinMode(Trig_Left, OUTPUT);
  pinMode(Echo_Left, INPUT);
  pinMode(Trig_Right, OUTPUT);
  pinMode(Echo_Right, INPUT);
}
 
void loop() {
  long leftDistance = measureDistance(Trig_Left, Echo_Left);
  long rightDistance = measureDistance(Trig_Right, Echo_Right);
 
  if (abs(leftDistance - rightDistance) > 5) {
    if (leftDistance < rightDistance) {
      moveRight();
    } else {
      moveLeft();
    }
  } else {
    stopMoving();
    Serial.println("Centered between walls.");
  }
 
  delay(100);
}
 
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}
 
void moveLeft() {
  int d=200;
  Serial.println("Moving Left");
  for (int i = 90; i >= 60; i--){
  servoFL.write(i);
  servoFR.write(i);
  servoBL.write(180 - i);
  servoBR.write(180 - i);
  }
  if(d > 0) {
    delay(d);
    stopMoving();
  }
}
 
void moveRight() {
  int d=200;
  Serial.println("Moving Right");
  for (int i = 90; i >=60; i--){
  servoFL.write(180 - i);
  servoFR.write(180 - i);
  servoBL.write(i);
  servoBR.write(i);
  }
  if(d > 0) {
    delay(d);
    stopMoving();
  }
}
 
void stopMoving() {
  Serial.println("Stopping");
  servoFL.write(90);
  servoFR.write(90);
  servoBL.write(90);
  servoBR.write(90);
}
