#include "trajectory.h"
#include <Servo.h> 
Servo motor1;
Servo motor2;
//#define L1 0.17
//#define L2 0.17
#define pi 3.14159265359
#define LED 13
int scale = 50;
volatile int sensor = A2;
//volatile int sensorD = 2;
int fire;
//int fire_on = 21;  //**Calibration
//int fire_off = 0;
const int buttonPin1 = 8;
int buttonState1;
int lastButtonState1 = LOW;
int ledState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
volatile int num=0; // Run the calibration function only once
int enA = 9;  //**pump
int in1 = 8;
int in2 = 7;              
int teta1[] = {129,118,108,98,88,77,66,53,56,69,81,91,101,110,120,131,134,124,115,106,97,87,76,62,73,85,95,104,112,120,129,138,143,134,127,120,113,106,98,89,110,113,118,123,128,134,141,149,156,149,143,138,134,131,129,129,146,143,143,144,147,151,157,164};   // variable to store the servo1 position
int teta2[] = {54,71,85,96,107,116,124,131,139,131,122,113,102,90,77,61,65,81,94,106,117,127,137,146,150,141,131,120,109,97,83,68,69,84,98,110,121,132,142,152,151,141,131,120,109,97,84,68,66,81,95,107,118,128,138,147,140,132,123,114,103,91,78,62};  // variable to store the servo1 position
//int teta1[] = {40} ; 
//int teta2[] = {40} ;
int i = 1 ; 

Trajectory servoTrajectory1(4000, 8000);   //smooth
Trajectory servoTrajectory2(4000, 8000);
#define UPDATE_FREQUENCY 100
#define UPDATE_TIME (1000 / UPDATE_FREQUENCY)
unsigned long updateTimer = 0;
int ii = 0;

void firesys() {
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(LED, HIGH);
  Serial.println("detected!");
  digitalWrite(LED, HIGH); 
  
}

void setup() {
  motor1.attach(5);
  motor2.attach(3);
  Serial.begin(115200);
  pinMode(sensor, INPUT);  //**sensor
  //pinMode(LED, OUTPUT);

  pinMode(enA, OUTPUT);  //**pump
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  pinMode(buttonPin1, INPUT);  //**Calibration
  digitalWrite(LED, ledState);

  //attachInterrupt(digitalPinToInterrupt(2), firesys, RISING);
  
  servoTrajectory1.reset(teta1[1]);
  servoTrajectory2.reset(180-teta2[1]);
}

void nextMove() {
  servoTrajectory1.setTargetPos(teta1[ii]) ; 
  servoTrajectory2.setTargetPos(180-teta2[ii]) ; 
  ii++;
}

void loop() {

// Update the servo position at regular intervals
if (updateTimer <= millis()) {
if (updateTimer <= millis() - UPDATE_TIME) updateTimer = millis() + UPDATE_TIME;
else updateTimer += UPDATE_TIME;

  float currentAngle1 = servoTrajectory1.update();
  motor1.write((currentAngle1));

  float currentAngle2 = servoTrajectory2.update();
  motor2.write((currentAngle2));

    fire = analogRead(sensor);
    if (fire < 22) { 
    ///digitalWrite(sensorD, HIGH);
    Serial.println("detected!");
    firesys() ;
    delay(3000) ; 
    }

  if (servoTrajectory1.ready()&&servoTrajectory2.ready()&&ii<66) { 
    nextMove(); 
  }
  if(ii>64)
  {
  servoTrajectory1.reset(teta1[1]);
  servoTrajectory2.reset(180-teta2[1]);
  ii = 0 ; 
  }

}}