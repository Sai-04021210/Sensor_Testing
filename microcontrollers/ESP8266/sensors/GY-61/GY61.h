#ifndef GY61_H
#define GY61_H

#include <Arduino.h>

// ==========================================
// GY-61 (ADXL335) SENSOR CONFIGURATION
// ==========================================

struct GY61Config {
  // Pin configuration (Analog pins)
  int xPin = A0;             // X-axis output (only analog pin on ESP8266)
  // Note: ESP8266 has only ONE analog pin (A0)
  // We'll need to read X, Y, Z sequentially using a multiplexer
  // OR just read X-axis only

  // Voltage reference
  float vcc = 3.3;           // Supply voltage (3.3V)
  float zeroG = 1.65;        // 0g voltage (typically VCC/2)
  float sensitivity = 0.3;   // Sensitivity: 300mV/g

  // Timing
  unsigned long readInterval = 3000;  // Read every 3 seconds
  unsigned long serialBaudRate = 115200;

  // Calibration
  int numSamples = 10;       // Number of samples for averaging
};

// ==========================================
// GY-61 SENSOR CLASS
// ==========================================

class GY61Sensor {
private:
  GY61Config config;

  float readAxis(int pin);
  float analogToG(float voltage);

public:
  GY61Sensor() {}
  GY61Sensor(GY61Config cfg) : config(cfg) {}

  void begin();
  void loop();

  // Getters
  GY61Config& getConfig() { return config; }
  void setConfig(GY61Config cfg) { config = cfg; }
};

#endif // GY61_H
