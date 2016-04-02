/* MMKIT version to control motors
in development
V1.0
*/

#ifndef MMkit_h
#define MMkit_h

#include "Arduino.h"
#include "AccelStepper.h"

class MMkit
{
public:
    // IR thresholds
    #define IR_FRONT_L_THRESHOLD 105  //38
    #define IR_FRONT_R_THRESHOLD 105  //38
    #define IR_LEFT_THRESHOLD    70  //18
    #define IR_RIGHT_THRESHOLD   70
    
    #define _WHEEL_SPACING 81.0 //mm  81
    #define _WHEEL_RADIUS 31.0 //mm   27.5

    int IRsensorsValues[4];
    MMkit(AccelStepper leftMotor, AccelStepper rightMotor);
    
    ///Description: The robot will try to move in its forward direction at the predefined 
    ///forward motion speed. If a front wall is detected, the robot shall rotate right or left.
    ///If walls are sensed on its left and right, it shall move parallel to them and 
    ///in their middle. If only one wall is sensed, it shall move parallel to it.    
    ///Input parameter: none
    ///Output parameter: none 
    void goForward(float cm);
    
    void rotate(float deg);
    
    ///Description: The robot shall rotate in it's axis the specified angle to the Right.
    ///Input parameter: desired angle in degrees
    ///Output parameter: none   
    void rotateRight (float deg);
    
    ///Description: The robot shall rotate in it's axis the specified angle to the Right.
    ///Input parameter: desired angle in degrees
    ///Output parameter: none 
    void rotateLeft(float deg);
    
     
    ///Description: Perform initial configuration
    ///Input parameter: none
    ///Output parameter: none   
    void setupMMkit();
    void run();
    void stop();
    void setIR_LEFT(float LeftCorrection);
    void setIR_RIGHT(float RightCorrection);
    ///Description: Continuously checks for the start signal (hand movement close to the left forward distance sensor where a sequence of high, low and high distances are detected)
    ///Input parameter: none
    ///Output parameter: none 
    void waitForStart();
    
    boolean running();
    void readIRSensors();
    void testIRSensors();
    boolean isWallRight(void);
    boolean isWallLeft(void);
    boolean isWallFront(void);
    
    /*********************/
/* define structures */
/*********************/
struct cell
{
  unsigned char x;
  unsigned char y;
  unsigned char theta;
  unsigned char wall;
  unsigned char weight;
};
    struct cell current_cell;
    struct cell track[156];

    
    ///  Description: Define the Wheel Spacing of the robot
    ///  Input parameter: Wheel Spacing in cm/s
    ///  Output parameter: none
 ///   void setWHEEL_SPACING(float WHEEL_SPACING);
        
    ///  Description: Define the Wheel Spacing of the robot
    ///  Input parameter: Wheel Spacing in cm/s
    ///  Output parameter: none
 ///   void setWHEEL_RADIUS(float WHEEL_RADIUS);
    
    ///  Description: Define the forward motion velocity of the robot
    ///  Input parameter: desired speed in cm/s
    ///  Output parameter: none
    ///  Used by: 
    void setForwardMotionSpeed (float speed); 
    
    ///  Description: Get the configured forward motion velocity of the robot
    ///  Input parameter: none
    ///  Output parameter: speed in cm/s
    float getForwardMotionSpeed(void);
    
    ///Description: Define the forward motion acceleration of the robot.
    ///Input parameter: desired acceleration in cm/s
    ///Output parameter: none
    void setForwardMotionAcceleration (float Acceleration);
    
    ///  Description: Get the configured forward motion acceleration of the robot.
    ///  Input parameter: none
    ///  Output parameter: acceleration in cm/s
    float getForwardMotionAcceleration(void);
    
    void setMaxSpeeds (float leftMaxSpeed, float rightMaxSpeed);
    void runSpeed();
    void runSpeedWalls(float cm);
    void runSpeedRwall(float cm);
    
    void runSpeedLwall(float cm);

private:
    long cmToSteps(float cm);
    long stepsToCm(float steps);
    float _leftSpeed;
    float _rightSpeed;
    AccelStepper _leftMotor;
    AccelStepper _rightMotor;
};

#endif
