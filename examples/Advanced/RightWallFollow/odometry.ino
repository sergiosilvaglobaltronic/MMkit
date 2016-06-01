/**@file*/
unsigned char odometry(unsigned char THETA, unsigned char MOVE){
  //Grigoras.current_cell.theta
  switch (MOVE){
  case STATE_MOV_RIGHT:
    switch (THETA) {
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
    break;
  case STATE_MOV_LEFT:
    switch (THETA) {
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    }
    break;
  case STATE_MOV_UTURN:
    switch (THETA) {
    case ANGLE_90:
      Grigoras.current_cell.theta = ANGLE_270;
      break;
    case ANGLE_0:
      Grigoras.current_cell.theta = ANGLE_180;
      break;
    case ANGLE_270:
      Grigoras.current_cell.theta = ANGLE_90;
      break;
    case ANGLE_180:
      Grigoras.current_cell.theta = ANGLE_0;
      break;
    }
    break;
  }
}






