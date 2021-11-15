
#include "LibDefinitions.h"
#include "LibVariables.h"

#include <OneWire.h>
#include <EEPROM.h>
#include <Servo.h>
#include "RF24.h"

Servo feeder;
RF24 radio (radioPinCE, radioPinCSN);
OneWire oneWire(TEMPERATURE_PIN);
