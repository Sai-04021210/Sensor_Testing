#include <Arduino.h>
#include "DHT11.h"

// ==========================================
// DHT11 TEMPERATURE & HUMIDITY SENSOR
// ==========================================

void DHT11Sensor::begin() {
  Serial.begin(config.serialBaudRate);
  delay(1000);

  pinMode(config.dataPin, INPUT);

  Serial.println("\n=== DHT11 TEMPERATURE & HUMIDITY SENSOR ===");
  Serial.println("Initializing...\n");
  delay(2000);
}

void DHT11Sensor::loop() {
  static unsigned long lastReadTime = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastReadTime >= config.readInterval) {
    // DHT11 reading logic would go here
    // For now, this is a placeholder structure

    Serial.println("Temperature: -- °C");
    Serial.println("Humidity: -- %");
    Serial.println("---");

    lastReadTime = currentTime;
  }

  delay(10);
}
