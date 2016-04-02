#include <AccelStepper.h>
#include <MMkit.h>
AccelStepper motorLeft(AccelStepper::DRIVER, 9, 8);
AccelStepper motorRight(AccelStepper::DRIVER, 11, 10);
MMkit MMKIT(motorLeft, motorRight);

void setup(){
  Serial.begin(9600);
  MMKIT.setupMMkit();
  MMKIT.rotateRight(90); // or use MMKIT.rotate(90);
  MMKIT.setForwardMotionSpeed(500);
  delay(2000);
}

void loop(){
  if(MMKIT.running()==true) {
    MMKIT.run();
  }else{
    MMKIT.stop();
  }
}

