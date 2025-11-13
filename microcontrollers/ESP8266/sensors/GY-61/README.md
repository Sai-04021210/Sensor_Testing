# GY-61 (ADXL335) Accelerometer with ESP8266

## Hardware Setup

### Wiring
Connect the GY-61 to ESP8266 NodeMCU:

| GY-61 Pin | ESP8266 Pin | Description |
|-----------|-------------|-------------|
| VCC       | 3.3V        | Power supply (3.3V) |
| GND       | GND         | Ground |
| X-out     | A0          | X-axis analog output |
| Y-out     | Not used*   | Y-axis analog output |
| Z-out     | Not used*   | Z-axis analog output |

**Important:** ESP8266 has only **ONE** analog pin (A0). This code reads X-axis only.

### Reading Y and Z axes:
**Option 1:** Manually swap wiring
- Connect Y-out to A0 for Y readings
- Connect Z-out to A0 for Z readings

**Option 2:** Use an analog multiplexer (CD4051 or similar)

## Build and Upload

```bash
pio run -e esp8266_gy61 -t upload
```

## Monitor Output

```bash
pio device monitor -e esp8266_gy61 -b 115200
```

## What You'll See

The sensor displays:
- **X-axis voltage** (0-3.3V)
- **X-axis G-force** (-3g to +3g)
- **Orientation** (Tilted LEFT/RIGHT/Level)
- Updates every 3 seconds

## Configuration

Adjust settings in `GY61.h`:

```cpp
struct GY61Config {
  int xPin = A0;                         // Analog pin A0
  float vcc = 3.3;                       // Supply voltage
  float zeroG = 1.65;                    // 0g voltage (VCC/2)
  float sensitivity = 0.3;               // 300mV/g
  unsigned long readInterval = 3000;     // 3 seconds
  int numSamples = 10;                   // Averaging samples
};
```

## Calibration

The GY-61 outputs analog voltage:
- **At 0g (level):** ~1.65V (VCC/2)
- **At +1g:** ~1.95V (1.65V + 0.3V)
- **At -1g:** ~1.35V (1.65V - 0.3V)

If readings seem off:
1. Measure actual VCC voltage
2. Place sensor level and note X-out voltage
3. Update `zeroG` value in config

## Troubleshooting

### Wrong Readings
- Check VCC is exactly 3.3V (use multimeter)
- Calibrate `zeroG` by measuring voltage when level
- Ensure good GND connection

### No Data / Always 0
- Verify X-out is connected to A0
- Check sensor has power (VCC/GND)
- ESP8266 ADC range is 0-1V internally (with voltage divider)

### Want to Read All 3 Axes?
Use an Arduino with 3+ analog pins, or add a multiplexer chip (CD4051).

## Specifications

- **Range:** ±3g
- **Sensitivity:** 300 mV/g
- **Supply:** 1.8V - 3.6V (use 3.3V)
- **Output:** Analog voltage (ratiometric to VCC)
