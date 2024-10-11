#include "NewPing.h"

const int trigPin[] = {31, 26, 28, 30};  
const int echoPin[] = {30, 27, 29, 31};

#define MAX_DISTANCE 400  

NewPing sonarF(trigPin[0], echoPin[0], MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int distanceF = sonarF.ping_cm();
  Serial.print("Front: ");
  Serial.print(distanceF);
  delay(500);
}