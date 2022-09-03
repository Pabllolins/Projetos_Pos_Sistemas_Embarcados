
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Arduino.h>
#include <Stepper.h>


const int IN1 = 2; //Bobina 1
const int IN2 = 4; //Bobina 2
const int IN3 = 5; //Bobina 3
const int IN4 = 18; //Bobina 4

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(stepsPerRevolution, 2, 4, 5, 18);
Stepper myStepper(stepsPerRevolution, 2, 5, 4, 18);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(3);
  // initialize the serial port:
  Serial.begin(115200);
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}

