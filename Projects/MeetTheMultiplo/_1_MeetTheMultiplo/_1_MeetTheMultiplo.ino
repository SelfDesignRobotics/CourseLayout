//
// MeetTheMultiplo
//
// Operate the multiplo robot using the hand-held remote provided
// in the Multiplo Builder's kit.
//
// Requirements:
//    1. Assemble the basic robot from 'Meeting the Multiplo' project
//    2. the Multiplo IR 38 KHz sensor connected to port S0
//    3. a standard RC5 remote control ... like the one in the Builder's 
//       Robot Kit.
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
        // Otherwise, ignore it.
        break;
    }
}
