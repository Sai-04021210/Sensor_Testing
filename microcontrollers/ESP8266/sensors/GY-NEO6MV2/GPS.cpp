#include "GPS.h"

// ==========================================
// HELPER FUNCTIONS
// ==========================================

void GPSSensor::begin() {
  // Initialize serial communication
  Serial.begin(config.serialBaudRate);
  while (!Serial) { delay(10); }

  Serial.println("\n=================================");
  Serial.println("GY-NEO6MV2 GPS Module");
  Serial.println("=================================");

  // Initialize GPS serial (use hardware serial Serial1 on ESP8266)
  // Swap Serial pins: RX to GPIO13 (D7), TX to GPIO15 (D8)
  Serial1.begin(config.gpsBaudRate);
  gpsSerial = &Serial1;

  Serial.println("\nConfiguration:");
  Serial.println("  Using Hardware Serial (GPIO2/D4 = TX)");
  Serial.println("  Connect GPS RX -> ESP8266 D4 (GPIO2)");
  Serial.println("  Connect GPS TX -> ESP8266 RX (not used in Serial1)");
  Serial.print("  GPS Baud Rate: ");
  Serial.println(config.gpsBaudRate);
  Serial.print("  Read Interval: ");
  Serial.print(config.readInterval);
  Serial.println("ms");
  Serial.println("=================================");
  Serial.println("Waiting for GPS signal...");
  Serial.println("(This may take a few minutes outdoors)");
  Serial.println("=================================\n");

  delay(100);
}

void GPSSensor::loop() {
  static unsigned long lastRead = 0;
  unsigned long currentTime = millis();

  // Read data from GPS
  while (gpsSerial->available() > 0) {
    gps.encode(gpsSerial->read());
  }

  // Display GPS data at specified interval
  if (currentTime - lastRead >= config.readInterval) {
    lastRead = currentTime;

    Serial.println("-------------------------------");
    Serial.print("Time: ");
    Serial.print(currentTime / 1000.0, 1);
    Serial.println("s");

    // Check if GPS has valid location
    if (gps.location.isValid()) {
      Serial.println("\n*** GPS LOCKED ***");

      // Location
      Serial.println("\nLocation:");
      Serial.print("  Latitude:  ");
      Serial.print(gps.location.lat(), 6);
      Serial.println("°");
      Serial.print("  Longitude: ");
      Serial.print(gps.location.lng(), 6);
      Serial.println("°");

      // Altitude
      if (gps.altitude.isValid()) {
        Serial.print("  Altitude:  ");
        Serial.print(gps.altitude.meters());
        Serial.println(" m");
      }

      // Speed
      if (gps.speed.isValid()) {
        Serial.print("  Speed:     ");
        Serial.print(gps.speed.kmph());
        Serial.println(" km/h");
      }

      // Course
      if (gps.course.isValid()) {
        Serial.print("  Course:    ");
        Serial.print(gps.course.deg());
        Serial.println("°");
      }

      // Date & Time (UTC)
      if (gps.date.isValid() && gps.time.isValid()) {
        Serial.println("\nDate & Time (UTC):");
        Serial.print("  ");
        if (gps.date.month() < 10) Serial.print("0");
        Serial.print(gps.date.month());
        Serial.print("/");
        if (gps.date.day() < 10) Serial.print("0");
        Serial.print(gps.date.day());
        Serial.print("/");
        Serial.print(gps.date.year());
        Serial.print(" ");
        if (gps.time.hour() < 10) Serial.print("0");
        Serial.print(gps.time.hour());
        Serial.print(":");
        if (gps.time.minute() < 10) Serial.print("0");
        Serial.print(gps.time.minute());
        Serial.print(":");
        if (gps.time.second() < 10) Serial.print("0");
        Serial.println(gps.time.second());
      }

      // Satellites
      if (gps.satellites.isValid()) {
        Serial.print("\nSatellites: ");
        Serial.println(gps.satellites.value());
      }

      // HDOP (Horizontal Dilution of Precision)
      if (gps.hdop.isValid()) {
        Serial.print("HDOP:       ");
        Serial.println(gps.hdop.hdop());
      }

    } else {
      Serial.println("\n*** NO GPS SIGNAL ***");
      Serial.println("Searching for satellites...");

      if (gps.satellites.isValid()) {
        Serial.print("Satellites in view: ");
        Serial.println(gps.satellites.value());
      } else {
        Serial.println("No satellite data yet");
      }

      Serial.println("\nTips:");
      Serial.println("- Make sure GPS module is outdoors");
      Serial.println("- Clear view of the sky");
      Serial.println("- May take 1-5 minutes for first fix");
    }

    // Characters processed
    Serial.print("\nChars processed: ");
    Serial.print(gps.charsProcessed());
    Serial.print(" | Failed checksum: ");
    Serial.println(gps.failedChecksum());

    Serial.println("-------------------------------\n");
  }
}
