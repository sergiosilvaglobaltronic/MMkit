/**@file*/
void robotMove(void)
{
  switch (stateMovement) {
    case STATE_MOV_IDLE:
      digitalWrite(13,HIGH);
      break;
    case STATE_MOV_STOP:
      Grigoras.stop();
      delay(2000);
      break;
    case STATE_MOV_FRONT:
      turn = false;
       aceleration=1;
      Grigoras.goForward(18.0);
      break;
    case STATE_MOV_RIGHT:
      turn = true;
       aceleration=1;
      Grigoras.rotate(90);
      break;
    case STATE_MOV_UTURN:
      turn = true;
       aceleration=1;
      Grigoras.rotate(180);
      break;
    case STATE_MOV_LEFT:
      turn = true;
       aceleration=1;
      Grigoras.rotate(-90);
      break;
  }

}
