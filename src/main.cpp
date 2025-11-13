#include <Arduino.h>
#include "HCSR04.h"

// ==========================================
// HC-SR04 ULTRASONIC SENSOR - USING MODULAR LIBRARY
// ==========================================

// Create HC-SR04 sensor instance with default config
HCSR04Sensor sensor;

void setup() {
  sensor.begin();
}

void loop() {
  sensor.loop();
}
