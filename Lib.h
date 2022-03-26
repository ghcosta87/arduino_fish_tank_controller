#include "LibDefinitions.h"
#include "LibVariables.h"

#include <OneWire.h>
#include <EEPROM.h>
#include <Servo.h>

#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

Servo feeder;
RF24 radio (radioPinCE, radioPinCSN);
OneWire oneWire(TEMPERATURE_PIN);
