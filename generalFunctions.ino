
unsigned long minToMili(int input) {
  //  unsigned long constFormat = (unsigned long)msToMinute;
  //  unsigned long output = input * constFormat;
  //  return output;
  return (unsigned long)(input * (unsigned long)msToMinute);
}

unsigned long hourToMili(int input) {
  return input * (unsigned long)msToHour;
}

float miliToHour(long input) {
  return (float)input / (float)msToHour;
}

float miliToMin(unsigned long input) {
  unsigned long constFormat = (unsigned long)msToMinute;
  return (float)input / (float)constFormat;
}

bool stopWatch(long initialValue, long setpoint) {
  long elapsedTime = millis() - initialValue;
  if (elapsedTime > setpoint) return true;
  return false;
}


String stopWatchValue(long initialValue, long setpoint) {
  long elapsedTime = millis() - initialValue;
  long diference = setpoint - elapsedTime;
  float floatOutput = miliToMin(diference);
  int minutes = (int)floatOutput;
  int seconds = (floatOutput - minutes) * 60;
  String output = (String)minutes + "'" + (String)seconds + "\" ";
  return output;
}

int analogLimit(int input) {
  if (input < 0)input = 0;
  if (input > 255)input = 255;
  return input;
}
