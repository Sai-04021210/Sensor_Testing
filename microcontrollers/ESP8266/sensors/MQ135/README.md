# MQ-135 Gas Sensor (CO2) for ESP8266

Air quality sensor that detects CO2, ammonia, benzene, alcohol, smoke, and other gases.

## Quick Start - Just Upload and Run

### 1. Connect Your Hardware
```
MQ-135 Sensor -> ESP8266
VCC           -> VIN (5V) or 3.3V
GND           -> GND
A0 (Analog)   -> A0
D0 (Digital)  -> D1 (GPIO5)
```

### 2. Upload the Code
```bash
pio run -e esp8266_mq135 -t upload
```

### 3. Monitor the Output
```bash
pio device monitor -e esp8266_mq135
```

That's it! You'll see:
```
=== CO2 SENSOR (MQ-135) ===
Warming up (20s)...
....................
Ready!

Raw ADC: 446 | Baseline: 846 | AirQuality=400 PPM
```

### What You'll See:
- **Normal air**: ~400 PPM
- **Blow on sensor**: Values increase to 1000-4000 PPM
- **Stuffy room**: 600-1000 PPM
- **Poor ventilation**: 2000+ PPM

## Features
- Simple direct ADC reading (no complex formulas)
- Averaging over 10 samples for stability
- Works with inverted sensor modules
- Easy calibration
- Real-time PPM display

## Configuration

Edit `MQ135.h` to adjust:
- `analogPin` - Analog input pin (default: A0)
- `digitalPin` - Digital threshold pin (default: D1)
- `readInterval` - Reading frequency in ms (default: 2000)
- `rl` - Load resistance in kΩ (default: 10.0)
- `r0` - Clean air resistance (default: 10.0 - **CALIBRATE THIS!**)
- `voltageRef` - Reference voltage (default: 3.3V)

## Library Structure

This folder contains the **reusable MQ135 library**:
- `MQ135.h` - Header file (class definition and configuration)
- `MQ135.cpp` - Implementation file (sensor logic)
- `README.md` - This documentation

Your **application code** goes in `src/main.cpp` at the project root.

## Usage

### In your `src/main.cpp`:
```cpp
#include <Arduino.h>
#include "MQ135.h"

MQ135Sensor sensor;

void setup() {
  sensor.begin();  // Initializes sensor with 20s warmup
}

void loop() {
  sensor.loop();  // Reads and prints CO2 PPM
}
```

### Custom Configuration
```cpp
MQ135Config config;
config.r0 = 12.5;  // Your calibrated value
config.readInterval = 1000;  // Read every second

MQ135Sensor sensor(config);
```

## Calibration (Optional)

If your readings seem off, adjust the baseline in `MQ135.h`:

1. Note the **Raw ADC** value in fresh outdoor air
2. Expected outdoor air = ~400 PPM
3. Calculate: `co2Zero = Raw_ADC + 400`
4. Update `co2Zero` in `MQ135.h`
5. Re-upload: `pio run -e esp8266_mq135 -t upload`

Example:
```cpp
// If Raw ADC shows 446 in outdoor air:
int co2Zero = 846;  // 446 + 400 = 846
```

## Troubleshooting

### Values Going Down When You Blow?
Your sensor module might not be inverted. Edit `MQ135.cpp` and change:
```cpp
co2ppm = config.co2Zero - co2raw;  // Inverted
```
to:
```cpp
co2ppm = co2raw - config.co2Zero;  // Standard
```

### Negative or Crazy Values?
Adjust `co2Zero` in `MQ135.h` - see Calibration section above.

## CO2 Level Reference
- **400-600 PPM**: Fresh outdoor air
- **600-1000 PPM**: Acceptable indoor air
- **1000-2000 PPM**: Stuffy, drowsiness possible
- **2000+ PPM**: Poor ventilation, headaches

## Notes
- Sensor warms up in 20 seconds (best accuracy after 24-48 hours)
- Detects CO2, ammonia, benzene, alcohol, smoke
- Affected by temperature and humidity
- For educational/hobby use - not medical/safety grade
