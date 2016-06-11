/**@file*/
void robotMove(void)
{
  switch (stateMovement) {
  case STATE_MOV_IDLE:
    Grigoras.stop();
   // delay(200);
    stateMovement = toMove;
    break;
  case STATE_MOV_FRONT:
    if (Grigoras.current_cell.theta == ANGLE_90)Grigoras.current_cell.y--;
    if (Grigoras.current_cell.theta == ANGLE_0) Grigoras.current_cell.x++;
    if (Grigoras.current_cell.theta == ANGLE_180) Grigoras.current_cell.x--;
    if (Grigoras.current_cell.theta == ANGLE_270) Grigoras.current_cell.y++;
    turn=false;
    Grigoras.goForward(18.0);
    stateMovement = STATE_MOV_IDLE;
    break;
  case STATE_MOV_RIGHT:
    turn=true;
    aceleration=1;
    Grigoras.rotate(90);
    odometry(Grigoras.current_cell.theta,STATE_MOV_RIGHT);
    stateMovement =STATE_MOV_FRONT;
    break;
  case STATE_MOV_LEFT:
    turn=true;
    Grigoras.rotate(-90);
    aceleration=1;
    odometry(Grigoras.current_cell.theta,STATE_MOV_LEFT);
    stateMovement =STATE_MOV_FRONT;
    break;
  case STATE_MOV_UTURN:
    turn=true;
    aceleration=1;
    Grigoras.rotate(180);
    odometry(Grigoras.current_cell.theta,STATE_MOV_UTURN);
    stateMovement =STATE_MOV_FRONT;
    break;
  }

}
