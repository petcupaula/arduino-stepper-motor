/*
Control of multiple stepper motors with A4988 and the AccelStepper library

Based on example: https://www.brainy-bits.com/control-2-stepper-motors-using-the-arduino-serial-monitor/
*/

#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. 
// Motor interface type must be set to 1 when using a driver
#define dirPinA 53
#define stepPinA 52

#define dirPinB 51
#define stepPinB 50

#define dirPinC 49
#define stepPinC 48

#define motorInterfaceType 1

// Create a new instances of the AccelStepper class
AccelStepper stepperA = AccelStepper(motorInterfaceType, stepPinA, dirPinA);
AccelStepper stepperB = AccelStepper(motorInterfaceType, stepPinB, dirPinB);
AccelStepper stepperC = AccelStepper(motorInterfaceType, stepPinC, dirPinC);


// Stepper Travel Variables
long TravelA;  // Used to store the A value entered in the Serial Monitor
long TravelB;  // Used to store the B value entered in the Serial Monitor
long TravelC;  // Used to store the C value entered in the Serial Monitor
int move_finished = 1;  // Used to check if move is completed

void setup() {
  Serial.begin(9600);  // Start the Serial monitor with speed of 9600 Bauds
  
  // Print out Instructions on the Serial Monitor at Start
  Serial.println("Enter Travel distance separated by a comma: A,B,C ");
  Serial.print("Enter Move Values Now: ");

  //  Set Max Speed and Acceleration of each Steppers
  // Speeds of more than 1000 steps per second can be unreliable
  stepperA.setMaxSpeed(500.0);
  stepperA.setAcceleration(500.0);

  stepperB.setMaxSpeed(500.0);
  stepperB.setAcceleration(500.0);
  
  stepperC.setMaxSpeed(500.0);
  stepperC.setAcceleration(500.0);

}

void loop() {
  while (Serial.available() > 0)  { // Check if values are available in the Serial Buffer
  
    move_finished = 0;  // Set variable for checking move of the Steppers
    
    TravelA = Serial.parseInt();  // Put First numeric value from buffer in TravelA variable
    Serial.print(TravelA);
    Serial.print(" A Travel , ");
    
    TravelB = Serial.parseInt();  // Put Second numeric value from buffer in TravelB variable
    Serial.print(TravelB);  
    Serial.print(" B Travel ");

    TravelC = Serial.parseInt();  // Put Second numeric value from buffer in TravelC variable
    Serial.print(TravelC);  
    Serial.println(" C Travel ");
    
    stepperA.moveTo(TravelA);  // Set new move position for Stepper A
    stepperB.moveTo(TravelB);  // Set new move position for Stepper B
    stepperC.moveTo(TravelC);  // Set new move position for Stepper C
    
    delay(1000);  // Wait 1 seconds before moving the Steppers
    Serial.print("Moving Steppers into position...");
    }

  // Check if the Steppers have reached desired position
  if ((stepperA.distanceToGo() != 0) || (stepperB.distanceToGo() !=0) || (stepperC.distanceToGo() !=0)) {
    
    stepperA.run();  // Move Stepper A into position
    stepperB.run();  // Move Stepper B into position
    stepperC.run();  // Move Stepper C into position
    
  }

  // If move is completed display message on Serial Monitor
  if ((move_finished == 0) && (stepperA.distanceToGo() == 0) && (stepperB.distanceToGo() == 0) && (stepperC.distanceToGo() == 0)) {
    Serial.println("COMPLETED!");
    Serial.println("");
    Serial.println("Enter Next Move Values (0,0,0 for reset): ");  // Get ready for new Serial monitor values
    move_finished = 1;  // Reset move variable
  }

}
