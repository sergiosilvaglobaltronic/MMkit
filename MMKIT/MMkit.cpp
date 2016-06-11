/* MMKIT version to control motors
 in development
 V1.0
 */

/*

 MUST Be INCLUDED IN Main Program 
 MMkit.setup();
 MMkit.run(); //Must be called regularly
 //MMkit.runSpeed(); // If we want to use constant speed
 //MMkit.runSpeedWalls(Distance_From_Walls); // use to mantain a certain discance from both walls
 //MMkit.runSpeedRwall(Distance_From_R_wall); // use to mantain a certain discance from Right wall
 //MMkit.runSpeedLwall(Distance_From_L_wall); // use to mantain a certain discance from Left wall
 
 AccelStepper motorLeft(AccelStepper::DRIVER, 9, 8);
 AccelStepper motorRight(AccelStepper::DRIVER, 11, 10);
 
 */


#include "Arduino.h"
#include "MMkit.h"
#include "AccelStepper.h"

AccelStepper    _motorLeft;
AccelStepper    _motorRight;

// IR SENSOR PINS
const int LED_LF = 4;  
const int LED_DL = 5;  
const int LED_DR = 6;  
const int LED_RF = 7;  

const int LEFT_DG = A2;   //A1  //For version 1
const int LEFT_FT = A1;   //A0  //For version 1
const int RIGHT_DG = A3;
const int RIGHT_FT = A0;
boolean Running=false;


int reading=0;
int _right_Correction=555;//-60
int _left_Correction=555;  //90

float _leftSpeed = 474.0; //default _leftSpeed 500
float _rightSpeed = 474.0; //default _rightSpeed 500
int _speed=6;

int sensorDark, sensorLight;
const int IRsensorsPairs[][2] = {
  { 
    LED_LF, LEFT_FT  }
  ,
  { 
    LED_DR, RIGHT_DG  }
  ,
  { 
	LED_DL, LEFT_DG  }
  ,
  //{                           //for version 1
  //  LED_DR, RIGHT_DG  }
  //,
  { 
        LED_RF, RIGHT_FT   }
};



MMkit::MMkit(AccelStepper motorLeft, AccelStepper motorRight) {
  _motorLeft = motorLeft;
  _motorRight = motorRight;
  _leftSpeed = 474.0; //default _leftSpeed 500
  _rightSpeed = 474.0; //default _rightSpeed 500
}

void MMkit::readIRSensors() {
  for (int i=0;i<4;i++){
    digitalWrite(IRsensorsPairs[i][0], LOW);
    sensorDark = analogRead(IRsensorsPairs[i][1]);
    digitalWrite(IRsensorsPairs[i][0], HIGH);
    delayMicroseconds(3);
    sensorLight = analogRead(IRsensorsPairs[i][1]);
    digitalWrite(IRsensorsPairs[i][0], LOW);
    IRsensorsValues[i] = sensorLight - sensorDark;
    /* 
     Serial.print("Sensor ");
     Serial.print(i);
     Serial.print(" = ");
     Serial.println(IRsensorsValues[i]);
     */
  } 
}
void MMkit::testIRSensors() {
  for (int i=0;i<4;i++){
    digitalWrite(IRsensorsPairs[i][0], LOW);
    sensorDark = analogRead(IRsensorsPairs[i][1]);
    digitalWrite(IRsensorsPairs[i][0], HIGH);
    delayMicroseconds(3);
    sensorLight = analogRead(IRsensorsPairs[i][1]);
    digitalWrite(IRsensorsPairs[i][0], LOW);
    IRsensorsValues[i] = sensorLight - sensorDark;
     
     Serial.print("Sensor ");
     Serial.print(i);
     Serial.print(" = ");
     Serial.println(IRsensorsValues[i]);

  } 
}

void MMkit::setIR_LEFT(float LeftCorrection){
 _left_Correction = LeftCorrection;    
 }
 
 void MMkit::setIR_RIGHT(float RightCorrection){
 _right_Correction = RightCorrection;    
 }
 
void MMkit::setForwardMotionSpeed (float speed) {
     if(speed<80){
     speed=158*speed;
     _speed=speed;
     }
  _motorLeft.setSpeed(speed);
  _motorRight.setSpeed(speed);
  _leftSpeed = speed; //default _leftSpeed 500
  _rightSpeed = speed; //default _rightSpeed 500
}

