/**@file*/
unsigned char nextMove(unsigned char State)
{
  if (Serial1.available())  //verifica se tem dados diponível para leitura
  {
    byteRead = Serial1.read(); //le bytwe mais recente no buffer da serial
    if (byteRead != '4') {
      Serial1.write(byteRead);
      if (byteRead == '1') {
        return STATE_MOV_FRONT;
        digitalWrite(13, HIGH);
        Serial.write(byteRead);
      }
      if (byteRead == '0') {
        digitalWrite(13, LOW);
        return STATE_MOV_STOP;
        Serial.write(byteRead);
      }
      if (byteRead == '3') {
        digitalWrite(13, HIGH);
        return STATE_MOV_RIGHT;
        Serial.write(byteRead);
      }
      if (byteRead == '2') {
        digitalWrite(13, LOW);
        return STATE_MOV_LEFT;
        Serial.write(byteRead);
      }
      if (byteRead == '5') {
        digitalWrite(13, LOW);
        return STATE_MOV_UTURN;
        Serial.write(byteRead);
      }
      Serial.write(byteRead);//reenvia para o computador o dado recebido
    }
  } else {
    return STATE_MOV_IDLE;

  }
}
