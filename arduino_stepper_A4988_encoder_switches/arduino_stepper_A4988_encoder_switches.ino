/*
 * Control a stepper motor with an A4988, a rotary encoder, and 2 limit switches
 * 
 * The stepper motor used is in a NEMA17 enclosure, with 1.8 deg/step (=200 steps per revolution)
 * The usage of the rotary encoder relies on enabling the internal pull-up resistors 
 * (otherwise could use external pull-up resistors or a module)
 * 
 * Based on: https://www.brainy-bits.com/nema-motor-with-rotary-encoder-part-2/ and 
 * https://www.brainy-bits.com/stepper-motor-with-joystick-and-limit-switches/
*/

// Define Constants

// Connections to A4988
const int dirPin = 8;  // Direction
const int stepPin = 9; // Step

// Rotary Encoder Module connections
const int PinCLK = 2;   // Generating interrupts using CLK signal
const int PinDT = 3;    // Reading DT signal
const int PinSW = 4;    // Reading Push Button switch

// Limit switch connections
const int Limit1Pin = 11;
const int Limit2Pin = 12;

volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean rotationdirection;  // CW or CCW rotation

int StepperPosition = 0;    // To store Stepper Motor Position
int StepsToTake = 8;      // Controls the speed of the Stepper per Rotary click
int direction;   // Variable to set Rotation (CW-CCW) of stepper

int limit1, limit2;

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

  pinMode(Limit1Pin, INPUT_PULLUP);
  pinMode(Limit2Pin, INPUT_PULLUP);

  pinMode(13, OUTPUT); // optional: use on-board LED to show status of limit switch(es)

}


void loop ()  {

  if((limit1 = digitalRead(Limit1Pin)) && (limit2 = digitalRead(Limit2Pin))) {  
    // If the switches are not activated, operate as usual
  
    // Runs if rotation was detected
    if (TurnDetected)  {
      TurnDetected = false;  // do NOT repeat IF loop until new rotation detected
      
      // Which direction to move Stepper motor
      if (rotationdirection) {
        digitalWrite(dirPin, LOW);
        for (int x = 1; x < StepsToTake; x++) {
          digitalWrite(stepPin, HIGH);
          delay(1);
          digitalWrite(stepPin, LOW);
          delay(1);            
        }
        StepperPosition = StepperPosition - StepsToTake;
      }
  
      if (!rotationdirection) {
        digitalWrite(dirPin, HIGH); 
        for (int x = 1; x < StepsToTake; x++) {
          digitalWrite(stepPin, HIGH);
          delay(1);
          digitalWrite(stepPin, LOW); 
          delay(1);         
        }
        StepperPosition = StepperPosition + StepsToTake;
      }
    }

    digitalWrite(13, LOW); // optional: turn on-board LED OFF
  }
  else { 
    // One of the switches is activated. 
    // Move away!

    digitalWrite(13, HIGH); // optional: turn on-board LED ON to signal danger!

    if(!limit1) {    
      while (!digitalRead(Limit1Pin)) {
        digitalWrite(dirPin, HIGH); 
        for (int x = 1; x < StepsToTake; x++) {
          digitalWrite(stepPin, HIGH);
          delay(1);
          digitalWrite(stepPin, LOW); 
          delay(1);         
        }
        StepperPosition = StepperPosition + StepsToTake;
      }
    } 
    else {
      while (!digitalRead(Limit2Pin)) {
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

    // Out of danger zone. Continue. 
  }
}

