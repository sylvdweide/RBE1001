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

void setup() {
  // put your setup code here, to run once:
pinMode(left, INPUT);
pinMode(right,INPUT);
leftMotor.attach(6);
rightMotor.attach(5);
pinMode(pot,INPUT);
armMotor.attach(11);
Serial.begin(9600);

raiseArm();
}

void forward() {
    leftMotor.write(115); //motor turns cw and wheel ccw
    rightMotor.write(75); //motor turns ccw and wheel cw
}

void turnRight() {
  leftMotor.write(115);
  rightMotor.write(90);
}

void turnLeft() {
  leftMotor.write(90);
  rightMotor.write(75);
}

void stopBot() {
  leftMotor.write(90);
  rightMotor.write(90);
}



// pot- initial (lower) posn = 305
// higher posn=379
void raiseArm() {
  int potread=analogRead(pot);
  while(potread<=550) {
    armMotor.write(120);
    potread=analogRead(pot);
    Serial.println(potread);
  }
   armMotor.write(90);
}

void lowerArm() {
  int potread=analogRead(pot);
  stopBot();
  while (potread>=305 && digitalRead(left)==LOW && digitalRead(right)==LOW) 
  {
    armMotor.write(70);
    potread=analogRead(pot);
    Serial.println(potread);
  }
  armMotor.write(90);
}

void lineTrack() {
  // setup robot with line between photoresistors
  while(digitalRead(left) == HIGH && digitalRead(right) == HIGH) {
    forward();
    raiseArm();
  }
  while(digitalRead(left) == LOW && digitalRead(right) == HIGH) {
    turnLeft();
    raiseArm();
  }
  while(digitalRead(left) == HIGH && digitalRead(right) == LOW) {
    turnRight();
    raiseArm();
  }
 /* while (digitalRead(left) == LOW && digitalRead(right) == LOW) {
    stopBot();
  }*/
} // figure out why line messes it up...?

void loop() {
  while(digitalRead(left) == HIGH || digitalRead(right) == HIGH)
  {
    lineTrack();
  }
  lowerArm();
  forward();
  delay(50);
  turnRight();
  delay(12);
  while(digitalRead(left) == HIGH || digitalRead(right) == HIGH)
  {
    lineTrack();
  }
  stopBot();
}