float MMkit::getForwardMotionSpeed(void){
  return _motorLeft.speed();
}

void MMkit::setForwardMotionAcceleration (float Acceleration) {
  _motorLeft.setAcceleration(Acceleration);
  _motorRight.setAcceleration(Acceleration);
}

float MMkit::getForwardMotionAcceleration(void){
  return 10000;
}

void MMkit::setMaxSpeeds (float leftMaxSpeed, float rightMaxSpeed) {
  _motorLeft.setMaxSpeed(leftMaxSpeed);
  _motorRight.setMaxSpeed(rightMaxSpeed);
}

//Definition of Movement related functions


boolean MMkit::running() {

    /* if (_motorLeft.distanceToGo() > 0 || _motorRight.distanceToGo() > 0) {                            
     return Running;
     }
     else {
     return Running=false;
     }*/
	if (_motorLeft.isRunning()&& _motorRight.isRunning()) {                            
     return Running;
    }
    else return Running=false;
}

long MMkit::cmToSteps(float cm)
{
  return (long)((cm * 10.0 *10.0 * 158.0)/(_WHEEL_RADIUS * 3.14159265358979 * 2.0));//171
}

long MMkit::stepsToCm(float steps)
{
  return ((long)((float)(steps *(_WHEEL_RADIUS * 3.14159265358979))/1580.0));//1580
}

void MMkit::goForward(float cm) {
  _motorLeft.move(cmToSteps(cm));
  _motorRight.move(cmToSteps(cm));
  Running=true;
}

void MMkit::rotate(float deg) {//positive rotates Right, negative rotates Left
   _motorLeft.setCurrentPosition(0);
   _motorRight.setCurrentPosition(0);  
  deg=deg/10;
  _motorLeft.move(cmToSteps((deg/360.0)*3.14159265358979*(_WHEEL_SPACING+10))); 
  _motorRight.move(-cmToSteps((deg/360.0)*3.14159265358979*(_WHEEL_SPACING+10)));
  Running=true;
}

void MMkit::rotateRight (float deg) { //Positive turns LEFT!!!  Negative turns RIGHT!!! (going backwards)
  deg=deg/10;
  _motorLeft.move(cmToSteps((deg/360.0)*3.14159265358979*_WHEEL_SPACING*2));
  //_motorRight.move(-cmToSteps((deg/360.0)*3.14159265358979*_WHEEL_SPACING*2)/4);
  _motorRight.move(0.0);
  Running=true;
}

void MMkit::rotateLeft(float deg) {//Positive turns Right, Negative turns Left (going backwards)
     deg=deg/10;
    _motorLeft.setCurrentPosition(0);
    _motorRight.setCurrentPosition(0);
    _motorRight.move(cmToSteps((deg/360.0)*3.14159265358979*_WHEEL_SPACING*2));
    _motorLeft.move(0.0);
  Running=true;
}


void MMkit::setupMMkit()
{
  pinMode(13, OUTPUT);
  pinMode(LED_LF, OUTPUT);
  digitalWrite(LED_LF, LOW);
  pinMode(LED_DL, OUTPUT);
  digitalWrite(LED_DL, LOW);
  pinMode(LED_DR, OUTPUT);
  digitalWrite(LED_DR, LOW);
  pinMode(LED_RF, OUTPUT);
  digitalWrite(LED_RF, LOW);
  _motorLeft.setPinsInverted(true, false, true);
  _motorLeft.setMaxSpeed(10000); //80000
  _motorRight.setMaxSpeed(10000); //80000
  _motorLeft.setAcceleration(1000);//20000
  _motorRight.setAcceleration(1000);//20000
  _motorLeft.setSpeed(_leftSpeed); //Must be set once to allow movement, setSpeed(float, float) should be called after moveTo, not needed to be called after move()
  _motorRight.setSpeed(_rightSpeed); //Must be set once to allow movement
}

void MMkit::waitForStart(){
   readIRSensors();
   delay(100);
   
  while(IRsensorsValues[0]<450||(6000 / (IRsensorsValues[1]- 17) - 4 )<6) {
    readIRSensors();
    digitalWrite(13,HIGH);
	int Diference_Between_Right_Left=abs(IRsensorsValues[1]-IRsensorsValues[2]); // get the difference between right and left sensor
    analogWrite(13,Diference_Between_Right_Left);
    Serial.println("Waiting for hand in front left and right");                         
  } 
  delay(500);
  digitalWrite(13,LOW);
}

