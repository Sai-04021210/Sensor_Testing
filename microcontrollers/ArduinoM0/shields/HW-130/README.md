# Arduino M0 + HW-130 Motor Shield

Control 2 DC motors and 2 servo motors using the HW-130 motor shield.

## Hardware Setup

**HW-130 Motor Shield on Arduino M0:**
- 2x DC Motors (Motor A & Motor B)
- 2x Servo Motors (Servo 1 & Servo 2)

## Pin Configuration

### Motors
- **Motor A**: DIR1=12, DIR2=13, PWM=3
- **Motor B**: DIR1=11, DIR2=8, PWM=5

### Servos
- **Servo 1**: Pin 9
- **Servo 2**: Pin 10

## Upload & Run

```bash
# Upload to Arduino M0
pio run -e arduinoM0_hw130 -t upload

# Monitor serial output
pio device monitor -b 115200
```

## Available Functions

### Motor Control
```cpp
shield.motorAForward(speed);      // Motor A forward (0-255)
shield.motorABackward(speed);     // Motor A backward
shield.motorAStop();               // Stop Motor A

shield.motorBForward(speed);      // Motor B forward
shield.motorBBackward(speed);     // Motor B backward
shield.motorBStop();               // Stop Motor B

shield.bothForward(speed);        // Both motors forward
shield.bothBackward(speed);       // Both motors backward
shield.bothStop();                 // Stop all motors

shield.turnLeft(speed);            // Turn left (differential)
shield.turnRight(speed);           // Turn right (differential)
```

### Servo Control
```cpp
shield.setServo1(angle);          // Servo 1: 0-180°
shield.setServo2(angle);          // Servo 2: 0-180°
```

### Demo Functions
```cpp
shield.demoMotors();              // Demo motor movements
shield.demoServos();               // Demo servo movements
shield.demoAll();                  // Combined demo
```

## Example Output

```
=== HW-130 Motor Shield Initialized ===
Motors and Servos ready!

=== Full Demo: Motors + Servos ===
Moving forward with servo sweep...
Both Motors Forward @ 150
Servo 1: 0°
Servo 2: 180°
...
Turning with servos...
Turning Right @ 150
Demo complete!
```
