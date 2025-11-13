#ifndef ADXL345_H
#define ADXL345_H

#include <Arduino.h>

// ==========================================
// ADXL345 SENSOR CONFIGURATION
// ==========================================

struct ADXL345Config {
  // Pin configuration (I2C mode)
  int sdaPin = D2;           // SDA pin (GPIO4)
  int sclPin = D1;           // SCL pin (GPIO5)

  // Optional pins
  int csPin = D8;            // CS pin (GPIO15) - set HIGH for I2C mode
  int int1Pin = D3;          // INT1 pin (GPIO0) - interrupt 1
  int int2Pin = D4;          // INT2 pin (GPIO2) - interrupt 2
  int sdoPin = -1;           // SDO/ALT ADDRESS pin (connect to GND for 0x53, VCC for 0x1D)

  // VCC and GND are power pins (connect to 3.3V and GND respectively)

  // I2C address (0x53 if SDO is LOW, 0x1D if SDO is HIGH)
  uint8_t i2cAddress = 0x53;

  // Sensor settings
  uint8_t range = 2;         // Range: 2, 4, 8, or 16 (in g)
  uint8_t dataRate = 10;     // Data rate code (see datasheet, 10 = 100Hz)

  // Timing
  unsigned long readInterval = 3000;  // Read every 3000ms (3 seconds)
  unsigned long serialBaudRate = 115200;

  // Enable interrupts
  bool useInt1 = false;      // Set true to use INT1 for data ready
  bool useInt2 = false;      // Set true to use INT2 for events
};

// ==========================================
// ADXL345 SENSOR CLASS
// ==========================================

class ADXL345Sensor {
private:
  ADXL345Config config;

public:
  ADXL345Sensor() {}
  ADXL345Sensor(ADXL345Config cfg) : config(cfg) {}

  void begin();
  void loop();

  // Getters for configuration
  ADXL345Config& getConfig() { return config; }
  void setConfig(ADXL345Config cfg) { config = cfg; }
};

#endif // ADXL345_H
