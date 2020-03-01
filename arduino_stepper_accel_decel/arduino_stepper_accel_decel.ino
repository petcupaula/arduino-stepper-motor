/*
Control of a stepper motor with an A4988 and the AccelStepper library
with acceleration and deceleration

Based on example: https://www.makerguides.com/a4988-stepper-motor-driver-arduino-tutorial/

*/

#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. 
// Motor interface type must be set to 1 when using a driver
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed in steps per second
  stepper.setMaxSpeed(1000);

  // Add in acceleration
  stepper.setAcceleration(400);
}

void loop() {
  // Set the target position:
  stepper.moveTo(6000);
  // Run to target position with set speed and acceleration/deceleration:
  stepper.runToPosition();
  delay(1000);
  
  // Move back to zero:
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(1000);
}
