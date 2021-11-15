void checkLighting(int ldrValue, int relayLightStatus) {
  //  ldrValue = analogRead(A0);

  if (DEBUG_LIGHT)Serial.println("\ncheckLighting(int ldrValue:" + (String)ldrValue + ", int relayLightStatus:" + (String)relayLightStatus + ")");

  int brightness = map(ldrValue, 0, 1000, 0, 100);

  bool turnLightOn = !relayLightStatus; //  verificar se precisar inicializar assim

  if (brightness > itsBright)turnLightOn = lightTurnOnEnabler(relayLightStatus);
  if (brightness < itsDark)turnLightOn = lightTurnOffEnabler(relayLightStatus);

  if (brightness > itsDark && brightness < itsBright) {
    if (DEBUG_LIGHT)Serial.println("\nSETTING IN BETWEEN CONDITION TURNING OFF ALL TIMERS");
    turnOnOnline = false;
    turnOffOnline = false;
  }

  if (turnLightOn) {
    digitalWrite(RELAY_LIGHT_PIN, LOW);
    digitalWrite(RELAY_OZONE, LOW);
    nightLedFader(false, ldrValue);
  } else {
    digitalWrite(RELAY_LIGHT_PIN, HIGH);
    digitalWrite(RELAY_OZONE, HIGH);
    nightLedFader(true, brightness);
  }
//Serial.println("next reading in: " + stopWatchValue(tempReadInitializer, minToMili(TEMPERATURE_READING_INTERVAL)) + "min");
  if (DEBUG_LIGHT) {
    Serial.println("\nEnd of\ncheckLighting(int ldrValue:" + (String)ldrValue + ", int relayLightStatus:" + (String)relayLightStatus + ")");
    Serial.println("brightness: " + (String)brightness);
    Serial.println("turnLightOn: " + (String)turnLightOn);
    Serial.println("relayLightStatus: " + (String)relayLightStatus);
    Serial.println("turnOnOnline: " + (String)turnOnOnline + " ~ " + stopWatchValue(turnOnInitialTime, minToMili(turnOnDelay)) + "min");
//    (String)miliToMin(millis() - turnOnInitialTime));
    Serial.println("turnOffOnline: " + (String)turnOffOnline + " ~ " +stopWatchValue(turnOffInitialTime, minToMili(turnOffDelay)) + "min");
//     (String)miliToMin(millis() - turnOffInitialTime));
  }
}


bool lightTurnOnEnabler(bool relayLightStatus) {
  turnOffOnline = false;

  if (DEBUG_LIGHT)
    Serial.println("\nlightTurnOnEnabler(bool relayLightStatus" + (String)relayLightStatus + ")");

  if (!relayLightStatus) { //  if the light is off
    if (!turnOnOnline) {  //  and the timer is not running
      Serial.println("\nRESETING TIMER turnOnOnline");
      turnOnOnline = true;  //  set the time to turn on
      turnOnInitialTime = millis(); //  and initialize the timer to turn on
    } else {                          //  ~ms ~t0          ~min ~setpoint
      if (turnOnOnline && stopWatch(turnOnInitialTime, minToMili(turnOnDelay))) { //((millis() - espera_p_ligar) / ms_p_m > tempo_lig_luz_p)) {
        turnOnOnline = false;
        Serial.println("\nCAN SWITCH ON");
        return true; // 1;
        //      }
      } else {
        return false; //!relayLightStatus;
      }
    }
  }
  return true; //!relayLightStatus;
}

bool lightTurnOffEnabler(bool relayLightStatus) {
  turnOnOnline = false;

  if (DEBUG_LIGHT)
    Serial.println("\nlightTurnOffEnabler(bool relayLightStatus" + (String)relayLightStatus + ")");

  if (relayLightStatus) {
    if (!turnOffOnline) {
      Serial.println("\nRESETING TIMER turnOffInitialTime");
      turnOffOnline = true;
      turnOffInitialTime = millis();
    } else {                          //  ~ms ~t0          ~min ~setpoint
      if (turnOffOnline && stopWatch(turnOffInitialTime, minToMili(turnOffDelay))) {
        //((millis() - espera_p_desligar) / ms_p_m > tempo_desl_luz_p)) {
        turnOffOnline = false;
        Serial.println("\nCAN SWITCH OFF");
        return false;
      }//0;
      else {
        //        Serial.println("\nWAITING TIMER TO TURN OFF");
        //        Serial.println("turnOffInitialTime: " + (String)turnOffInitialTime);
        //        long elapsedTime = millis() - turnOffInitialTime;
        //        Serial.println("elapsedTime: " + (String)elapsedTime);
        //        Serial.println("turnOffDelay: " + (String)turnOffDelay);
        //        unsigned long emMilli = minToMili(turnOffDelay);
        //        Serial.println("minToMili(turnOffDelay): " + (String)emMilli);
        //        Serial.println("stopWatch: " + (String)stopWatch(turnOffInitialTime, minToMili(turnOffDelay)));
        //        unsigned long timeremaining = emMilli - elapsedTime;
        //        Serial.print("time remaining: " + (String)timeremaining);
        //        float teste = miliToMin(timeremaining);
        //        Serial.println(" ~ " + (String)teste + " minutes");
        return true;
      }
    } //!estado_luz_p;
    //    }
  }
  //  Serial.println("turnOffInitialTime: " + (String)turnOffInitialTime);
  //  long elapsedTime = millis() - turnOffInitialTime;
  //  Serial.println("elapsedTime: " + (String)elapsedTime);
  //  Serial.println("turnOffDelay: " + (String)turnOffDelay);
  //  unsigned long emMilli = minToMili(turnOffDelay);
  //  Serial.println("minToMili(turnOffDelay): " + (String)emMilli);
  //  Serial.println("stopWatch: " + (String)stopWatch(turnOffInitialTime, minToMili(turnOffDelay)));
  //  unsigned long timeremaining = emMilli - elapsedTime;
  //  Serial.print("time remaining: " + (String)timeremaining);
  //  float teste = miliToMin(timeremaining);
  //  Serial.println(" ~ " + (String)teste + " minutes");
  if (!turnOffOnline && !stopWatch(turnOffInitialTime, minToMili(turnOffDelay)))
    return false;//!estado_luz_p;
}

void nightLedFader(bool activate, int brightness) {
  int intensity = map(brightness, 0, itsDark, 20, 255);
  (activate) ? analogWrite(NIGHT_LIGHT_PIN, analogLimit(intensity)) : digitalWrite(NIGHT_LIGHT_PIN, 0);
  if (DEBUG_LIGHT) {
    Serial.println("\nnightLedFader(bool activate, int brightness)");
    Serial.println("intensity: " + (String)intensity);
    Serial.println("activate: " + (String)activate + " ~ " + (String)digitalRead(NIGHT_LIGHT_PIN));
    Serial.println("analogLimit(intensity): " + (String)analogLimit(intensity));
  }
}
