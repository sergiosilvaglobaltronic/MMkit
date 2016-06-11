/**@file*/
unsigned char nextMove(unsigned char State)
{
  unsigned char nMove=State;
  // middle of maze found
  if (((Grigoras.current_cell.x == 7) || (Grigoras.current_cell.x == 8)) && ((Grigoras.current_cell.y == 7) || (Grigoras.current_cell.y == 8))) {
    if ((Grigoras.current_cell.x == 8)&&(Grigoras.current_cell.y == 8))digitalWrite(13,HIGH);
    return STATE_MOV_STOP;
   }
  switch (Grigoras.current_cell.wall) {
    //LRF
  case B00000000:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000100:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000101:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000111:
    return STATE_MOV_UTURN;
    break; //LRF
  case B00000001:
    return STATE_MOV_RIGHT;
    break; //LRF
  case B00000110:
    return STATE_MOV_FRONT;
    break; //LRF
  case B00000010:
    return STATE_MOV_FRONT;
    break; //LRF
  case B00000011:
    return STATE_MOV_LEFT;
    break;
  default:
    analogWrite(13,75);
    return STATE_MOV_FRONT;
    break;
  }
}
