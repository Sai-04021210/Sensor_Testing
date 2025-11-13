#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

// Servo settings
#define SERVO_PIN 9
#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define MOVE_INTERVAL 2000  // Move every 2 seconds

class ServoController {
private:
  Servo servo;
  unsigned long lastMoveTime;
  int currentAngle;

  int generateRandomAngle();
  void sendDataToSerial(int angle);

public:
  ServoController();
  void begin();
  void loop();
};

#endif
