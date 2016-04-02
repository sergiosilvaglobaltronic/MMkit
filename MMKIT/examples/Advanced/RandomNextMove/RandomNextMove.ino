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
boolean turn=false;
void setup(){
  Grigoras.setupMMkit();                // Starts the MMkit
  Grigoras.goForward(18.0);              //distance to go forward in cm (18.0) means 18.0cm
  Grigoras.setForwardMotionSpeed(500);  //sets forward speed
  Grigoras.waitForStart();            // waits for hand passing front right sensors
}

void loop(){

  if(Grigoras.running()==true) {
    if(turn==false){
      Grigoras.runSpeed();                //moves at the desired speed
    }
    else{
      Grigoras.run();
    }
  }
  else{
    digitalWrite(13,HIGH);
    turn=false;
    stateMovement = nextMove(stateMovement);
    robotMove();

  }
}

void robotMove(void)
{
  switch (stateMovement) {
  case STATE_MOV_IDLE:
    Grigoras.stop();
    delay(2000);
    break;

  case STATE_MOV_FRONT:
    turn=false;
    Grigoras.goForward(18.0);
    break;
  case STATE_MOV_RIGHT:
    turn=true;
    Grigoras.rotate(90);
    break;
  case STATE_MOV_LEFT:
    turn=true;
    Grigoras.rotate(-90);
    break;
  }

}
unsigned char nextMove(unsigned char State)
{
  unsigned char nMove=State;
  switch (nMove) {
  case STATE_MOV_FRONT:
    nMove=rand()%2;  //choose a random move Left or Right
    return nMove+2;
    break;
  case STATE_MOV_RIGHT:
    return STATE_MOV_FRONT;
    break;
  case STATE_MOV_LEFT:
     return STATE_MOV_FRONT;
    break;
  default:
    digitalWrite(13,LOW);
    return STATE_MOV_FRONT;
    break;
  }


}

