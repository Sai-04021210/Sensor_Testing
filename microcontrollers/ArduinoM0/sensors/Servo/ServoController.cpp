#include "ServoController.h"

ServoController::ServoController() {
  lastMoveTime = 0;
  currentAngle = 90;
}

void ServoController::begin() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect
  }

  Serial.println("=== Arduino M0 Servo Controller ===");

  // Initialize servo
  servo.attach(SERVO_PIN);
  servo.write(currentAngle);

  randomSeed(analogRead(0));  // Seed random number generator
  Serial.println("READY");
}

int ServoController::generateRandomAngle() {
  return random(MIN_ANGLE, MAX_ANGLE + 1);
}

void ServoController::sendDataToSerial(int angle) {
  // Simple readable output
  Serial.print("Servo moved to: ");
  Serial.print(angle);
  Serial.println(" degrees");
}

void ServoController::loop() {
  unsigned long currentTime = millis();

  // Check if it's time to move the servo
  if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
    lastMoveTime = currentTime;

    // Generate random angle
    int newAngle = generateRandomAngle();

    // Move servo
    servo.write(newAngle);
    currentAngle = newAngle;

    // Send data to serial
    sendDataToSerial(newAngle);
  }

  delay(10);
}
