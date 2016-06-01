/**@file*/
void robotMove(void)
{
  switch (stateMovement) {
  case STATE_MOV_IDLE:
    stateMovement = toMove;
    break;

  case STATE_MOV_FRONT:
    turn=false;
    Grigoras.track[Step].wall = Grigoras.current_cell.wall; 
    Grigoras.goForward(18.0);
    Step++;
    if (Grigoras.current_cell.theta == ANGLE_90)Grigoras.current_cell.y--;
    if (Grigoras.current_cell.theta == ANGLE_0) Grigoras.current_cell.x++;
    if (Grigoras.current_cell.theta == ANGLE_180) Grigoras.current_cell.x--;
    if (Grigoras.current_cell.theta == ANGLE_270) Grigoras.current_cell.y++;
    Grigoras.current_cell.weight = Map[Grigoras.current_cell.y][Grigoras.current_cell.x]; //Updates the weight of the new cell
    Grigoras.track[Step].x = Grigoras.current_cell.x;
    Grigoras.track[Step].y = Grigoras.current_cell.y;
    Grigoras.track[Step].weight = Grigoras.current_cell.weight;
    stateMovement = STATE_MOV_IDLE;
    checkTrack();  // Checks for robot movement in same cells
    break;
  case STATE_MOV_RIGHT:
    turn=true;
    aceleration=1;
    Grigoras.rotate(90.0);
    switch (Grigoras.current_cell.theta) {
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    }
    stateMovement = STATE_MOV_FRONT;
    break;
  case STATE_MOV_LEFT:
   turn=true;
   aceleration=1;
    Grigoras.rotate(-90.0);
    // odometry
    switch (Grigoras.current_cell.theta) {
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    }
    stateMovement = STATE_MOV_FRONT;
    break;
  case STATE_MOV_UTURN:
  turn=true;
  aceleration=1;
    Grigoras.rotate(180.0);
    // odometry
    switch (Grigoras.current_cell.theta) {
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    }
    stateMovement = STATE_MOV_FRONT;
    break;
  case STATE_MOV_STOP:
    Grigoras.stop();
    //disableOutputs
    break;
  }
}

