/**@file acceleration.ino*/
void acceleration(void)
{
  unsigned long currentMicros = micros();
  if (currentMicros>= previousMicros + 900) {
    previousMicros = currentMicros;
    if (aceleration <= velocidade) {
      Grigoras.setForwardMotionSpeed((int) aceleration);
      aceleration = aceleration + aceleration / 100;
    } 
  }
}