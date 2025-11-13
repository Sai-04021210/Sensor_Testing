#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

// ==========================================
// PIR MOTION SENSOR CONFIGURATION
// ==========================================

struct PIRConfig {
  // Pin configuration
  int pirPin = D5;           // PIR sensor output pin (GPIO14)

  // Timing
  unsigned long readInterval = 500;  // Check every 500ms
  unsigned long serialBaudRate = 115200;

  // Debouncing
  unsigned long debounceDelay = 200;  // Ignore changes within 200ms

  // Calibration time
  unsigned long calibrationTime = 30000;  // 30 seconds warm-up
};

// ==========================================
// PIR SENSOR CLASS
// ==========================================

class PIRSensor {
private:
  PIRConfig config;
  bool motionDetected;
  bool lastState;
  unsigned long lastMotionTime;
  unsigned long lastChangeTime;
  unsigned long motionCount;
  bool calibrated;

public:
  PIRSensor() : motionDetected(false), lastState(false),
                lastMotionTime(0), lastChangeTime(0),
                motionCount(0), calibrated(false) {}

  PIRSensor(PIRConfig cfg) : config(cfg), motionDetected(false),
                             lastState(false), lastMotionTime(0),
                             lastChangeTime(0), motionCount(0),
                             calibrated(false) {}

  void begin();
  void loop();

  // Getters
  PIRConfig& getConfig() { return config; }
  void setConfig(PIRConfig cfg) { config = cfg; }
  bool isMotionDetected() { return motionDetected; }
  unsigned long getMotionCount() { return motionCount; }
};

#endif // PIR_H
