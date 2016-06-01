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

uint8_t Map[16][16] ={
  {    16, 15, 14, 13, 12, 11, 10,  9,  9, 10, 11, 12, 13, 14, 15, 16 },
  {    15, 14, 13, 12, 11, 10,  9,  8,  8,  9, 10, 11, 12, 13, 14, 15 },
  {    14, 13, 12, 11, 10,  9,  8,  7,  7,  8,  9, 10, 11, 12, 13, 14 },
  {    13, 12, 11, 10,  9,  8,  7,  6,  6,  7,  8,  9, 10, 11, 12, 13 },
  {    12, 11, 10,  9,  8,  7,  6,  5,  5,  6,  7,  8,  9, 10, 11, 12 },
  {    11, 10,  9,  8,  7,  6,  5,  4,  4,  5,  6,  7,  8,  9, 10, 11 },
  {    10,  9,  8,  7,  6,  5,  4,  3,  3,  4,  5,  6,  7,  8,  9, 10 },
  {     9,  8,  7,  6,  5,  4,  3,  2,  2,  3,  4,  5,  6,  7,  8,  9 },
  {     9,  8,  7,  6,  5,  4,  3,  2,  2,  3,  4,  5,  6,  7,  8,  9 },
  {    10,  9,  8,  7,  6,  5,  4,  3,  3,  4,  5,  6,  7,  8,  9, 10 },
  {    11, 10,  9,  8,  7,  6,  5,  4,  4,  5,  6,  7,  8,  9, 10, 11 },
  {    12, 11, 10,  9,  8,  7,  6,  5,  5,  6,  7,  8,  9, 10, 11, 12 },
  {    13, 12, 11, 10,  9,  8,  7,  6,  6,  7,  8,  9, 10, 11, 12, 13 },
  {    14, 13, 12, 11, 10,  9,  8,  7,  7,  8,  9, 10, 11, 12, 13, 14 },
  {    15, 14, 13, 12, 11, 10,  9,  8,  8,  9, 10, 11, 12, 13, 14, 15 },
  {    16, 15, 14, 13, 12, 11, 10,  9,  9, 10, 11, 12, 13, 14, 15, 16 }
};


unsigned char stateMovement = STATE_MOV_FRONT;
unsigned char toMove = STATE_MOV_FRONT;
boolean turn=false;
unsigned int Step=0;
unsigned int velocidade=10;
double aceleration=1;  //usada para chegar a velocidade

void setup(){
  Grigoras.current_cell.x = 5;           // Start x position
  Grigoras.current_cell.y = 10;          // Start y position
  Grigoras.current_cell.theta = ANGLE_90; // Starts pointing up
  Grigoras.current_cell.weight = 16;      // Start Cell weight
  Grigoras.track[Step] = Grigoras.current_cell;  //Stores current Step
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
      Grigoras.runSpeed();                //moves at the desired speed if not in turn
  }
    else{
      Grigoras.run();                     //moves in turn
    }   
  }
  else{
    digitalWrite(13,LOW);
    turn=false;
	Grigoras.readIRSensors();
    toMove = nextMove();
    robotMove();

  }
}


void checkTrack(){
      // this for is used to check if the robot already passed a certain cell and to take another in that case
    for(int i=Step-1;i>=0;i--){
      if((Grigoras.track[i].x==Grigoras.current_cell.x)&&(Grigoras.track[i].y==Grigoras.current_cell.y)){
        //Direction of last time the robot passed this cell        
        switch (Grigoras.track[i].theta){
        case ANGLE_90:
           if(Grigoras.current_cell.theta == ANGLE_0)stateMovement = STATE_MOV_RIGHT;
          if(Grigoras.current_cell.theta == ANGLE_180) stateMovement = STATE_MOV_LEFT;
          Step=i;
          break;
        case ANGLE_0:
          //digitalWrite(13,HIGH);  // for debug
          if(Grigoras.current_cell.theta == ANGLE_90)stateMovement = STATE_MOV_LEFT;
          if(Grigoras.current_cell.theta == ANGLE_270) stateMovement = STATE_MOV_RIGHT;
          Step=i;
          break;
        case ANGLE_270:
          //digitalWrite(13,HIGH);  // for debug
          if(Grigoras.current_cell.theta == ANGLE_0)stateMovement = STATE_MOV_RIGHT;
          if(Grigoras.current_cell.theta == ANGLE_180) stateMovement = STATE_MOV_LEFT;
          Step=i;
          break;
        case ANGLE_180:
          //digitalWrite(13,HIGH);   // for debug
          if(Grigoras.current_cell.theta == ANGLE_90)stateMovement = STATE_MOV_LEFT;
          if(Grigoras.current_cell.theta == ANGLE_270) stateMovement = STATE_MOV_RIGHT;
          Step=i;
          break;
        }
        break;
      }
    }

 }




void reMap() {
  for (int i = Step; i >= 0; i--) {
    if((Grigoras.track[i].wall==B00000101)||(Grigoras.track[i].wall==B00000110)||(Grigoras.track[i].wall==B00000011)){
    Grigoras.track[i].weight++;
    Map[Grigoras.track[i].y][Grigoras.track[i].x] = Grigoras.track[i].weight;
    }else{
        Grigoras.current_cell.weight++;
        break;
    }
  Grigoras.current_cell.weight++;
}
}

