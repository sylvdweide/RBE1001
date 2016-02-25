#include <Servo.h>

const int left = 28; //left photoresistor (when looking from beking robot)
const int right = 29; //right photoresistor
Servo leftMotor;
Servo rightMotor;
const int pot = A0;
Servo armMotor;

void forward();
void turnLeft();
void turnRight();
void lineTrack();

const int potHigh = 450;
const int potLow = 315;

void setup() {
  // put your setup code here, to run once:
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  leftMotor.attach(6);
  rightMotor.attach(5);
  pinMode(pot, INPUT);
  armMotor.attach(11);

  //moveArm(potHigh);
  //delay(100);

  Serial.begin(9600);
}

void forward() {
  leftMotor.write(120); //motor turns cw and wheel ccw
  rightMotor.write(70); //motor turns ccw and wheel cw
}

void forwardSlow() {
  leftMotor.write(115); //motor turns cw and wheel ccw
  rightMotor.write(75); //motor turns ccw and wheel cw
}

void turnRight() {
  leftMotor.write(125);
  rightMotor.write(85);
  delay(50);
}

void turnLeft() {
  leftMotor.write(90);
  rightMotor.write(65);
  delay(50);
}

void turnLeftSlow() {
  leftMotor.write(90);
  rightMotor.write(75);
  delay(50);
}

void stopBot() {
  leftMotor.write(90);
  rightMotor.write(90);
}

int counter = 0;

void lineTrack() {
  if (digitalRead(left) == HIGH && digitalRead(right) == HIGH) {
    forward();
    moveArm(potHigh);
  }
  else if (digitalRead(left) == LOW && digitalRead(right) == HIGH) {
    turnLeft();
    moveArm(potHigh);
  }
  else if (digitalRead(left) == HIGH && digitalRead(right) == LOW) {
    turnRight();
    moveArm(potHigh);
  }
}

void lineTrackSlow() {
  if (digitalRead(left) == HIGH && digitalRead(right) == HIGH) {
    forwardSlow();
  }
  else if (digitalRead(left) == LOW && digitalRead(right) == HIGH) {
    turnLeftSlow();
  }
  else if (digitalRead(left) == HIGH && digitalRead(right) == LOW) {
    turnRight();
  }
}

void runCourse() {
  int runTime = millis();
  if (digitalRead(left) == LOW && digitalRead(right) == LOW) {
    stopBot();
    if (analogRead(pot) >= potLow) {
      moveArm(potLow);
    }
    else if (analogRead(pot) < (potLow+10) && counter == 0)
    {
      turnRight();
      delay(200);
      forward();
      delay(100);
      counter = 1;
    }
  }
  else if (runTime > 16000 || (runTime>9000 && counter==0)) {
    lineTrackSlow();
  }
  else {
    lineTrack();
  }
}

void moveArm(int posn) {
  int potread = analogRead(pot);
  int difference = posn - potread;
  double gain = .25;
  armMotor.write(90 + (difference * gain));
  potread = analogRead(pot);
  difference = posn - potread;
  //Serial.println(potread);
}



void loop() {
  Serial.println(analogRead(pot));
  //runCourse();
}
