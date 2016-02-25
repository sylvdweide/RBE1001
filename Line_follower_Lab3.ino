#include <Servo.h>

const int left = 28;
const int right = 29;
Servo leftMotor;
Servo rightMotor;

void forward();
void turnLeft();
void turnRight();
void lineTrack();

void setup() {
  // put your setup code here, to run once:
pinMode(left, INPUT);
pinMode(right,INPUT);
leftMotor.attach(6);
rightMotor.attach(5);
}

void forward() {
    leftMotor.write(110); //motor turns cw and wheel ccw
    rightMotor.write(70); //motor turns ccw and wheel cw
}

void turnRight() {
  leftMotor.write(120);
  rightMotor.write(90);
}

void turnLeft() {
  leftMotor.write(90);
  rightMotor.write(60);
}

void stop() {
  leftMotor.write(90);
  rightMotor.write(90);
}

void lineTrack() {
  // setup robot with line between photoresistors
  while(digitalRead(left) == HIGH && digitalRead(right) == HIGH) {
    forward();
  }
  while(digitalRead(left) == LOW && digitalRead(right) == HIGH) {
    turnLeft();
  }
  while(digitalRead(left) == HIGH && digitalRead(right) == LOW) {
    turnRight();
  }
}

void loop() {
  lineTrack();
}

