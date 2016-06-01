/**@file*/
void robotMove(void)
{
  a=a+1;
  switch (a) {
  case STATE_MOV_IDLE:
    Grigoras.stop();
    delay(2000);
    break;

  case STATE_MOV_FRONT:
    turn=false;
    Grigoras.goForward(18.0);
    break;
  case STATE_MOV_RIGHT:
    turn=true;
    Grigoras.rotate(90);
    break;
  case STATE_MOV_LEFT:
    turn=true;
    Grigoras.rotate(-90);
    break;
  }

}
