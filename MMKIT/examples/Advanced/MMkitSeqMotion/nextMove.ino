/**@file*/
unsigned char nextMove(unsigned char State)
{
  unsigned char nMove=State;
  switch (nMove) {
  case STATE_MOV_FRONT:  //se andou em frente
    nMove=STATE_MOV_RIGHT;  //choose a random move Left or Right
    return nMove;
    break;
  case STATE_MOV_RIGHT:
    return STATE_MOV_FRONT;
    break;
  case STATE_MOV_LEFT:
     return STATE_MOV_FRONT;
    break;
  default:
    digitalWrite(13,LOW);
    return STATE_MOV_FRONT;
    break;
  }
 }