void MMkit::run() {
/*
     if(_motorLeft.distanceToGo() >0){
        while ((_motorLeft.distanceToGo() > 0) || (_motorRight.distanceToGo() < 0)) {                           
               _motorLeft.run();
               _motorRight.run(); 
       }
     }
     if(_motorRight.distanceToGo()>0){
        while ((_motorLeft.distanceToGo() < 0) || (_motorRight.distanceToGo() > 0)) {                           
               _motorLeft.run();
               _motorRight.run(); 
       }
     
     }
*/
        while ((_motorLeft.isRunning()) && (_motorRight.isRunning())) {                           
               _motorLeft.run();
               _motorRight.run(); 
        }
}
void MMkit::stop() {
  _motorLeft.move(0);
  _motorRight.move(0);  
}

void MMkit::runSpeed() {
  reading++;
  if(reading>79){
   readIRSensors();
   reading=0;
   //Serial.println(_motorRight.distanceToGo());              
   }
  
  
  current_cell.wall = B00000000;    // clears cell values
  if (isWallLeft() == 1) {         // wall 0000 0 LRF  checks if there is a left wall
    current_cell.wall = current_cell.wall | B00000100;
  }
  if (isWallFront() == 1) {        // wall 0000 0 LRF  checks if there is a front wall
    current_cell.wall = current_cell.wall | B00000001;
  }
  if (isWallRight() == 1) {        // wall 0000 0 LRF  checks if there is a right wall
    current_cell.wall = current_cell.wall | B00000010;
  }
  switch(current_cell.wall){
	  case  B00000110:  // if there is left and right wall 
         _motorLeft.setSpeed(_leftSpeed-(IRsensorsValues[1]-IRsensorsValues[2]));
         _motorRight.setSpeed(+(_rightSpeed+(IRsensorsValues[1]-IRsensorsValues[2])));
      break;
      case B00000100:  //Left wall
         _motorRight.setSpeed(+(_rightSpeed+(_left_Correction-IRsensorsValues[2])));
         _motorLeft.setSpeed(_leftSpeed-(_left_Correction-IRsensorsValues[2]));
      break;
      case B00000010:  //Right wall
	     //Serial.println("Right Wall");
         _motorRight.setSpeed(+(_rightSpeed-(_right_Correction-IRsensorsValues[1])));
         _motorLeft.setSpeed(_leftSpeed+(_right_Correction-IRsensorsValues[1])/3);
      break;
  default:
    _motorLeft.setSpeed(_leftSpeed);
    _motorRight.setSpeed(+_rightSpeed);
    break;
  }
  //Serial.println(IRsensorsValues[3]); 
  if(IRsensorsValues[0]>750&&IRsensorsValues[3]>750){
    if(_motorRight.distanceToGo()>1000&&_motorLeft.distanceToGo()>1000){
         if(current_cell.theta=0x02)current_cell.y++;
         if(current_cell.theta=0x01)current_cell.x--;
         if(current_cell.theta=0x04)current_cell.x++; 
         if(current_cell.theta=0x08)current_cell.y--;
         digitalWrite(13,HIGH);
    }
    _motorLeft.setCurrentPosition(0);
    _motorRight.setCurrentPosition(0);                                              
    _motorLeft.setSpeed(+_leftSpeed);
    _motorRight.setSpeed(_rightSpeed);                                            
 
  }
  _motorLeft.runSpeed();
  _motorRight.runSpeed();
  running();
}

void MMkit::runSpeedWalls(float cm) {
  _motorLeft.runSpeed();
  _motorRight.runSpeed();
}
boolean MMkit::isWallLeft(void)
{
  if (IRsensorsValues[2] < IR_LEFT_THRESHOLD) return 0;
  else return 1;

}

boolean MMkit::isWallRight(void)
{
  if (IRsensorsValues[1] < IR_RIGHT_THRESHOLD) return 0;
  else return 1;

}

boolean MMkit::isWallFront(void)
{
  if ((IRsensorsValues[0] < IR_FRONT_R_THRESHOLD) && (IRsensorsValues[3] < IR_FRONT_L_THRESHOLD)) return 0;
  else return 1;

}

