#include "GY61.h"

// ==========================================
// HELPER FUNCTIONS
// ==========================================

float GY61Sensor::readAxis(int pin) {
  // Read multiple samples and average
  long sum = 0;
  for (int i = 0; i < config.numSamples; i++) {
    sum += analogRead(pin);
    delay(10);
  }

  float average = sum / (float)config.numSamples;

  // Convert ADC value to voltage
  // ESP8266 ADC: 0-1023 = 0-1V (with voltage divider internally)
  // But actual range is 0-3.3V before divider
  float voltage = (average / 1023.0) * 3.3;

  return voltage;
}

float GY61Sensor::analogToG(float voltage) {
  // Convert voltage to g-force
  // g = (Vout - VzeroG) / Sensitivity
  float g = (voltage - config.zeroG) / config.sensitivity;
  return g;
}

void GY61Sensor::begin() {
  // Initialize serial communication
  Serial.begin(config.serialBaudRate);
  while (!Serial) { delay(10); }

  Serial.println("\n=================================");
  Serial.println("GY-61 (ADXL335) Accelerometer");
  Serial.println("=================================");

  Serial.println("\nConfiguration:");
  Serial.print("  X-axis Pin: A0");
  Serial.println("\n  Note: ESP8266 has only 1 analog pin");
  Serial.println("  Reading X-axis only");
  Serial.print("  VCC: ");
  Serial.print(config.vcc);
  Serial.println("V");
  Serial.print("  Zero-G Voltage: ");
  Serial.print(config.zeroG);
  Serial.println("V");
  Serial.print("  Sensitivity: ");
  Serial.print(config.sensitivity * 1000);
  Serial.println(" mV/g");
  Serial.print("  Read Interval: ");
  Serial.print(config.readInterval);
  Serial.println("ms");
  Serial.println("=================================\n");

  delay(100);
}

void GY61Sensor::loop() {
  static unsigned long lastRead = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastRead >= config.readInterval) {
    lastRead = currentTime;

    // Read X-axis
    float xVoltage = readAxis(config.xPin);
    float xG = analogToG(xVoltage);

    Serial.println("-------------------------------");
    Serial.print("Time: ");
    Serial.print(currentTime / 1000.0, 1);
    Serial.println("s");

    Serial.println("\nX-Axis Acceleration:");
    Serial.print("  Voltage: ");
    Serial.print(xVoltage, 3);
    Serial.println(" V");
    Serial.print("  G-Force: ");
    Serial.print(xG, 3);
    Serial.println(" g");

    // Interpretation
    Serial.println("\nOrientation:");
    if (xG > 0.8) {
      Serial.println("  Tilted RIGHT");
    } else if (xG < -0.8) {
      Serial.println("  Tilted LEFT");
    } else {
      Serial.println("  Level (X-axis)");
    }

    Serial.println("\nNote:");
    Serial.println("  ESP8266 has only 1 analog pin (A0)");
    Serial.println("  Connect X-out to A0 for X-axis reading");
    Serial.println("  For Y/Z: swap connections manually");
    Serial.println("  or use an analog multiplexer");

    Serial.println("-------------------------------\n");
  }
}
