#ifndef HW130_SHIELD_H
#define HW130_SHIELD_H

#include <Arduino.h>
#include <Servo.h>

// HW-130 Motor Shield Pin Definitions (M1 and M2 Terminals)
// Standard L298N configuration
// M1 Motor
#define MOTOR_A_DIR1 7     // IN1
#define MOTOR_A_DIR2 6     // IN2
#define MOTOR_A_PWM 5      // ENA (PWM)

// M2 Motor
#define MOTOR_B_DIR1 4     // IN3
#define MOTOR_B_DIR2 3     // IN4
#define MOTOR_B_PWM 2      // ENB (PWM)

// Servo connections
#define SERVO_1_PIN 9      // Servo 1
#define SERVO_2_PIN 10     // Servo 2

// Motor direction constants
enum MotorDirection {
  FORWARD,
  BACKWARD,
  BRAKE,
  RELEASE
};

class HW130Shield {
private:
  Servo servo1;
  Servo servo2;

  void setMotorA(MotorDirection dir, uint8_t speed);
  void setMotorB(MotorDirection dir, uint8_t speed);

public:
  HW130Shield();
  void begin();

  // Motor control
  void motorAForward(uint8_t speed);
  void motorABackward(uint8_t speed);
  void motorAStop();

  void motorBForward(uint8_t speed);
  void motorBBackward(uint8_t speed);
  void motorBStop();

  void bothForward(uint8_t speed);
  void bothBackward(uint8_t speed);
  void bothStop();

  void turnLeft(uint8_t speed);
  void turnRight(uint8_t speed);

  // Servo control
  void setServo1(uint8_t angle);
  void setServo2(uint8_t angle);

  // Demo modes
  void demoMotors();
  void demoServos();
  void demoAll();
};

#endif
