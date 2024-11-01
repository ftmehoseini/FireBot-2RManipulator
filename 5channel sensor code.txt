#include <Servo.h>
//#include "trajectory.h"
#include <iostream>
#include <algorithm>

Servo motor1;
Servo motor2;
#define L1 0.17  //**inverse kinematic
#define L2 0.17
#define pi 3.14159265359
float angle1;
float angle2;
float rad_angle1;
float rad_angle2;

#define LED 13
//#define pump
int scale = 50;

volatile int sensor1 = A1;  //**5channel sensor
volatile int sensor2 = A2;
//volatile int sensor3 = A3;
volatile int sensor4 = A4;
volatile int sensor5 = A5;
/*volatile int sensorD1 = 9;
volatile int sensorD2 = 10;*/
volatile int sensorD3 = 2;  //(Interrupt pin)
/*volatile int sensorD4 = 12;
volatile int sensorD5 = 13;*/
volatile float xx;
volatile float yy;
int fire1;
int fire2;
int fire4;
int fire5;

int fire_on = 21;  //**Calibration
//int fire_off = 0;
const int buttonPin1 = 8;
int buttonState1;
int lastButtonState1 = LOW;
int ledState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
volatile int num = 0;  // Run the calibration function only once

int enA = 9;  //**pump
int in1 = 8;
int in2 = 7;

//int teta1[] = {129,118,108,98,88,77,66,53,56,69,81,91,101,110,120,131,134,124,115,106,97,87,76,62,73,85,95,104,112,120,129,138,143,134,127,120,113,106,98,89,110,113,118,123,128,134,141,149,156,149,143,138,134,131,129,129,146,143,143,144,147,151,157,164};   // variable to store the servo1 position
//int teta2[] = {54,71,85,96,107,116,124,131,139,131,122,113,102,90,77,61,65,81,94,106,117,127,137,146,150,141,131,120,109,97,83,68,69,84,98,110,121,132,142,152,151,141,131,120,109,97,84,68,66,81,95,107,118,128,138,147,140,132,123,114,103,91,78,62};  // variable to store the servo1 position
int teta1[] = { 0 }; //teta A-D
int teta2[] = { 160 };
int i = 1;

float x[] = { 0.06, 0.18, 0.18, 0.06 }; // point A-D
float y[] = { 0.17, 0.17, 0.05, 0.05 };

/*Trajectory servoTrajectory1(60, 40);  //**smooth
Trajectory servoTrajectory2(60, 40);*/
#define UPDATE_FREQUENCY 100
#define UPDATE_TIME (1000 / UPDATE_FREQUENCY)
unsigned long updateTimer = 0;
int moveNumber = 0;

void firesys() {
  analogWrite(enA, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(LED, HIGH);
  Serial.println("detected!");
  digitalWrite(LED, HIGH);
  delay(1000);
}

/*void trajectory() {
  servoTrajectory1.setTargetPos(teta1[i], 1);
  servoTrajectory2.setTargetPos(180 - teta2[i], 1);
}*/

int Calibration() {
  int reading = digitalRead(buttonPin1);
  if (reading != lastButtonState1) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState1) {
      buttonState1 = reading;
      if (buttonState1 == HIGH) {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(LED, ledState);
  lastButtonState1 = reading;

  if (buttonState1 == HIGH) {
    fire_on = analogRead(sensorD3);
    Serial.print("fire_on = ");
    Serial.println(fire_on);
    delay(500);
  }
  num++;
}

void setup() {
  motor1.attach(5);
  motor2.attach(3);
  Serial.begin(9600);
  //pinMode(sensorD1, INPUT);  //**sensor
  //pinMode(sensorD2, INPUT);
  pinMode(sensorD3, INPUT);
  //pinMode(sensorD4, INPUT);
  //pinMode(sensorD5, INPUT);

  //pinMode(LED, OUTPUT);

  pinMode(enA, OUTPUT);  //**pump
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  pinMode(buttonPin1, INPUT);  //**Calibration
  digitalWrite(LED, ledState);

  attachInterrupt(digitalPinToInterrupt(2), firesys, RISING);

  /*servoTrajectory1.reset(teta1[1]);
  servoTrajectory2.reset(teta2[1]);*/
}
void loop() {
  if (num == 0) {  //calibration
    Calibration();
  }
  for (i = 1; i < 5; i++) {
    //inverse kinematic
    rad_angle2 = acos((sq(x[i]) + sq(y[i]) - sq(L1) - sq(L2)) / (2 * L1 * L2));
    rad_angle1 = atan(y[i] / x[i]) - atan((L2 * sin(rad_angle2)) / (L1 + L2 * cos(rad_angle2)));
    angle1 = (rad_angle1 * 180) / pi;
    angle2 = (rad_angle2 * 180) / pi;
    if (angle1 < 0) {
      angle1 += 180;
    }
    motor1.write(angle1);
    motor2.write(angle2);
    Serial.print("y = ");
    Serial.println(y[i]);
    Serial.print("x = ");
    Serial.println(x[i]);
    /*Serial.print("angle1 =  ");
   Serial.println(angle1);
   Serial.print("angle2 = ");
   Serial.println(angle2);*/
    Serial.println("________________ ");
    delay(250);
    
    fire1 = analogRead(sensor1);
    fire2 = analogRead(sensor2);
    fire4 = analogRead(sensor4);
    fire5 = analogRead(sensor5);
    realfire = max(fire1, fire2, fire4, fire5);
    switch (realfire) {
      case fire1: //go to point L
        xx = x[i] + 3;
        yy = y[i] - 3;
        break;
      case fire2: //go to point E
        xx = x[i] + 3;
        yy = y[i] + 3;
        break;
      case fire4: //go to point F
        xx = x[i] - 3;
        yy = y[i] + 3;
        break;
      case fire5: //go to point G
        xx = x[i] - 3;
        yy = y[i] - 3;
        break;
        rad_angle2 = acos((sq(xx) + sq(yy) - sq(L1) - sq(L2)) / (2 * L1 * L2));
        rad_angle1 = atan(yy / xx) - atan((L2 * sin(rad_angle2)) / (L1 + L2 * cos(rad_angle2)));
        angle1 = (rad_angle1 * 180) / pi;
        angle2 = (rad_angle2 * 180) / pi;
        if (angle1 < 0) {
          angle1 += 180;
        }
        motor1.write(angle1);
        motor2.write(angle2);        
    }
  }
}