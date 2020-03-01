/*
Basic control of a stepper motor with an A4988 and the AccelStepper library
Continous rotation in one direction

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
  // Speeds of more than 1000 steps per second can be unreliable
  stepper.setMaxSpeed(1000);
}

void loop() {
  // Set the speed in steps per second
  stepper.setSpeed(800);
  // Step the motor with a constant speed as set by setSpeed()
  stepper.runSpeed();

  // To turn in opposite direction:
  // stepper.setSpeed(-800) 
}
