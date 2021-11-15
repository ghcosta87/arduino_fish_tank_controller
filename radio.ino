void radioInitializer() {
  if (DEBUG_RADIO)Serial.println("\nradioInitializer()");
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(addresses[writingAddress]);
  if (DEBUG_RADIO)
    (!radio.begin()) ? Serial.println("Radio not responding") : Serial.println("Radio working");
}

void sendRadioData() {
  if (sendDataEnabled)sendDataInitializer = millis(), sendDataEnabled = false;
  //            ~ms ~t0              ~ms ~setpoint
  if (stopWatch(sendDataInitializer, radionSendInterval)) {
    sendDataEnabled = true;
    setRadioData(rd_digitalRead, rd_digitalRead);
    if (!radio.available())!radio.write(&rfOutput, sizeof(rfOutput));
  }
}

void setRadioData(int variable, int value) {
  switch (variable) {
    case rd_digitalRead:
      rfOutput.fanFeedback = digitalRead(RELAY_FAN_PIN);;
      rfOutput.internalLightFeedback = !digitalRead(RELAY_LIGHT_PIN);
      rfOutput.airPmpFeedback  = !digitalRead(RELAY_OZONE);
      break;
    case rd_feederCounterFeedback:
      rfOutput.feederCounterFeedback = value;
      break;
    case rd_minTemperature:
      rfOutput.minTemperature = value;
      break;
    case rd_maxTemperature:
      rfOutput.maxTemperature = value;
      break;
    case rd_currentTemperature:
      rfOutput.currentTemperature = value;
      break;
    case rd_timeNextFeed:
      rfOutput.timeNextFeed = value;
      break;
  }
}
