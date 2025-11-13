# PIR Motion Sensor with ESP8266

## Hardware Setup

### Wiring
Connect the PIR sensor to ESP8266 NodeMCU:

| PIR Pin | ESP8266 Pin | Description |
|---------|-------------|-------------|
| VCC     | 5V or 3.3V  | Power supply |
| GND     | GND         | Ground |
| OUT     | D5 (GPIO14) | Digital output (HIGH when motion detected) |

**Note:** Most PIR sensors work with both 3.3V and 5V. Output is 3.3V compatible.

## Build and Upload

```bash
pio run -e esp8266_pir -t upload
```

## Monitor Output

```bash
pio device monitor -e esp8266_pir -b 115200
```

## What You'll See

**Calibration (30 seconds):**
- Progress bar showing sensor warm-up
- Don't move during this time

**Operation:**
- 🚨 **Motion detected** alerts with count
- ✅ **Motion ended** with duration
- 📊 **Status updates** every 30 seconds
- Total detection count

## Configuration

Adjust settings in `PIR.h`:

```cpp
struct PIRConfig {
  int pirPin = D5;                       // PIR output pin
  unsigned long readInterval = 500;      // Check every 500ms
  unsigned long debounceDelay = 200;     // Debounce 200ms
  unsigned long calibrationTime = 30000; // 30s warm-up
};
```

## How It Works

PIR sensors detect infrared radiation changes:
1. **Warm-up:** Sensor stabilizes (30 seconds)
2. **Monitoring:** Detects heat signatures moving
3. **Output:** Goes HIGH when motion detected
4. **Trigger:** Stays HIGH during motion
5. **Reset:** Goes LOW when no motion

## Troubleshooting

### Constant Motion Detection
- Sensor needs full warm-up (30 seconds)
- Check for heat sources (heater, sunlight)
- Adjust sensitivity potentiometer on sensor
- Keep away from moving air (fan, AC)

### No Motion Detection
- Check wiring (OUT → D5)
- Verify power supply
- Increase sensor sensitivity (turn potentiometer)
- Check sensor detection range (up to 7m)

### False Triggers
- Increase debounce delay in config
- Keep away from pets, moving curtains
- Ensure sensor is stable (not vibrating)
- Adjust detection angle/range pots on sensor

## Sensor Adjustments

Most PIR sensors have 2 potentiometers:
- **Sensitivity (Sx):** Detection range (2m - 7m)
- **Time Delay (Tx):** How long output stays HIGH (0.3s - 200s)

**Recommended settings:**
- Sensitivity: Medium (3-5m range)
- Time Delay: Low (0.3-5s)

## Specifications

- **Detection Range:** 2m - 7m (adjustable)
- **Detection Angle:** ~120° cone
- **Power:** 3.3V - 5V
- **Current:** ~65mA
- **Output:** 3.3V (HIGH when motion)
- **Warm-up:** 30-60 seconds
