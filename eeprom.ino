void eepromInitializer() {
  if (DEBUG_SETUP)Serial.println("\neepromInitializer()");

  minTemp = (EEPROM.get(EEPROM_MEM_POS1, FLOAT_FORMAT)) * 100;
  maxTemp = (EEPROM.get(EEPROM_MEM_POS2, FLOAT_FORMAT)) * 100;
  feederCounter = (EEPROM.get(EEPROM_MEM_POS3, FLOAT_FORMAT)) * 100;
  m_feederTimeRemaining = (EEPROM.get(EEPROM_MEM_POS4, FLOAT_FORMAT)) * 100;

  if (DEBUG_SETUP) {
    String outputMessage = "minTemp:" + (String)minTemp + "\nmaxTemp:" + (String)maxTemp + "\ncounter:" + (String)feederCounter + "\nremainingTime:" + (String)m_feederTimeRemaining;
    Serial.println(outputMessage);
  }
}

void cleanMemory()
{
  EEPROM.put(EEPROM_MEM_POS1, EEPROM_MAX_VALUE);
  EEPROM.put(EEPROM_MEM_POS2, EEPROM_MIN_VALUE);
  EEPROM.put(EEPROM_MEM_POS3, EEPROM_MIN_VALUE);
  EEPROM.put(EEPROM_MEM_POS4, EEPROM_MIN_VALUE);

  contagem = EEPROM.get(EEPROM_MEM_POS3, FLOAT_FORMAT);
}

void recordData()
{
  if (stopWatch(recorderInititalTime, minToMili(EEPROM_REC_INTERVAL))) {
    temperatureRecorder();
    feederRecorder();
  }
}


void temperatureRecorder() {
  if (currentTemp < m_minTemp)
  {
    minTemp = currentTemp; //temperatura minima
    m_minTemp = minTemp;
    setRadioData(rd_minTemperature, m_minTemp);
    EEPROM.put(EEPROM_MEM_POS1, ((float)temperaturaMin) / 100);
  }
  if (currentTemp > m_maxTemp)
  {
    maxTemp = currentTemp; //temperatura maxima
    m_maxTemp = maxTemp;
    setRadioData(rd_maxTemperature, m_maxTemp);
    EEPROM.put(EEPROM_MEM_POS2, ((float)temperaturaMax) / 100);
  }
  //  if (temperatura < 0 || temperatura > 40) {
  //    alarme[4] = true;
  //  }
}

void feederRecorder() {
  m_feederCounter = feederCounter;
  EEPROM.put(EEPROM_MEM_POS3, ((float)m_feederCounter) / 100);
  EEPROM.put(EEPROM_MEM_POS4, m_feederTimeRemaining);
}
