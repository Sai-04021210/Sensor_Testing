#include <Arduino.h>
#include "ADXL345.h"

// ==========================================
// ADXL345 ACCELEROMETER SENSOR - USING MODULAR LIBRARY
// ==========================================

// Create ADXL345 sensor instance with default config
ADXL345Sensor sensor;

void setup() {
  sensor.begin();
}

void loop() {
  sensor.loop();
}
