#include <Arduino.h>
#include "ServoController.h"

// ==========================================
// ARDUINO M0 SERVO CONTROLLER
// ==========================================

ServoController servo;

void setup() {
  servo.begin();
}

void loop() {
  servo.loop();
}
