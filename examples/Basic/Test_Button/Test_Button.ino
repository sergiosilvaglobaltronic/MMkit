/**@file*/
/* 
 This example was created by Sérgio Silva
 on the 20th April 2015
 
 This code example is in the public domain. 
 
 Description:
 The LED on pin 13 RED LED turns ON when one of the switch is ON
 
 */
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  //read the pushbutton value and light RED led
  if (digitalRead(3)||digitalRead(2)) {
    digitalWrite(13, HIGH);
  } else{
    digitalWrite(13, LOW);
  }
}



