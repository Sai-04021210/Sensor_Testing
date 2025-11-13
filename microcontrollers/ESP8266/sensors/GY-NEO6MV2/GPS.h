#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

// ==========================================
// GY-NEO6MV2 GPS MODULE CONFIGURATION
// ==========================================

struct GPSConfig {
  // Pin configuration (Hardware Serial1: RX=GPIO13/D7, TX is TX1)
  // Note: ESP8266 Serial1 is TX only by default
  // We'll use D7 (GPIO13) for RX from GPS TX

  // Timing
  unsigned long readInterval = 3000;  // Read every 3000ms (3 seconds)
  unsigned long serialBaudRate = 115200;
  unsigned long gpsBaudRate = 9600;   // NEO6M default baud rate
};

// ==========================================
// GPS SENSOR CLASS
// ==========================================

class GPSSensor {
private:
  GPSConfig config;
  TinyGPSPlus gps;
  HardwareSerial* gpsSerial;

public:
  GPSSensor() {
    gpsSerial = nullptr;
  }

  GPSSensor(GPSConfig cfg) : config(cfg) {
    gpsSerial = nullptr;
  }

  void begin();
  void loop();

  // Getters for configuration
  GPSConfig& getConfig() { return config; }
  void setConfig(GPSConfig cfg) { config = cfg; }

  // Get GPS object
  TinyGPSPlus& getGPS() { return gps; }
};

#endif // GPS_H
