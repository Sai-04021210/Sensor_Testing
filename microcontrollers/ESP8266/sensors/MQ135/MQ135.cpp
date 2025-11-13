#include <Arduino.h>
#include "MQ135.h"

// ==========================================
// MQ-135 GAS SENSOR IMPLEMENTATION
// ==========================================

void MQ135Sensor::begin() {
  Serial.begin(config.serialBaudRate);
  delay(1000);

  pinMode(config.analogPin, INPUT);

  Serial.println("\n=== CO2 SENSOR (MQ-135) ===");
  Serial.println("Warming up (20s)...");
  for (int i = 20; i > 0; i--) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nReady!\n");
}

void MQ135Sensor::loop() {
  static unsigned long lastReadTime = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastReadTime >= config.readInterval) {
    // Array to store multiple readings
    int co2now[10];
    int co2raw = 0;
    int co2ppm = 0;
    int zzz = 0;

    // Sample CO2 multiple times for averaging
    for (int x = 0; x < config.samples; x++) {
      co2now[x] = analogRead(config.analogPin);
      delay(config.sampleDelay);
    }

    // Add all samples together
    for (int x = 0; x < config.samples; x++) {
      zzz = zzz + co2now[x];
    }

    // Calculate average
    co2raw = zzz / config.samples;

    // Calculate PPM (INVERTED for backwards sensor modules)
    // When ADC goes DOWN, CO2 should go UP
    co2ppm = config.co2Zero - co2raw;

    // Debug output
    Serial.print("Raw ADC: ");
    Serial.print(co2raw);
    Serial.print(" | Baseline: ");
    Serial.print(config.co2Zero);
    Serial.print(" | ");

    // Display CO2 in PPM
    Serial.print("AirQuality=");
    Serial.print(co2ppm);
    Serial.println(" PPM");

    lastReadTime = currentTime;
  }

  delay(10);
}
