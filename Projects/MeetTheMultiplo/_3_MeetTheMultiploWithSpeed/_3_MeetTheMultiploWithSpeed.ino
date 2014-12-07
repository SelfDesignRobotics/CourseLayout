//
// MeetTheMultiplo ... with speed control.
//
// Identical to _2_MeetTheMultiploDebugged except ...
//
// We have added speed control to slow down/speed up movement
//

// Import Statements
#include <IRremote.h>
#include <DCMotor.h>

// Constants

#define SPEED        50

#define NOTHING_NEW  0
#define FORWARD      2
#define BACKWARD     8
#define LEFT         4
#define RIGHT        6
#define STOP         5
#define GO_FASTER    1
#define GO_SLOWER    7

// Definition of Global Variables and Objects
IRrecv irReceiver(A0);                // setup IR sensor on S0 input

DCMotor motor0(M0_EN, M0_D0, M0_D1);  // Setup a motor for each wheel
DCMotor motor1(M1_EN, M1_D0, M1_D1);

//
// setup
//
// Run once at the very start to setup the robot
//
// Notes:
//
// The wheels on the robot are driven by two seperate motors ...
// we've called these motors motor0 and motor1.
// 
void setup()
{
  // setup the motors to work together to drive the robot.
  motor0.setClockwise(false);
  motor1.setClockwise(false);

  // Initialize serial communication ... 
  // ... helps us fix the robot when it is not working
  Serial.begin(9600);
}

//
// loop
//
// Called repetitively after initial call to setup() 
// until the power is turned off or the reset button is 
// pressed.
//
// Each time loop() is called check for new input
// from the remote control and change the robot
// behaviour based on this input.
//
void loop()
{
   int code = 0;
   int pace0, pace1;
   
   code = irReceiver.getIRRemoteCode();
 
   switch (code) {
     case FORWARD:
        motor0.setSpeed(SPEED);
        motor1.setSpeed(SPEED);
        break;    
     case BACKWARD:
        motor0.setSpeed(-SPEED);
        motor1.setSpeed(-SPEED);
        break;
     case RIGHT:
        motor0.setSpeed(-SPEED);
        motor1.setSpeed(SPEED);
        break;
     case LEFT:
        motor0.setSpeed(SPEED);
        motor1.setSpeed(-SPEED);
        break;
     case GO_FASTER:
        pace0 = motor0.getSpeed() + 1;
        motor0.setSpeed(pace0);
        pace1 = motor1.getSpeed() + 1;
        motor1.setSpeed(pace1);
        break;
     case GO_SLOWER:
        pace0 = motor0.getSpeed() - 1;
        motor0.setSpeed(pace0);
        pace1 = motor1.getSpeed() - 1;
        motor1.setSpeed(pace1);
        break;
     case STOP:
        motor0.setSpeed(0);
        motor1.setSpeed(0);
        break;
     case NOTHING_NEW:
        // Nothing has changed ... 
        // just keep doing last command
        break;
     default:
       // we have no action for this input ...
       // ... dump it to the serial monitor for debugging
       // Otherwise, ignore it.
       if ( code != 0) {
         Serial.print("Robot got - ");
         Serial.println (code);   
       }
   }
}
