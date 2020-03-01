/*
  Basic sketch to control a stepper motor with an A4988
  The stepper motor used is in a NEMA17 enclosure, with 1.8 deg/step (=200 steps per revolution)

  Adapted from:
  https://dronebotworkshop.com/stepper-motors-with-arduino/
  
  Stepper Motor Demonstration 4
  Stepper-Demo4.ino
  Demonstrates NEMA 17 Bipolar Stepper with A4988 Driver

  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Define Constants

// Connections to A4988
const int dirPin = 2;  // Direction
const int stepPin = 3; // Step

// Motor steps per rotation
const int STEPS_PER_REV = 200; // full step = 200
const int N = 30; // multiplier, because we have a gear head for reduction; also used to define range (how much of full rotation should be made?)

// Interval - controls speed
const int interval = 1000;

void setup() {
  
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  
  // Set motor direction clockwise
  digitalWrite(dirPin,HIGH); 

  // Spin motor N rotations quickly
  for(int x = 0; x < (STEPS_PER_REV * N); x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(interval);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(interval);
  }

  // Pause for one second
  delay(1000);
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin,LOW);

  // Spin motor N rotations quickly
  for(int x = 0; x < (STEPS_PER_REV * N); x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(interval);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(interval);
  }
  
  // Pause for one second
  delay(1000);
}
