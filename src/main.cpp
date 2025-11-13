#include <Arduino.h>
#include "PIR.h"

// ==========================================
// PIR MOTION SENSOR - USING MODULAR LIBRARY
// ==========================================

// Create PIR sensor instance with default config
PIRSensor sensor;

void setup() {
  sensor.begin();
}

void loop() {
  sensor.loop();
}
