/**@file*/
unsigned char nextMove(void)
{
  unsigned char nMove;
  // middle of maze found
  if (((Grigoras.current_cell.x == 7) || (Grigoras.current_cell.x == 8)) && ((Grigoras.current_cell.y == 7) || (Grigoras.current_cell.y == 8))) {
    return STATE_MOV_STOP;
  }
  if ( (Grigoras.current_cell.x == 0) && (Grigoras.current_cell.y == 15))
    return STATE_MOV_STOP;
  if (Grigoras.current_cell.wall==B00000000){
    // odometry
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        Serial.println(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]);
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight & Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]>0 ){
        Serial.println(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]);
        nMove = STATE_MOV_LEFT;
      }
      else{
        nMove = STATE_MOV_RIGHT;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000100){
    // odometry
    Serial.println("Parede esquerda");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000001){
    // odometry
    Serial.println("Parede frente");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      Serial.print(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]);
      Serial.print("<");
      Serial.println(Grigoras.current_cell.weight);
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                            //LRF
  if (Grigoras.current_cell.wall==B00000101){
    // odometry
    Serial.println("Parede esquerda e frente");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_RIGHT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000110){
    // odometry
    
    Serial.println("Parede esquerda e direita");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      //digitalWrite(13,HIGH);  // for debug
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000010){
    // odometry
    Serial.println("Parede direita");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_FRONT;
      }
      else if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF
  if (Grigoras.current_cell.wall==B00000011){
    // odometry
    Serial.println("Parede direita e frente");
    if(Grigoras.current_cell.theta == ANGLE_90){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x-1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_0) {
      if(Map[Grigoras.current_cell.y-1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;  
    }
    } 
    if(Grigoras.current_cell.theta == ANGLE_180){
      if(Map[Grigoras.current_cell.y+1][Grigoras.current_cell.x]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
    if(Grigoras.current_cell.theta == ANGLE_270){
      if(Map[Grigoras.current_cell.y][Grigoras.current_cell.x+1]<Grigoras.current_cell.weight){
        nMove = STATE_MOV_LEFT;
      }
      else{
        reMap();
        nMove = STATE_MOV_IDLE;
      }
    }
  }                          //LRF  
  if (Grigoras.current_cell.wall==B00000111){
    Serial.println("Beco sem saida");
    nMove = STATE_MOV_UTURN;
        if(75+Step<=255){
          Map[Grigoras.current_cell.y][Grigoras.current_cell.x]=75+Step;
        }else{
          Map[Grigoras.current_cell.y][Grigoras.current_cell.x]=255;
        }
    for(int i=Step;i>=0;i--){
      if((Grigoras.track[i].wall==B00000101)||(Grigoras.track[i].wall==B00000110)||(Grigoras.track[i].wall==B00000011)){
        if(75+i<=255){
          Map[Grigoras.track[i].y][Grigoras.track[i].x]=75+i;
        }else{
          Map[Grigoras.track[i].y][Grigoras.track[i].x]=255;
        }
      }
      else{
        Step=i;
        break;
      }
    }
  }
  return nMove;
}
