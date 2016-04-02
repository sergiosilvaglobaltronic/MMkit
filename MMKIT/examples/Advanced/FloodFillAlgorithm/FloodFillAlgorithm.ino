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

int Map[16][16] = {
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

void setup(){
  Grigoras.current_cell.x = 5;           // Start x position
  Grigoras.current_cell.y = 10;          // Start y position
  Grigoras.current_cell.theta = ANGLE_90; // Starts pointing up
  Grigoras.current_cell.weight = 16;      // Start Cell weight
  Grigoras.track[Step] = Grigoras.current_cell;  //Stores current Step
  Grigoras.setupMMkit();                // Starts the MMkit
  Grigoras.goForward(18.0);              //distance to go forward in cm (18.0) means 18.0cm
  Grigoras.current_cell.y--;           //goes forward one cell
  Grigoras.setForwardMotionSpeed(5);  //sets forward speed
  Grigoras.waitForStart();            // waits for hand passing front right sensors
}

void loop(){
 if(Grigoras.running()==true) {
    if(turn==false){
      Grigoras.runSpeed();                //moves at the desired speed if not in turn
     digitalWrite(13,LOW);                 //For debug
  }
    else{
      Grigoras.run();                     //moves in turn
    }   
  }
  else{
     turn=false;
    toMove = nextMove();
    robotMove();

  }
}

void robotMove(void)
{
  switch (stateMovement) {
  case STATE_MOV_IDLE:
    stateMovement = toMove;
    break;

  case STATE_MOV_FRONT:
    turn=false;
    Grigoras.track[Step].wall = Grigoras.current_cell.wall; 
    Grigoras.goForward(18.0);
    Step++;
    if (Grigoras.current_cell.theta == ANGLE_90)Grigoras.current_cell.y--;
    if (Grigoras.current_cell.theta == ANGLE_0) Grigoras.current_cell.x++;
    if (Grigoras.current_cell.theta == ANGLE_180) Grigoras.current_cell.x--;
    if (Grigoras.current_cell.theta == ANGLE_270) Grigoras.current_cell.y++;
    Grigoras.current_cell.weight = Map[Grigoras.current_cell.y][Grigoras.current_cell.x]; //Updates the weight of the new cell
    Grigoras.track[Step].x = Grigoras.current_cell.x;
    Grigoras.track[Step].y = Grigoras.current_cell.y;
    Grigoras.track[Step].weight = Grigoras.current_cell.weight;
    stateMovement = STATE_MOV_IDLE;
    checkTrack();  // Checks for robot movement in same cells
    break;
  case STATE_MOV_RIGHT:
    turn=true;
    Grigoras.rotate(90.0);
    switch (Grigoras.current_cell.theta) {
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
    stateMovement = STATE_MOV_FRONT;
    break;
  case STATE_MOV_LEFT:
   turn=true;
    Grigoras.rotate(-90.0);
    // odometry
    switch (Grigoras.current_cell.theta) {
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    }
    stateMovement = STATE_MOV_FRONT;
    break;
  case STATE_MOV_UTURN:
  turn=true;
    Grigoras.rotate(180.0);
    // odometry
    switch (Grigoras.current_cell.theta) {
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    }
    stateMovement = STATE_MOV_FRONT;
    break;
  case STATE_MOV_STOP:
    Grigoras.stop();
    //disableOutputs
    break;
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


unsigned char nextMove(void)
{
  unsigned char nMove;
  // middle of maze found
  if (((Grigoras.current_cell.x == 7) || (Grigoras.current_cell.x == 8)) && ((Grigoras.current_cell.y == 7) || (Grigoras.current_cell.y == 8))) {
    return STATE_MOV_STOP;
  }
  if ( (Grigoras.current_cell.x == 0) && (Grigoras.current_cell.y == 15))
    return STATE_MOV_STOP;
  if (Grigoras.current_cell.wall==B00000000){
    // odometry
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        Serial.println(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]);
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight & Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]>0 ){
        Serial.println(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]);
        nMove = STATE_MOV_LEFT;
      }
      else{
        nMove = STATE_MOV_RIGHT;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000100){
    // odometry
    Serial.println("Parede esquerda");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000001){
    // odometry
    Serial.println("Parede frente");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      Serial.print(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]);
      Serial.print("<");
      Serial.println(Grigoras.current_cell.weight);
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                            //LRF
  if (Grigoras.current_cell.wall==B00000101){
    // odometry
    Serial.println("Parede esquerda e frente");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000110){
    // odometry
    
    Serial.println("Parede esquerda e direita");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      //digitalWrite(13,HIGH);  // for debug
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000010){
    // odometry
    Serial.println("Parede direita");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000011){
    // odometry
    Serial.println("Parede direita e frente");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;  
    }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF  
  if (Grigoras.current_cell.wall==B00000111){
    Serial.println("Beco sem saida");
    nMove = STATE_MOV_UTURN;
    Map[Grigoras.current_cell.y][Grigoras.current_cell.x]=100+Step;
    for(int i=Step;i>=0;i--){
      if((Grigoras.track[i].wall==B00000101)||(Grigoras.track[i].wall==B00000110)||(Grigoras.track[i].wall==B00000011)){
        Map[Grigoras.track[i].y][Grigoras.track[i].x]=100+Step;
      }
      else{
        Step=i;
        break;
      }
    }
  }
  return nMove;
}

void reMap() {
  for (int i = Step; i >= 0; i--) {
    Grigoras.track[i].weight++;
    Map[Grigoras.track[i].y][Grigoras.track[i].x] = Grigoras.track[i].weight;
  }
  Grigoras.current_cell.weight++;
}


