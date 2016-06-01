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
int value=0; 
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  //read the pushbutton value and blink RED led
 value=digitalRead(2)+digitalRead(3);
 switch (value) {
    case 0:    
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      delay(1000);
      break;
    case 1:    
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      break;
    case 2:   
       digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
      break;
  }
}
