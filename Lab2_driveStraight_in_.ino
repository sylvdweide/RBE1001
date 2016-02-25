#include <Servo.h> // servo library

Servo right; // Servo object
Servo left; // Servo object

void setup()    // put your setup code here, to run once:
{
  left.attach(6, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
  right.attach(5, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
  Serial.begin(9600);
  driveStraight(48);
}

void stopRobot()    // This function tells the robot to stop
{
    left.write(90); //Stops left motor
    right.write(90); //Stops right motor 
    delay(500);
}

int inchToMS(int in) 
{
    const float RPM = 98.6 ;   //RPM for motors on VEX Basebot
    const double whDiam = 2.75;  //Diameter of wheel with tyres in inches
    double MSPerInch = (36.0/33.0)*(60000/(RPM*whDiam*3.14));//conversion factor for milliseconds to inches, given an RPM and wheel diameter defined above

    return in*MSPerInch;
}


void driveStraight (int inches) 
{
    left.write(15); //motor turns cw and wheel ccw
    right.write(180); //motor turns ccw and wheel cw
    delay(inchToMS(inches));
    stopRobot();
}

void loop() {
  
}

