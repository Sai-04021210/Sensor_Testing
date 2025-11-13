#include "PIR.h"

// ==========================================
// HELPER FUNCTIONS
// ==========================================

void PIRSensor::begin() {
  // Initialize serial communication
  Serial.begin(config.serialBaudRate);
  while (!Serial) { delay(10); }

  Serial.println("\n=================================");
  Serial.println("PIR Motion Sensor");
  Serial.println("=================================");

  // Initialize PIR pin
  pinMode(config.pirPin, INPUT);

  Serial.println("\nConfiguration:");
  Serial.print("  PIR Pin: D");
  Serial.println(config.pirPin);
  Serial.print("  Check Interval: ");
  Serial.print(config.readInterval);
  Serial.println("ms");
  Serial.print("  Debounce Delay: ");
  Serial.print(config.debounceDelay);
  Serial.println("ms");
  Serial.println("=================================");

  Serial.println("\n⏳ Calibrating sensor...");
  Serial.print("Please wait ");
  Serial.print(config.calibrationTime / 1000);
  Serial.println(" seconds");
  Serial.println("(Do not move in front of sensor)");

  unsigned long startTime = millis();
  int progress = 0;

  while (millis() - startTime < config.calibrationTime) {
    int newProgress = ((millis() - startTime) * 100) / config.calibrationTime;
    if (newProgress > progress && newProgress % 10 == 0) {
      progress = newProgress;
      Serial.print("  ");
      Serial.print(progress);
      Serial.println("%");
    }
    delay(100);
  }

  calibrated = true;
  Serial.println("\n✅ Calibration complete!");
  Serial.println("Sensor ready for motion detection");
  Serial.println("=================================\n");

  delay(100);
}

void PIRSensor::loop() {
  static unsigned long lastRead = 0;
  unsigned long currentTime = millis();

  if (!calibrated) {
    return;
  }

  if (currentTime - lastRead >= config.readInterval) {
    lastRead = currentTime;

    // Read PIR sensor
    bool currentState = digitalRead(config.pirPin);

    // Debouncing - only process if enough time has passed since last change
    if (currentState != lastState &&
        (currentTime - lastChangeTime) >= config.debounceDelay) {

      lastChangeTime = currentTime;
      lastState = currentState;

      if (currentState == HIGH) {
        // Motion detected
        motionDetected = true;
        motionCount++;
        lastMotionTime = currentTime;

        Serial.println("==============================");
        Serial.print("🚨 MOTION DETECTED! #");
        Serial.println(motionCount);
        Serial.print("Time: ");
        Serial.print(currentTime / 1000.0, 1);
        Serial.println("s");
        Serial.println("==============================\n");

      } else {
        // Motion ended
        motionDetected = false;
        unsigned long motionDuration = currentTime - lastMotionTime;

        Serial.println("------------------------------");
        Serial.println("✅ Motion ended");
        Serial.print("Duration: ");
        Serial.print(motionDuration / 1000.0, 1);
        Serial.println("s");
        Serial.println("------------------------------\n");
      }
    }

    // Periodic status update (every 30 seconds when no motion)
    static unsigned long lastStatusUpdate = 0;
    if (!motionDetected && (currentTime - lastStatusUpdate) >= 30000) {
      lastStatusUpdate = currentTime;

      Serial.println("------------------------------");
      Serial.println("📊 Status Update");
      Serial.print("Time: ");
      Serial.print(currentTime / 1000.0, 1);
      Serial.println("s");
      Serial.print("Total detections: ");
      Serial.println(motionCount);

      if (motionCount > 0) {
        unsigned long timeSinceLastMotion = currentTime - lastMotionTime;
        Serial.print("Last motion: ");
        Serial.print(timeSinceLastMotion / 1000.0, 0);
        Serial.println("s ago");
      }

      Serial.println("Status: Monitoring...");
      Serial.println("------------------------------\n");
    }
  }
}
