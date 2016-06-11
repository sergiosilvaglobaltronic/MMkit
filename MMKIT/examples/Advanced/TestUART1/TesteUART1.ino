/**@file*/
/* 
 This example was created by Sérgio Silva 
 Globaltronic
 on the 2nd Feb 2016
 
 Description:
 Just connect your bluetooth module to the front available pins.
 From left to right the pinout is Vcc Gnd Rx TX. 
 The schematic bellow shows the connections (remenber that Rx from MMkit Connects to Tx of Bluetooth module
 and Tx from MMkit Connects to Rx of Bluetooth module
             
             __     __
            __2   1__
        | |  o o o o  | |
       - 3   V G RxTx  0 -                 |
  |00| |      MMKIT      | |00|   (150)    | W
  |00|motorLeft  motorRight|00| <------->  | A
  |00| !                 | |00|            | L
       |                 |                 | L
        _________________                  |

This code example is in the public domain. 

*/
 
#include <AccelStepper.h>                // Accelaration library
#include <MMkit.h>                       // MMkit library

AccelStepper motorLeft(AccelStepper::DRIVER, 9, 8);  // declaration of motorLeft to control the MMkit
AccelStepper motorRight(AccelStepper::DRIVER, 11, 10);  // declaration of motorRight to control the MMkit
unsigned long previousMicros=0;

MMkit Grigoras(motorLeft, motorRight);  // declaration of object variable to control the MMkit

void setup(){
  Grigoras.setupMMkit();                // Starts the MMkit
  motorLeft.disableOutputs();           // To turn off motors use: motorLeft.enableOutputs(); //to enable motors
  motorRight.disableOutputs();           // To turn off motors use: motorRight.enableOutputs(); //to enable motors                                // 
  Serial1.begin(9600);                   // Enable UART1 
 }

void loop(){
  delay(50);  //increase to see in serial port decrease to see in led
  Serial1.println("MMKIT");
}



