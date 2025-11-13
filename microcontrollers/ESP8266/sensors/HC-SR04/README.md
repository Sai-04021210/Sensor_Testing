# HC-SR04 Ultrasonic Distance Sensor with ESP8266

## Hardware Setup

### Wiring
Connect the HC-SR04 to ESP8266 NodeMCU:

| HC-SR04 Pin | ESP8266 Pin | Description |
|-------------|-------------|-------------|
| VCC         | 5V or 3.3V  | Power supply |
| GND         | GND         | Ground |
| Trig        | D6 (GPIO12) | Trigger pin (send pulse) |
| Echo        | D7 (GPIO13) | Echo pin (receive pulse) |

**Note:** HC-SR04 works with both 3.3V and 5V. Echo output is 5V, but ESP8266 is generally 5V tolerant on GPIO pins.

## Build and Upload

```bash
pio run -e esp8266_hcsr04 -t upload
```

## Monitor Output

```bash
pio device monitor -e esp8266_hcsr04 -b 115200
```

## What You'll See

The sensor displays:
- **Distance** in cm, meters, and inches
- **Range status** (Very Close, Close, Medium, Far, Very Far)
- **Valid readings count** (averages 3 measurements)
- Updates every 3 seconds

## Configuration

Adjust settings in `HCSR04.h`:

```cpp
struct HCSR04Config {
  int trigPin = D6;                      // Trigger pin
  int echoPin = D7;                      // Echo pin
  unsigned long readInterval = 3000;     // 3 seconds
  unsigned long timeout = 30000;         // 30ms timeout (~5m max)
  float soundSpeed = 0.0343;             // cm/μs at 20°C
};
```

## How It Works

1. Sensor sends 8x 40kHz ultrasonic pulses
2. Pulses bounce off object and return
3. Time measured = distance calculation
4. **Distance = (time × speed of sound) / 2**

## Troubleshooting

### No Valid Readings
- Check wiring (Trig → D6, Echo → D7)
- Ensure object is within range (2cm - 4m)
- Object surface should be flat/hard (not soft/angled)
- Check power supply is stable

### Inaccurate Readings
- Temperature affects speed of sound
- Adjust `soundSpeed` in config (increases ~0.6m/s per °C)
- Avoid very small or soft objects
- Keep sensor perpendicular to surface

### Reads Maximum Distance
- No object detected or object too far
- Surface absorbs sound (carpet, foam, fabric)
- Object at an angle (sound reflects away)

## Specifications

- **Range:** 2cm to 4m (optimal: 2cm - 3m)
- **Accuracy:** ±3mm
- **Angle:** 15° cone
- **Frequency:** 40kHz
- **Power:** 5V or 3.3V
- **Current:** 15mA
