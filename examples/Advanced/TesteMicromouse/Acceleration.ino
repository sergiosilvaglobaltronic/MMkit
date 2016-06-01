/**@file*/
void acceleration(void)
{
if (aceleration<=velocidade){
    Grigoras.setForwardMotionSpeed((int) aceleration);
    aceleration=aceleration+aceleration/100;
    //Serial.println((int) aceleration);
	   delayMicroseconds(900);
    }else{
      //Serial.println((int) aceleration);
	     delayMicroseconds(900);
    }
}
