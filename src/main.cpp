#include <Arduino.h>
#include "MQ135.h"

// ==========================================
// MQ-135 GAS SENSOR - USING MODULAR LIBRARY
// ==========================================

// Create MQ135 sensor instance with default config
MQ135Sensor sensor;

void setup() {
  sensor.begin();
}

void loop() {
  sensor.loop();
}
