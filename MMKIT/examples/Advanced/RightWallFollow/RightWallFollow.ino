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
void setup(){                            //start maze size  16;14;12;10; 8; 6; 4
  Grigoras.current_cell.x = 5;           // Start x position 0; 1; 2; 3; 4; 5; 6
  Grigoras.current_cell.y =10;          // Start y position 15;14;13;12;11;10; 9
  Grigoras.current_cell.theta = ANGLE_90; // Starts pointing up
  Grigoras.setupMMkit();                // Starts the MMkit
  Grigoras.goForward(18.0);              //distance to go forward in cm (18.0) means 18.0cm
  Grigoras.current_cell.y--;           //goes forward one cell
  Grigoras.setForwardMotionSpeed(7);  //sets forward speed
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
    digitalWrite(13,LOW);
    turn=false;
    toMove = nextMove(stateMovement);
    robotMove();
  }
}

void robotMove(void)
{
  switch (stateMovement) {
  case STATE_MOV_IDLE:
    Grigoras.stop();
   // delay(200);
    stateMovement = toMove;
    break;
  case STATE_MOV_FRONT:
    if (Grigoras.current_cell.theta == ANGLE_90)Grigoras.current_cell.y--;
    if (Grigoras.current_cell.theta == ANGLE_0) Grigoras.current_cell.x++;
    if (Grigoras.current_cell.theta == ANGLE_180) Grigoras.current_cell.x--;
    if (Grigoras.current_cell.theta == ANGLE_270) Grigoras.current_cell.y++;
    turn=false;
    Grigoras.goForward(18.0);
    stateMovement = STATE_MOV_IDLE;
    break;
  case STATE_MOV_RIGHT:
    turn=true;
    Grigoras.rotate(90);
    odometry(Grigoras.current_cell.theta,STATE_MOV_RIGHT);
    stateMovement =STATE_MOV_FRONT;
    break;
  case STATE_MOV_LEFT:
    turn=true;
    Grigoras.rotate(-90);
    odometry(Grigoras.current_cell.theta,STATE_MOV_LEFT);
    stateMovement =STATE_MOV_FRONT;
    break;
  case STATE_MOV_UTURN:
    turn=true;
    Grigoras.rotate(180);
    odometry(Grigoras.current_cell.theta,STATE_MOV_UTURN);
    stateMovement =STATE_MOV_FRONT;
    break;
  }

}
unsigned char nextMove(unsigned char State)
{
  unsigned char nMove=State;
  // middle of maze found
  if (((Grigoras.current_cell.x == 7) || (Grigoras.current_cell.x == 8)) && ((Grigoras.current_cell.y == 7) || (Grigoras.current_cell.y == 8))) {
    if ((Grigoras.current_cell.x == 8)&&(Grigoras.current_cell.y == 8))digitalWrite(13,HIGH);
    return STATE_MOV_STOP;
   }
  switch (Grigoras.current_cell.wall) {
    //LRF
  case B00000000:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000100:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000101:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000111:
    return STATE_MOV_UTURN;
    break; //LRF
  case B00000001:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000110:
    return STATE_MOV_FRONT;
    break; //LRF
  case B00000010:
    return STATE_MOV_FRONT;
    break; //LRF
  case B00000011:
    return STATE_MOV_LEFT;
    break;
  default:
    analogWrite(13,75);
    return STATE_MOV_FRONT;
    break;
  }
}
unsigned char odometry(unsigned char THETA, unsigned char MOVE){
  //Grigoras.current_cell.theta
  switch (MOVE){
  case STATE_MOV_RIGHT:
    switch (THETA) {
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    }
    break;
  case STATE_MOV_LEFT:
    switch (THETA) {
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    }
    break;
  case STATE_MOV_UTURN:
    switch (THETA) {
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    }
    break;
  }
}






