/*
 * Control a stepper motor with an A4988 and rotary encoder
 * The stepper motor used is in a NEMA17 enclosure, with 1.8 deg/step (=200 steps per revolution)
 * Relies on enabling the internal pull-up resistors (otherwise could use external pull-up resistors or a module)
 * 
 * Based on: https://www.brainy-bits.com/nema-motor-with-rotary-encoder-part-2/
*/

// Define Constants

// Connections to A4988
const int dirPin = 8;  // Direction
const int stepPin = 9; // Step

// Rotary Encoder Module connections
const int PinCLK = 2;   // Generating interrupts using CLK signal
const int PinDT = 3;    // Reading DT signal
const int PinSW = 4;    // Reading Push Button switch

volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean rotationdirection;  // CW or CCW rotation

int StepperPosition = 0;    // To store Stepper Motor Position
int StepsToTake = 8;      // Controls the speed of the Stepper per Rotary click
int direction;   // Variable to set Rotation (CW-CCW) of stepper

// Interrupt routine runs if CLK goes from HIGH to LOW
void rotarydetect ()  {
  delay(4);  // delay for Debouncing
  
  if (digitalRead(PinCLK)) {
    rotationdirection= digitalRead(PinDT);
  } else {
    rotationdirection= !digitalRead(PinDT);
  }
  
  TurnDetected = true;
}

void setup() {
  
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  // Set pins to Input
  pinMode(PinCLK,INPUT);  
  pinMode(PinDT,INPUT);  
  pinMode(PinSW,INPUT);

  digitalWrite(PinCLK, HIGH); //turn pullup resistor on
  digitalWrite(PinDT, HIGH); //turn pullup resistor on
  digitalWrite(PinSW, HIGH); // Pull-Up resistor for switch
  
  attachInterrupt (0,rotarydetect,FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO

}


void loop ()  {

  // Code below used to reset to initial position based on button push
  // Comment if not needed
   if (!(digitalRead(PinSW))) {   // check if button is pressed
    if (StepperPosition == 0) {  // check if button was already pressed
    } else {
      if (StepperPosition > 0) {  // Stepper was moved CW
        while (StepperPosition != 0) {  //  Do until Motor position is back to ZERO
          digitalWrite(dirPin, HIGH);
          for (int x = 1; x < StepsToTake; x++) {
              digitalWrite(stepPin, HIGH);
              delay(1);
              digitalWrite(stepPin, LOW);
              delay(1);            
            }
          StepperPosition = StepperPosition - StepsToTake;
        }
      } else {
        while (StepperPosition != 0) { 
          digitalWrite(dirPin, LOW);
          for (int x = 1; x < StepsToTake; x++) {
              digitalWrite(stepPin, HIGH);
              delay(1);
              digitalWrite(stepPin, LOW);
              delay(1);            
          }
          StepperPosition = StepperPosition + StepsToTake;
        }
      }
      StepperPosition = 0; // Reset position to ZERO after moving motor back
    }
  }

  // Runs if rotation was detected
  if (TurnDetected)  {
    TurnDetected = false;  // do NOT repeat IF loop until new rotation detected
    
    // Which direction to move Stepper motor
    if (rotationdirection) {
      digitalWrite(dirPin, HIGH);
      for (int x = 1; x < StepsToTake; x++) {
        digitalWrite(stepPin, HIGH);
        delay(1);
        digitalWrite(stepPin, LOW);
        delay(1);            
      }
      StepperPosition = StepperPosition - StepsToTake;
    }

    if (!rotationdirection) {
      digitalWrite(dirPin, LOW); 
      for (int x = 1; x < StepsToTake; x++) {
        digitalWrite(stepPin, HIGH);
        delay(1);
        digitalWrite(stepPin, LOW); 
        delay(1);         
      }
      StepperPosition = StepperPosition + StepsToTake;
    }
  }
}

