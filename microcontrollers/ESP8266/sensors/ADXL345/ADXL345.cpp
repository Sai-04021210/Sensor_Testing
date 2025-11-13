#include "ADXL345.h"
#include <Wire.h>

// ==========================================
// ADXL345 REGISTER MAP
// ==========================================
#define ADXL345_POWER_CTL    0x2D
#define ADXL345_DATA_FORMAT  0x31
#define ADXL345_BW_RATE      0x2C
#define ADXL345_DATAX0       0x32
#define ADXL345_DATAX1       0x33
#define ADXL345_DATAY0       0x34
#define ADXL345_DATAY1       0x35
#define ADXL345_DATAZ0       0x36
#define ADXL345_DATAZ1       0x37
#define ADXL345_DEVID        0x00

// ==========================================
// HELPER FUNCTIONS
// ==========================================

void ADXL345Sensor::begin() {
  // Initialize serial communication
  Serial.begin(config.serialBaudRate);
  while (!Serial) { delay(10); }

  Serial.println("\n=================================");
  Serial.println("ADXL345 Accelerometer Sensor");
  Serial.println("=================================");

  // If using CS pin for I2C mode, set it HIGH
  if (config.csPin >= 0) {
    pinMode(config.csPin, OUTPUT);
    digitalWrite(config.csPin, HIGH);
    Serial.println("CS pin set HIGH for I2C mode");
  }

  // Initialize I2C
  Wire.begin(config.sdaPin, config.sclPin);
  delay(100);

  // Check device ID
  Wire.beginTransmission(config.i2cAddress);
  Wire.write(ADXL345_DEVID);
  Wire.endTransmission();

  Wire.requestFrom(config.i2cAddress, 1);
  if (Wire.available()) {
    uint8_t devid = Wire.read();
    Serial.print("Device ID: 0x");
    Serial.println(devid, HEX);

    if (devid != 0xE5) {
      Serial.println("ERROR: ADXL345 not found!");
      Serial.println("Check connections and I2C address");
      return;
    }
  } else {
    Serial.println("ERROR: Cannot read from ADXL345!");
    Serial.println("Check I2C connections");
    return;
  }

  // Set data rate
  Wire.beginTransmission(config.i2cAddress);
  Wire.write(ADXL345_BW_RATE);
  Wire.write(config.dataRate);
  Wire.endTransmission();

  // Set range
  uint8_t format = 0x00;
  switch (config.range) {
    case 2:  format = 0x00; break;
    case 4:  format = 0x01; break;
    case 8:  format = 0x02; break;
    case 16: format = 0x03; break;
    default: format = 0x00; break;
  }

  Wire.beginTransmission(config.i2cAddress);
  Wire.write(ADXL345_DATA_FORMAT);
  Wire.write(format);
  Wire.endTransmission();

  // Enable measurement mode
  Wire.beginTransmission(config.i2cAddress);
  Wire.write(ADXL345_POWER_CTL);
  Wire.write(0x08);  // Measurement mode
  Wire.endTransmission();

  Serial.println("\nConfiguration:");
  Serial.print("  I2C Address: 0x");
  Serial.println(config.i2cAddress, HEX);
  Serial.print("  SDA Pin: D");
  Serial.println(config.sdaPin);
  Serial.print("  SCL Pin: D");
  Serial.println(config.sclPin);
  Serial.print("  Range: ±");
  Serial.print(config.range);
  Serial.println("g");
  Serial.print("  Read Interval: ");
  Serial.print(config.readInterval);
  Serial.println("ms");
  Serial.println("=================================\n");

  delay(100);
}

void ADXL345Sensor::loop() {
  static unsigned long lastRead = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastRead >= config.readInterval) {
    lastRead = currentTime;

    // Read all 6 bytes (X, Y, Z data)
    Wire.beginTransmission(config.i2cAddress);
    Wire.write(ADXL345_DATAX0);
    Wire.endTransmission();

    Wire.requestFrom(config.i2cAddress, 6);

    if (Wire.available() >= 6) {
      // Read raw data
      int16_t x = Wire.read();
      x |= ((int16_t)Wire.read()) << 8;

      int16_t y = Wire.read();
      y |= ((int16_t)Wire.read()) << 8;

      int16_t z = Wire.read();
      z |= ((int16_t)Wire.read()) << 8;

      // Convert to g values (ADXL345 uses ~256 LSB/g in ±2g mode)
      float scale = 256.0 / config.range;
      float x_g = x / scale;
      float y_g = y / scale;
      float z_g = z / scale;

      // Calculate magnitude
      float magnitude = sqrt(x_g*x_g + y_g*y_g + z_g*z_g);

      // Display readings
      Serial.println("-------------------------------");
      Serial.print("Time: ");
      Serial.print(currentTime / 1000.0, 1);
      Serial.println("s");

      Serial.println("\nAcceleration (g):");
      Serial.print("  X: ");
      Serial.print(x_g, 3);
      Serial.print(" g  (raw: ");
      Serial.print(x);
      Serial.println(")");

      Serial.print("  Y: ");
      Serial.print(y_g, 3);
      Serial.print(" g  (raw: ");
      Serial.print(y);
      Serial.println(")");

      Serial.print("  Z: ");
      Serial.print(z_g, 3);
      Serial.print(" g  (raw: ");
      Serial.print(z);
      Serial.println(")");

      Serial.print("\nMagnitude: ");
      Serial.print(magnitude, 3);
      Serial.println(" g");

      Serial.println("-------------------------------\n");
    } else {
      Serial.println("ERROR: Failed to read accelerometer data");
    }
  }
}
