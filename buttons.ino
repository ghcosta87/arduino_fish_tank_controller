void readButtons() {
  if (!digitalRead(BUTTON_ERASE_PIN)) {
    blynk(BUTTON_ERASE_PIN);
    delay(1000);
    cleanMemory();  //  file eepromFunctions.ino
  }

  if (!digitalRead(BUTTON_OPEN_FEEDER)) {
    blynk(BUTTON_OPEN_FEEDER);
    delay(1000);
    openFeeder();   //  file servoFunctions.ino
  }

  if (!digitalRead(BUTTON_FEED_PIN)) {
    blynk(BUTTON_FEED_PIN);
    delay(1000);
    feedNow();    //  file servoFunctions.ino
  }
}

void blynk(int settingsIndex) {
  int blynkTimes = 0;
  switch (settingsIndex) {
    case BUTTON_ERASE_PIN: blynkTimes = 3;
      break;
    case BUTTON_OPEN_FEEDER: blynkTimes = 4;
      break;
    case BUTTON_FEED_PIN: blynkTimes = 2;
      break;
  }
  for (int i = 0; i < blynkTimes; ++i ) {
    digitalWrite(settingsIndex, HIGH);
    delay(200);
    digitalWrite(settingsIndex, LOW);
    delay(200);
  }
}

void readFromSerial() {

  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'e') {
      Serial.println(F("################## APAGANDO EEPROM"));
      blynk(BUTTON_ERASE_PIN);
      delay(1000);
      cleanMemory();  //  file eepromFunctions.ino
    }

    //  if (!digitalRead(BUTTON_OPEN_FEEDER)) {
    //    blynk(BUTTON_OPEN_FEEDER);
    //    delay(1000);
    //    openFeeder();   //  file servoFunctions.ino
    //  }

    if (command == 'f') {
      Serial.println(F("################## ALIMENTANDO MANUALMENTE"));
      blynk(BUTTON_FEED_PIN);
      delay(1000);
      feedNow();    //  file servoFunctions.ino
    }
  }
}
