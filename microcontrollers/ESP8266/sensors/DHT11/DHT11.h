#ifndef DHT11_H
#define DHT11_H

#include <Arduino.h>

// ==========================================
// DHT11 SENSOR CONFIGURATION
// ==========================================

struct DHT11Config {
  // Pin configuration
  int dataPin = D4;          // Data pin (GPIO2)

  // Timing
  unsigned long readInterval = 2000;  // Read every 2 seconds (DHT11 limitation)
  unsigned long serialBaudRate = 115200;
};

// ==========================================
// DHT11 SENSOR CLASS
// ==========================================

class DHT11Sensor {
private:
  DHT11Config config;

public:
  DHT11Sensor() {}
  DHT11Sensor(DHT11Config cfg) : config(cfg) {}

  void begin();
  void loop();

  // Getters for configuration
  DHT11Config& getConfig() { return config; }
  void setConfig(DHT11Config cfg) { config = cfg; }
};

#endif // DHT11_H
