#include "HW130Shield.h"

HW130Shield::HW130Shield() {
}

void HW130Shield::begin() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial
  }

  Serial.println("=== HW-130 Motor Shield Initialized ===");

  // Setup Motor A pins
  pinMode(MOTOR_A_DIR1, OUTPUT);
  pinMode(MOTOR_A_DIR2, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);

  // Setup Motor B pins
  pinMode(MOTOR_B_DIR1, OUTPUT);
  pinMode(MOTOR_B_DIR2, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);

  // Initialize servos
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);

  // Center servos
  servo1.write(90);
  servo2.write(90);

  // Stop all motors
  bothStop();

  Serial.println("Motors and Servos ready!");
}

void HW130Shield::setMotorA(MotorDirection dir, uint8_t speed) {
  switch (dir) {
    case FORWARD:
      digitalWrite(MOTOR_A_DIR1, HIGH);
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, speed);
      break;

    case BACKWARD:
      digitalWrite(MOTOR_A_DIR1, LOW);
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, speed);
      break;

    case BRAKE:
      digitalWrite(MOTOR_A_DIR1, HIGH);
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, 0);
      break;

    case RELEASE:
      digitalWrite(MOTOR_A_DIR1, LOW);
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, 0);
      break;
  }
}

void HW130Shield::setMotorB(MotorDirection dir, uint8_t speed) {
  switch (dir) {
    case FORWARD:
      digitalWrite(MOTOR_B_DIR1, HIGH);
      digitalWrite(MOTOR_B_DIR2, LOW);
      analogWrite(MOTOR_B_PWM, speed);
      break;

    case BACKWARD:
      digitalWrite(MOTOR_B_DIR1, LOW);
      digitalWrite(MOTOR_B_DIR2, HIGH);
      analogWrite(MOTOR_B_PWM, speed);
      break;

    case BRAKE:
      digitalWrite(MOTOR_B_DIR1, HIGH);
      digitalWrite(MOTOR_B_DIR2, HIGH);
      analogWrite(MOTOR_B_PWM, 0);
      break;

    case RELEASE:
      digitalWrite(MOTOR_B_DIR1, LOW);
      digitalWrite(MOTOR_B_DIR2, LOW);
      analogWrite(MOTOR_B_PWM, 0);
      break;
  }
}

// Motor A control functions
void HW130Shield::motorAForward(uint8_t speed) {
  setMotorA(FORWARD, speed);
  Serial.print("Motor A Forward @ ");
  Serial.println(speed);
}

void HW130Shield::motorABackward(uint8_t speed) {
  setMotorA(BACKWARD, speed);
  Serial.print("Motor A Backward @ ");
  Serial.println(speed);
}

void HW130Shield::motorAStop() {
  setMotorA(BRAKE, 0);
  Serial.println("Motor A Stopped");
}

// Motor B control functions
void HW130Shield::motorBForward(uint8_t speed) {
  setMotorB(FORWARD, speed);
  Serial.print("Motor B Forward @ ");
  Serial.println(speed);
}

void HW130Shield::motorBBackward(uint8_t speed) {
  setMotorB(BACKWARD, speed);
  Serial.print("Motor B Backward @ ");
  Serial.println(speed);
}

void HW130Shield::motorBStop() {
  setMotorB(BRAKE, 0);
  Serial.println("Motor B Stopped");
}

// Both motors control
void HW130Shield::bothForward(uint8_t speed) {
  setMotorA(FORWARD, speed);
  setMotorB(FORWARD, speed);
  Serial.print("Both Motors Forward @ ");
  Serial.println(speed);
}

void HW130Shield::bothBackward(uint8_t speed) {
  setMotorA(BACKWARD, speed);
  setMotorB(BACKWARD, speed);
  Serial.print("Both Motors Backward @ ");
  Serial.println(speed);
}

void HW130Shield::bothStop() {
  setMotorA(BRAKE, 0);
  setMotorB(BRAKE, 0);
  Serial.println("Both Motors Stopped");
}

// Turning functions
void HW130Shield::turnLeft(uint8_t speed) {
  setMotorA(BACKWARD, speed);
  setMotorB(FORWARD, speed);
  Serial.print("Turning Left @ ");
  Serial.println(speed);
}

void HW130Shield::turnRight(uint8_t speed) {
  setMotorA(FORWARD, speed);
  setMotorB(BACKWARD, speed);
  Serial.print("Turning Right @ ");
  Serial.println(speed);
}

// Servo control
void HW130Shield::setServo1(uint8_t angle) {
  servo1.write(angle);
  Serial.print("Servo 1: ");
  Serial.print(angle);
  Serial.println("°");
}

void HW130Shield::setServo2(uint8_t angle) {
  servo2.write(angle);
  Serial.print("Servo 2: ");
  Serial.print(angle);
  Serial.println("°");
}

// Demo functions
void HW130Shield::demoMotors() {
  Serial.println("\n=== Motor Demo ===");

  // Forward
  Serial.println("Forward...");
  bothForward(150);
  delay(2000);

  // Backward
  Serial.println("Backward...");
  bothBackward(150);
  delay(2000);

  // Turn left
  Serial.println("Turn Left...");
  turnLeft(150);
  delay(1000);

  // Turn right
  Serial.println("Turn Right...");
  turnRight(150);
  delay(1000);

  // Stop
  bothStop();
  delay(1000);
}

void HW130Shield::demoServos() {
  Serial.println("\n=== Servo Demo ===");

  // Sweep servo 1
  Serial.println("Sweeping Servo 1...");
  for (int angle = 0; angle <= 180; angle += 10) {
    setServo1(angle);
    delay(100);
  }
  delay(500);

  // Sweep servo 2
  Serial.println("Sweeping Servo 2...");
  for (int angle = 0; angle <= 180; angle += 10) {
    setServo2(angle);
    delay(100);
  }
  delay(500);

  // Both servos synchronized
  Serial.println("Both servos synchronized...");
  for (int angle = 0; angle <= 180; angle += 10) {
    setServo1(angle);
    setServo2(180 - angle);  // Mirror movement
    delay(100);
  }

  // Return to center
  setServo1(90);
  setServo2(90);
}

void HW130Shield::demoAll() {
  Serial.println("\n=== Full Demo: Motors + Servos ===");

  // Move forward with servo sweep
  Serial.println("Moving forward with servo sweep...");
  bothForward(150);
  for (int angle = 0; angle <= 180; angle += 10) {
    setServo1(angle);
    setServo2(180 - angle);
    delay(100);
  }
  bothStop();

  delay(1000);

  // Turn while moving servos
  Serial.println("Turning with servos...");
  turnRight(150);
  setServo1(45);
  setServo2(135);
  delay(2000);
  bothStop();

  // Center everything
  setServo1(90);
  setServo2(90);
  Serial.println("Demo complete!");
}
