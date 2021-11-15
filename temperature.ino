
void oneWireInitializer() {
  if (DEBUG_TEMP)Serial.println("\noneWireInitializer()");
  oneWire.search(sensorAdress);

  bool sensorConnected = true;
  String sensorModel;

  switch (sensorAdress[0]) {
    case 0x10:
      sensorType = 1;
      sensorModel = "S20";  // or old DS1820
      break;
    case 0x28:
      sensorType = 0;
      sensorModel = "B20";
      break;
    case 0x22:
      sensorType = 0;
      sensorModel = "22";
      break;
    default:
      sensorConnected = false;
  }
  if (DEBUG_TEMP)
    (sensorConnected) ? Serial.println(OneWireMessage + sensorModel), readOneWireSensor()
    : Serial.println(oneWireError);
}

void checkTemperature() {
  if (DEBUG_TEMP)Serial.println("\ncheckTemperature()");
  bool readTemperature = false;
  (readTimerEnabled) ? readTimerEnabled = false, tempReadInitializer = millis()
                                          : readTemperature = stopWatch(tempReadInitializer, minToMili(TEMPERATURE_READING_INTERVAL));
  if (readTemperature)
    currentTemp = readOneWireSensor();

  setRadioData(rd_currentTemperature, currentTemp);
  if (DEBUG_TEMP)
    Serial.println("next reading in: " + stopWatchValue(tempReadInitializer, minToMili(TEMPERATURE_READING_INTERVAL)) + "mins");
}

int readOneWireSensor() {  // rever essa bosta
  if (DEBUG_TEMP)Serial.println("\nreadOneWireSensor()");
  byte i;
  byte data[12];
  float celsius;

  oneWire.reset();
  oneWire.select(sensorAdress);
  oneWire.write(0x44, 1);        // start conversion, with parasite power on at the end

  delay(1000);

  oneWire  .reset();
  oneWire.select(sensorAdress);
  oneWire.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = oneWire.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (sensorType) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  }
  else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  }
  celsius = ((float)raw / 16.0) * 100;
  celsius = (int)celsius;
  if (DEBUG_TEMP)Serial.println("current temperature: " + (String)(celsius / 100));
  return celsius;
}
