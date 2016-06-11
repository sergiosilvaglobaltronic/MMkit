/**@file*/
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


byte byteRead;
unsigned char stateMovement = STATE_MOV_FRONT;
unsigned char toMove = STATE_MOV_FRONT;
boolean turn=false;
unsigned int velocidade=10;
double aceleration=1;  //usada para chegar a velocidade
// usadas para comunicação
unsigned int integerValue=0;  // valor máximo 65535
char incomingByte;
void setup(){
  Serial1.begin(9600);
  Grigoras.setupMMkit();                // Starts the MMkit
  Grigoras.goForward(18.0);              //distance to go forward in cm (18.0) means 18.0cm
  Grigoras.setForwardMotionSpeed(1);  //sets forward speed
  Grigoras.waitForStart();            // waits for hand passing front right sensors
}


void loop() {
    if(Grigoras.running()==true) {
    if(turn==false){
      acceleration();
      Grigoras.runSpeed();                //moves at the desired speed
    }
    else{
      Grigoras.run();
    }
  }
  else{
    turn=false;
    stateMovement = nextMove(stateMovement);
    robotMove();

  }

}
