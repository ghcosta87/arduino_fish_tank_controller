void feederInitializer() {
  if (DEBUG_FEEDER)Serial.println("\nfeederInitializer()");
  feeder.attach(FEEDER_PIN);
  feeder.write(feederCloseAngle);
  feederInititalTime = millis();
}

void checkFeeder() {
  long initialTime = (millis() - feederInititalTime) + minToMili(m_feederTimeRemaining);

  //            ➔ t0 [ms]    ➔ setpoint [ms]
  if (stopWatch(initialTime, hourToMili(fedderInterval)))
    feedNow();
}

void feedNow() {
  feeder.write(feederOpenAngle);
  delay(feederOpenCloseInterval);
  feeder.write(feederCloseAngle);

  feederCounter++;
  setRadioData(rd_feederCounterFeedback, feederCounter);
  feederInititalTime = millis();
  m_feederTimeRemaining = 0;
}

void openFeeder() {
  feeder.write(feederFullOpen);
}

//void gravar_hora() {
//  if ((((millis() - tempo_inicial) / ms_p_h)) * 100 >= (float)tempo_gravar_intervalo_alimentacao / 100) {
//    float timer = ((millis() - tempo_inicial) / ms_p_h) + (((float)tempo_gravado) / 100);
//    m_feederTimeRemaining = (int)(100 * timer);
//  }
//}
