#ifndef MQ135_H
#define MQ135_H

#include <Arduino.h>

// ==========================================
// MQ-135 SENSOR CONFIGURATION
// ==========================================

struct MQ135Config {
  // Pin configuration
  int analogPin = A0;        // Analog output pin
  int digitalPin = D1;       // Digital output pin (GPIO5)

  // Timing
  unsigned long readInterval = 2000;  // Read every 2 seconds
  unsigned long serialBaudRate = 115200;

  // Simplified calibration (INVERTED for backwards modules)
  int co2Zero = 846;         // Calibrated baseline: ADC value at ~400 PPM + 400 (adjust this!)
  int samples = 10;          // Number of samples to average
  int sampleDelay = 200;     // Delay between samples in ms
};

// ==========================================
// MQ-135 SENSOR CLASS
// ==========================================

class MQ135Sensor {
private:
  MQ135Config config;

public:
  MQ135Sensor() {}
  MQ135Sensor(MQ135Config cfg) : config(cfg) {}

  void begin();
  void loop();

  // Getters for configuration
  MQ135Config& getConfig() { return config; }
  void setConfig(MQ135Config cfg) { config = cfg; }
};

#endif // MQ135_H
