#include <Arduino.h>
#include "GY61.h"

// ==========================================
// GY-61 (ADXL335) ACCELEROMETER - USING MODULAR LIBRARY
// ==========================================

// Create GY-61 sensor instance with default config
GY61Sensor sensor;

void setup() {
  sensor.begin();
}

void loop() {
  sensor.loop();
}
