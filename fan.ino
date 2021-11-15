void checkFan() {
  if (highTemperature() && !fanTimerEnabled) {
    fanInititalTime = millis();
    fanTimerEnabled = true;
    digitalWrite(RELAY_FAN_PIN, HIGH);
  }                   //           ➔ t0 [ms]        ➔ setpoint [ms]
  if (fanTimerEnabled && stopWatch(fanInititalTime, minToMili(swithcingInterval) && lowTemperature())) {
    digitalWrite(RELAY_FAN_PIN, LOW);
    fanTimerEnabled = false;
  }
}

bool highTemperature() {
  return (currentTemp >= maxTemp);
}

bool lowTemperature() {
  return (currentTemp <= minTemp);
}
