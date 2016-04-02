/* 
 This example was created by Sérgio Silva
 on the 20th April 2015
 
 This code example is in the public domain. 
 
 Description:
 The robot moves forward the desired distance in cm
 
 */
#include <AccelStepper.h>                // Accelaration library
#include <MMkit.h>                       // MMkit library

AccelStepper motorLeft(AccelStepper::DRIVER, 9, 8);  // declaration of motorLeft to control the MMkit
AccelStepper motorRight(AccelStepper::DRIVER, 11, 10);  // declaration of motorRight to control the MMkit

MMkit Grigoras(motorLeft, motorRight);  // declaration of object variable to control the MMkit

enum statesRobotMovements {
  STATE_MOV_IDLE,
  STATE_MOV_FRONT,
  STATE_MOV_RIGHT,
  STATE_MOV_LEFT,
  STATE_MOV_UTURN,
  STATE_MOV_STOP
};

unsigned char stateMovement = STATE_MOV_FRONT;
unsigned char toMove = STATE_MOV_FRONT;

void setup(){
  Grigoras.setupMMkit();                // Starts the MMkit
  Grigoras.goForward(20.0);              //distance to go forward in cm (18.0) means 18.0cm
  Grigoras.setForwardMotionSpeed(20);  //sets forward speed if value < 40 = cm/s
  Grigoras.waitForStart();            // waits for hand passing front right sensors
}

void loop(){
  if(Grigoras.running()==true) {
    Grigoras.runSpeed();                //moves at the desired speed
  }
  else{
    Grigoras.stop();  
  }
}



