#include <Arduino.h>
#include <Servo.h>

// ==========================================
// SERVO RANDOM MOVEMENT ONLY
// ==========================================

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("\n=== Random Servo Movement ===\n");

  // Attach servos
  servo1.attach(9);
  servo2.attach(10);

  // Center servos
  servo1.write(90);
  servo2.write(90);

  randomSeed(analogRead(0));
  delay(1000);
}

void loop() {
  // Random speeds for 360° servos
  // 0-89 = rotate one direction
  // 90 = stop
  // 91-180 = rotate other direction

  int speed1 = random(0, 181);
  int speed2 = random(0, 181);

  Serial.print("Servo 1 speed: ");
  Serial.print(speed1);
  Serial.print(" | Servo 2 speed: ");
  Serial.println(speed2);

  servo1.write(speed1);
  servo2.write(speed2);

  // Random duration (1-3 seconds)
  int duration = random(1000, 3001);
  delay(duration);

  // Stop both servos
  Serial.println("Stop");
  servo1.write(90);
  servo2.write(90);
  delay(500);
}
