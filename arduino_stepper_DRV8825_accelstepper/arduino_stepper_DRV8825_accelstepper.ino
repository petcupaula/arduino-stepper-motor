/*
Basic control of a stepper motor with a DRV8825 and the AccelStepper library

Demo 1: Continous rotation in one direction.
Demo 2: Acceleration and deceleration, moving to a prespecified position, and back. 

Based on example: https://www.makerguides.com/a4988-stepper-motor-driver-arduino-tutorial/
https://www.makerguides.com/drv8825-stepper-motor-driver-arduino-tutorial/

The code for DRV8825 and A4988 is basically the same 
(same motorInterfaceType = 1, i.e. driver)
Note that in terms of wiring, there is a difference in how the logic voltage is supplied.

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
  stepper.setAcceleration(400);
}

void demo1() {
  // Set the speed in steps per second
  stepper.setSpeed(800);
  // Step the motor with a constant speed as set by setSpeed()
  stepper.runSpeed();

  // To turn in opposite direction:
  // stepper.setSpeed(-800) 
}

void demo2() {
  // Set the target position:
  stepper.moveTo(0000);
  // Run to target position with set speed and acceleration/deceleration:
  stepper.runToPosition();
  
  delay(1000);
  
  // Move back to zero:
  stepper.moveTo(0);
  stepper.runToPosition();
  
  delay(1000);

  // Note: The function stepper.runToPostion() is blocking, 
  // so don’t use this when you need to control other things at the same time.
  
}

void loop() {
  //demo1();
  //delay(2000);
  demo2();
  delay(2000);
}
