#ifndef HCSR04_H
#define HCSR04_H

#include <Arduino.h>

// ==========================================
// HC-SR04 ULTRASONIC SENSOR CONFIGURATION
// ==========================================

struct HCSR04Config {
  // Pin configuration
  int trigPin = D6;          // Trigger pin (GPIO12)
  int echoPin = D7;          // Echo pin (GPIO13)

  // Timing
  unsigned long readInterval = 3000;  // Read every 3 seconds
  unsigned long serialBaudRate = 115200;

  // Timeout
  unsigned long timeout = 30000;  // 30ms timeout (max ~5m range)

  // Speed of sound (cm/microsecond)
  float soundSpeed = 0.0343;  // 343 m/s = 0.0343 cm/μs at 20°C
};

// ==========================================
// HC-SR04 SENSOR CLASS
// ==========================================

class HCSR04Sensor {
private:
  HCSR04Config config;

  float measureDistance();

public:
  HCSR04Sensor() {}
  HCSR04Sensor(HCSR04Config cfg) : config(cfg) {}

  void begin();
  void loop();

  // Getters
  HCSR04Config& getConfig() { return config; }
  void setConfig(HCSR04Config cfg) { config = cfg; }
};

#endif // HCSR04_H
