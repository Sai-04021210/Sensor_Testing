# GY-NEO6MV2 GPS Module with ESP8266

## Hardware Setup

### Wiring
Connect the GY-NEO6MV2 to ESP8266 NodeMCU:

| GPS Pin | ESP8266 Pin | Description |
|---------|-------------|-------------|
| VCC     | 3.3V        | Power supply (3.3V) |
| GND     | GND         | Ground |
| TX      | Not used    | GPS transmit (not connected) |
| RX      | D4 (GPIO2)  | GPS receive (connect to Serial1 TX) |

**Note:** ESP8266 Serial1 is TX-only. We use D4 (GPIO2) to send data to GPS RX.

## Build and Upload

```bash
pio run -e esp8266_gps -t upload
```

## Monitor Output

```bash
pio device monitor -e esp8266_gps -b 115200
```

## What You'll See

The GPS module will display:
- **Location:** Latitude, Longitude, Altitude
- **Movement:** Speed (km/h), Course (degrees)
- **Time:** UTC date and time
- **Signal Quality:** Number of satellites, HDOP

**First-time GPS lock:** May take 1-5 minutes outdoors with clear sky view.

## Configuration

Adjust settings in `GPS.h`:

```cpp
struct GPSConfig {
  unsigned long readInterval = 3000;     // Read every 3 seconds
  unsigned long serialBaudRate = 115200;
  unsigned long gpsBaudRate = 9600;      // NEO6M default
};
```

## Troubleshooting

### No GPS Signal
- **Make sure you're outdoors** with a clear view of the sky
- GPS doesn't work well indoors or near buildings
- First fix can take 1-5 minutes (cold start)
- Check "Satellites in view" - need at least 4 for a fix

### No Data in Serial Monitor
- Check wiring connections
- GPS RX should connect to ESP8266 D4 (GPIO2)
- Make sure GPS module has power (LED should blink)
- Use correct baud rate: `-b 115200`

### GPS Module Not Responding
- GPS module requires 3.3V power
- Check GND connection
- GPS TX doesn't need to be connected (Serial1 is TX-only)

## Tips

- **Cold start:** 30+ seconds (no satellite data stored)
- **Warm start:** 5-30 seconds (recent data available)
- **Hot start:** <5 seconds (just powered on)
- Best results: Open area, away from tall buildings
- The module updates position every second
