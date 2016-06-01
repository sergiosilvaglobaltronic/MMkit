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

#define ANGLE_0    0x01
#define ANGLE_90   0x02
#define ANGLE_180  0x04
#define ANGLE_270  0x08

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
unsigned int velocidade=10;
double aceleration=1;  //usada para chegar a velocidade
void setup(){                            //start maze size  16;14;12;10; 8; 6; 4
  Grigoras.current_cell.x = 5;           // Start x position 0; 1; 2; 3; 4; 5; 6
  Grigoras.current_cell.y =10;          // Start y position 15;14;13;12;11;10; 9
  Grigoras.current_cell.theta = ANGLE_90; // Starts pointing up
  Grigoras.setupMMkit();                // Starts the MMkit
  Grigoras.goForward(18.0);              //distance to go forward in cm (18.0) means 18.0cm
  Grigoras.current_cell.y--;           //goes forward one cell
  Grigoras.setForwardMotionSpeed(velocidade);  //sets forward speed
  Grigoras.waitForStart();            // waits for hand passing front right sensors
}

void loop(){
  
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
    digitalWrite(13,LOW);
    turn=false;
	Grigoras.readIRSensors();
    toMove = nextMove(stateMovement);
    robotMove();
  }
}




