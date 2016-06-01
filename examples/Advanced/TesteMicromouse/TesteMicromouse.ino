/**@file*/
/*
  This example was created by Sérgio Silva
  on the 20th April 2015

  This code example is in the public domain.

  Description:
  The LED on pin 13 RED LED turns ON when one of the switch is ON
  Makes 4 blinking combination switch
  | switchs|  pin
  |Position| value
  | |I 0|  | PIN2  0
  | |I 0|  | PIN3  0
  ------------------
  | |0 I|  | PIN2  1
  | |I 0|  | PIN3  0
  ------------------
  | |I 0|  | PIN2  0
  | |0 I|  | PIN3  1
  ------------------
  | |0 I|  | PIN2  1
  | |0 I|  | PIN3  1

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
char value = B00;
unsigned int velocidade = 10;
double aceleration = 1; //usada para chegar a velocidade
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  Grigoras.setupMMkit();                // Starts the MMkit
  Grigoras.goForward(2000.0);              //distance to go forward in cm (18.0) means 18.0cm
  Grigoras.setForwardMotionSpeed(velocidade);  //sets forward speed if value < 40 = cm/s
}

void loop() {
  value = B00;
  if (digitalRead(3) == 1) {
    value = value | B01;
  }
  if (digitalRead(2) == 1) {
    value = value | B10;
  }
  Serial.println(value,BIN);
  switch (value) {
    case  B11:
      Grigoras.testIRSensors();
      Grigoras.current_cell.wall = B00000000;    // clears cell values
      if ( Grigoras.isWallLeft() == 1) {         // wall 0000 0 LRF  checks if there is a left wall
        Grigoras.current_cell.wall = Grigoras.current_cell.wall | B00000100;
      }
      if ( Grigoras.isWallFront() == 1) {        // wall 0000 0 LRF  checks if there is a front wall
        Grigoras.current_cell.wall = Grigoras.current_cell.wall | B00000001;
      }
      if ( Grigoras.isWallRight() == 1) {        // wall 0000 0 LRF  checks if there is a right wall
        Grigoras.current_cell.wall = Grigoras.current_cell.wall | B00000010;
      }
      Serial.println(Grigoras.current_cell.wall, BIN);
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      delay(1000);
      break;
    case  B10:
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      break;
    case  B01:
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
      break;
    case  B00:
      if (Grigoras.running() == true) {
        acceleration();
        Grigoras.runSpeed();                //moves at the desired speed
      }
      else {
        Grigoras.stop();
      }
      break;
  }
}
