// → BIBLIOTECAS
#include "Lib.h"

void setup()
{
  Serial.begin(9600);
  Serial.println(VERSION);

  //  file  HardwareSetup.ino
  setPinConfiguration();
  setInititalCondition();

  //  file eepromFunctions.ino
  eepromInitializer();

  //  file oneWireFunctions.ino
  oneWireInitializer();

  //  file servoFunctions.ino
  feederInitializer();

  //  file radioFunctions.ino
  radioInitializer();

  
}

void loop()
{
  //  file lighting.ino
  checkLighting(analogRead(LDR_PIN), digitalRead(RELAY_LIGHT_PIN));

  //  file temperature.ino
  checkTemperature();

  //  file feeder.ino
  //  checkFeeder();

  //  file  fan.ino
  //  checkFan();

  //  file buttons.ino
  //  readButtons();

  //  file eeprom.ino
  //  recordData();

  //  file radio.ino
  //  sendRadioData();

  //  file debug.ino
  //  if(DEBUG)serialOutput();

  //  file buttons.ino
  if (DEBUG_SER_CONTROL)readFromSerial();

  delay(30);
}
