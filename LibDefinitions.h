#define VERSION "v.3"

#define DEBUG_LIGHT false
#define DEBUG_TEMP false
#define DEBUG_RADIO false
#define DEBUG_FEEDER false
#define DEBUG_EEPROM false
#define DEBUG_SETUP false
#define DEBUG_SER_CONTROL true

//  output digital pins settings
#define RELAY_FAN_PIN 2
// #define RELAY_CIRCULATION_PIN A1
// #define RELAY_HEATER_PIN A1
#define RELAY_LIGHT_PIN 4
#define RELAY_OZONE 3
#define SETTING_LED_PIN A3 //new

//  input digital pins settings
#define BUTTON_ERASE_PIN A3
#define BUTTON_FEED_PIN A4
#define BUTTON_OPEN_FEEDER A5

#define TEMPERATURE_PIN A1

//  input analog pins settings
#define LDR_PIN A6

//  output pwm pins settings
#define NIGHT_LIGHT_PIN 5 // n ta functionando
#define FEEDER_PIN 6

//  radio settings * reserved pins  9, 10, 11, 12, 13
#define radioPinCE 9
#define radioPinCSN 10
#define writingAddress 3
#define radionSendInterval 1000 // in miliseconds
#define rd_ambientLightnessValue 0
#define rd_feederCounterFeedback 1
#define rd_minTemperature 2
#define rd_maxTemperature 3
#define rd_currentTemperature 4
#define rd_timeNextFeed 5
#define rd_digitalRead 6

//  eeprom settings
const float FLOAT_FORMAT = 0.00f;
#define EEPROM_MAX_VALUE 99.0
#define EEPROM_MIN_VALUE 0.0
#define EEPROM_MEM_POS1 0
#define EEPROM_MEM_POS2 4
#define EEPROM_MEM_POS3 8
#define EEPROM_MEM_POS4 12
#define EEPROM_MEM_POS5 16
#define EEPROM_REC_INTERVAL 5

//  temperature settings
#define TEMPERATURE_READING_INTERVAL 5 // in minutes

//  lighting settings
#define itsBright 18
#define itsDark 19
#define turnOnDelay 1  //  in minutes
#define turnOffDelay 2 //  in minutes

//  feeder settings
#define recoverFedderInterval 20
#define fedderInterval 6            //  in hours
#define feederOpenAngle 49          //  degrees
#define feederCloseAngle 25         //  degrees
#define feederFullOpen 140          //  degrees
#define feederOpenCloseInterval 800 //  in miliseconds
#define feederTintervalBetween 50   //  in miliseconds

//  fan settings
#define swithcingInterval 2 //  in minutes

//  convertion values
#define msToHour 3600000.00
#define msToMinute 60000.00
//const int msToMinute=60000;

//  string constants
#define OneWireMessage "Chip = DS18"
#define oneWireError "no sensor detected"
