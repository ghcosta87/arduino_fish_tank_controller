#include <OneWire.h>

byte type_s;
byte addr[8];

OneWire ds(A1);

void inicializar_onewire() {
  ds.search(addr);
  switch (addr[0]) {
    case 0x10:
      Serial.println("> Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("> Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("> Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("> Device is not a DS18x20 family device.");
      return;
  }
}

int ler_one_wire() {
  byte i;
  byte data[12];
  float celsius;

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  delay(1000);

  ds  .reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
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
  return celsius;
}
