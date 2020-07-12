/*
Control of multiple (six) stepper motors with DRV8825 and the AccelStepper library

Based on example: https://www.brainy-bits.com/control-2-stepper-motors-using-the-arduino-serial-monitor/

"When we first power up the Arduino, the Stepper motors have a position value of ‘zero’.  
So if we enter a minus number the stepper will move counter clockwise and a positive number will move clockwise. 
To return to the starting point we just have to enter a value of zero."

*/

#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. 
// Motor interface type must be set to 1 when using a driver
#define dirPinA 12
#define stepPinA 13

#define dirPinB 10
#define stepPinB 11

#define dirPinC 8
#define stepPinC 9

#define dirPinD 6
#define stepPinD 7

#define dirPinE 4
#define stepPinE 5

#define dirPinF 2
#define stepPinF 3

#define motorInterfaceType 1

// Create a new instances of the AccelStepper class
AccelStepper stepperA = AccelStepper(motorInterfaceType, stepPinA, dirPinA);
AccelStepper stepperB = AccelStepper(motorInterfaceType, stepPinB, dirPinB);
AccelStepper stepperC = AccelStepper(motorInterfaceType, stepPinC, dirPinC);
AccelStepper stepperD = AccelStepper(motorInterfaceType, stepPinD, dirPinD);
AccelStepper stepperE = AccelStepper(motorInterfaceType, stepPinE, dirPinE);
AccelStepper stepperF = AccelStepper(motorInterfaceType, stepPinF, dirPinF);

// Stepper Travel Variables
long TravelA;  // Used to store the A value entered in the Serial Monitor
long TravelB;  // Used to store the B value entered in the Serial Monitor
long TravelC;  // Used to store the C value entered in the Serial Monitor
long TravelD;  // Used to store the D value entered in the Serial Monitor
long TravelE;  // Used to store the E value entered in the Serial Monitor
long TravelF;  // Used to store the F value entered in the Serial Monitor
int move_finished = 1;  // Used to check if move is completed

void setup() {
  Serial.begin(9600);  // Start the Serial monitor with speed of 9600 Bauds
  
  // Print out Instructions on the Serial Monitor at Start
  Serial.println("Enter Travel distance separated by a comma: A,B,C,D,E,F ");
  Serial.print("Enter Move Values Now: ");

  //  Set Max Speed and Acceleration of each Steppers
  // Speeds of more than 1000 steps per second can be unreliable
  stepperA.setMaxSpeed(500.0);
  stepperA.setAcceleration(500.0);

  stepperB.setMaxSpeed(500.0);
  stepperB.setAcceleration(500.0);
  
  stepperC.setMaxSpeed(500.0);
  stepperC.setAcceleration(500.0);

  stepperD.setMaxSpeed(500.0);
  stepperD.setAcceleration(500.0);

  stepperE.setMaxSpeed(500.0);
  stepperE.setAcceleration(500.0);
  
  stepperF.setMaxSpeed(500.0);
  stepperF.setAcceleration(500.0);

}

void loop() {
  while ((Serial.available() > 0) && (move_finished == 1))  { // Check if values are available in the Serial Buffer
  
    move_finished = 0;  // Set variable for checking move of the Steppers
    
    TravelA = Serial.parseInt();  // Put 1st numeric value from buffer in TravelA variable
    Serial.print(TravelA);
    Serial.print(" A Travel, ");
    
    TravelB = Serial.parseInt();  // Put 2nd numeric value from buffer in TravelB variable
    Serial.print(TravelB);  
    Serial.print(" B Travel, ");

    TravelC = Serial.parseInt();  // Put 3rd numeric value from buffer in TravelC variable
    Serial.print(TravelC);  
    Serial.print(" C Travel, ");

    TravelD = Serial.parseInt();  // Put 4th numeric value from buffer in TravelD variable
    Serial.print(TravelD);
    Serial.print(" D Travel, ");
    
    TravelE = Serial.parseInt();  // Put 5th numeric value from buffer in TravelE variable
    Serial.print(TravelE);  
    Serial.print(" E Travel, ");

    TravelF = Serial.parseInt();  // Put 6th numeric value from buffer in TravelF variable
    Serial.print(TravelF);  
    Serial.println(" F Travel");
    
    stepperA.moveTo(TravelA);  // Set new move position for Stepper A
    stepperB.moveTo(TravelB);  // Set new move position for Stepper B
    stepperC.moveTo(TravelC);  // Set new move position for Stepper C
    stepperD.moveTo(TravelD);  // Set new move position for Stepper D
    stepperE.moveTo(TravelE);  // Set new move position for Stepper E
    stepperF.moveTo(TravelF);  // Set new move position for Stepper F
    
    delay(3000);  // Wait 1 seconds before moving the Steppers
    Serial.println("Moving Steppers into position...");
    }

  // Check if the Steppers have reached desired position
  if ((stepperA.distanceToGo() != 0) || (stepperB.distanceToGo() !=0) || 
    (stepperC.distanceToGo() !=0) || (stepperD.distanceToGo() !=0) 
    || (stepperE.distanceToGo() !=0) || (stepperF.distanceToGo() !=0)
    ) {
    
    stepperA.run();  // Move Stepper A into position
    stepperB.run();  // Move Stepper B into position
    stepperC.run();  // Move Stepper C into position
    stepperD.run();  // Move Stepper D into position
    stepperE.run();  // Move Stepper E into position
    stepperF.run();  // Move Stepper F into position
    
  }

  // If move is completed display message on Serial Monitor
  if ((move_finished == 0) && 
  (stepperA.distanceToGo() == 0) && (stepperB.distanceToGo() == 0) && 
  (stepperC.distanceToGo() == 0) && (stepperD.distanceToGo() == 0) 
  && (stepperE.distanceToGo() == 0) && (stepperF.distanceToGo() == 0)
  ) {
    Serial.println("COMPLETED!");
    Serial.println("");
    Serial.println("Enter Next Move Values (0,0,0,0,0,0 for reset): ");  // Get ready for new Serial monitor values
    move_finished = 1;  // Reset move variable
  }

}
