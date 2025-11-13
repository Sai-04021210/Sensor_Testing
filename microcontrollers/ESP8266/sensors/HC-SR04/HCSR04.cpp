#include "HCSR04.h"

// ==========================================
// HELPER FUNCTIONS
// ==========================================

float HCSR04Sensor::measureDistance() {
  // Send 10μs pulse to trigger
  digitalWrite(config.trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(config.trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(config.trigPin, LOW);

  // Measure echo pulse duration
  unsigned long duration = pulseIn(config.echoPin, HIGH, config.timeout);

  // Calculate distance
  // Distance = (duration * speed of sound) / 2
  // Divide by 2 because sound travels to object and back
  float distance = (duration * config.soundSpeed) / 2.0;

  // Return 0 if timeout (no echo received)
  if (duration == 0) {
    return 0;
  }

  return distance;
}

void HCSR04Sensor::begin() {
  // Initialize serial communication
  Serial.begin(config.serialBaudRate);
  while (!Serial) { delay(10); }

  Serial.println("\n=================================");
  Serial.println("HC-SR04 Ultrasonic Sensor");
  Serial.println("=================================");

  // Initialize pins
  pinMode(config.trigPin, OUTPUT);
  pinMode(config.echoPin, INPUT);

  digitalWrite(config.trigPin, LOW);

  Serial.println("\nConfiguration:");
  Serial.print("  Trigger Pin: D");
  Serial.println(config.trigPin);
  Serial.print("  Echo Pin: D");
  Serial.println(config.echoPin);
  Serial.print("  Read Interval: ");
  Serial.print(config.readInterval);
  Serial.println("ms");
  Serial.print("  Max Range: ~");
  Serial.print((config.timeout * config.soundSpeed) / 2.0 / 100.0);
  Serial.println("m");
  Serial.println("=================================\n");

  delay(100);
}

void HCSR04Sensor::loop() {
  static unsigned long lastRead = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastRead >= config.readInterval) {
    lastRead = currentTime;

    // Take multiple measurements and average
    float sum = 0;
    int validReadings = 0;
    const int numReadings = 3;

    for (int i = 0; i < numReadings; i++) {
      float distance = measureDistance();
      if (distance > 0) {
        sum += distance;
        validReadings++;
      }
      delay(50);  // Small delay between readings
    }

    Serial.println("-------------------------------");
    Serial.print("Time: ");
    Serial.print(currentTime / 1000.0, 1);
    Serial.println("s");

    if (validReadings > 0) {
      float avgDistance = sum / validReadings;

      Serial.println("\nDistance Measurement:");
      Serial.print("  Distance: ");
      Serial.print(avgDistance, 1);
      Serial.print(" cm (");
      Serial.print(avgDistance / 100.0, 2);
      Serial.println(" m)");

      Serial.print("  Distance: ");
      Serial.print(avgDistance / 2.54, 1);
      Serial.println(" inches");

      Serial.print("  Valid Readings: ");
      Serial.print(validReadings);
      Serial.print("/");
      Serial.println(numReadings);

      // Range interpretation
      Serial.println("\nRange Status:");
      if (avgDistance < 2) {
        Serial.println("  ⚠️  Too close (< 2cm)");
      } else if (avgDistance < 20) {
        Serial.println("  🔴 Very Close");
      } else if (avgDistance < 50) {
        Serial.println("  🟡 Close");
      } else if (avgDistance < 100) {
        Serial.println("  🟢 Medium");
      } else if (avgDistance < 200) {
        Serial.println("  🔵 Far");
      } else {
        Serial.println("  🟣 Very Far");
      }

    } else {
      Serial.println("\n⚠️  No valid readings!");
      Serial.println("Check:");
      Serial.println("  - Object is within range (2cm - 4m)");
      Serial.println("  - Wiring connections");
      Serial.println("  - Object surface is not too soft/angled");
    }

    Serial.println("-------------------------------\n");
  }
}
