# Sensor Testing Platform

A modular, organized platform for testing sensors with various microcontrollers. Each microcontroller has its own folder with individual sensor implementations to eliminate redundancy.

## Project Structure

```
sensor_testing/
├── microcontrollers/
│   ├── ESP8266/
│   │   ├── config.json          # ESP8266-specific configuration
│   │   ├── README.md            # ESP8266 documentation
│   │   └── sensors/
│   │       ├── MQ135/           # Gas sensor
│   │       │   ├── MQ135.cpp
│   │       │   ├── MQ135.h
│   │       │   └── README.md
│   │       ├── DHT11/           # Temperature & humidity
│   │       │   ├── DHT11.cpp
│   │       │   ├── DHT11.h
│   │       │   └── README.md
│   │       ├── LM35/            # Temperature sensor
│   │       └── RainSensor/      # Rain detection
│   │
│   └── ArduinoM0/
│       ├── config.json          # Arduino M0-specific configuration
│       ├── README.md            # Arduino M0 documentation
│       └── sensors/             # Add sensors here
│
└── platformio.ini               # Build configuration

```

## Quick Start - 3 Simple Steps

### 1. Wire Your Sensor
Check the sensor's README in `microcontrollers/[YourBoard]/sensors/[SensorName]/`

### 2. Upload the Code
```bash
# For MQ135 CO2 sensor on ESP8266:
pio run -e esp8266_mq135 -t upload
```

### 3. Monitor Output
```bash
pio device monitor -e esp8266_mq135 -b 115200
```

That's it! The sensor starts reading immediately after upload.

## Available Sensors

### ESP8266
- **MQ135** (CO2/Air Quality)
  ```bash
  pio run -e esp8266_mq135 -t upload
  pio device monitor -e esp8266_mq135 -b 115200
  ```

- **ADXL345** (Accelerometer) - 3D visualization included
  ```bash
  pio run -e esp8266_adxl345 -t upload
  pio device monitor -e esp8266_adxl345 -b 115200
  ```
  Run 3D visualizer:
  ```bash
  cd microcontrollers/ESP8266/sensors/ADXL345
  source venv/bin/activate
  python3 visualize_3d.py
  ```

- **GY-NEO6MV2** (GPS Module)
  ```bash
  pio run -e esp8266_gps -t upload
  pio device monitor -e esp8266_gps -b 115200
  ```

- **GY-61** (ADXL335 Analog Accelerometer)
  ```bash
  pio run -e esp8266_gy61 -t upload
  pio device monitor -e esp8266_gy61 -b 115200
  ```

- **HC-SR04** (Ultrasonic Distance Sensor)
  ```bash
  pio run -e esp8266_hcsr04 -t upload
  pio device monitor -e esp8266_hcsr04 -b 115200
  ```

- **PIR** (Motion Sensor)
  ```bash
  pio run -e esp8266_pir -t upload
  pio device monitor -e esp8266_pir -b 115200
  ```

- **DHT11** (Temperature/Humidity) - Coming soon
- **LM35** (Temperature) - Coming soon

### Arduino M0
- Structure ready - Add your sensors here

## Adding New Microcontrollers

1. Create a new folder: `microcontrollers/YourBoard/`
2. Add `config.json` with board-specific settings
3. Create `sensors/` subfolder
4. Add `README.md` with documentation

## Adding New Sensors

1. Go to `microcontrollers/[YourBoard]/sensors/`
2. Create sensor folder: `mkdir NewSensor/`
3. Add implementation files: `NewSensor.cpp`, `NewSensor.h`
4. Add `README.md` with wiring diagram and usage
5. Update board's `config.json` if needed

## Current Status

### ESP8266
- ✅ MQ135 (Gas sensor)
- ✅ ADXL345 (Accelerometer with 3D visualization)
- ✅ GY-NEO6MV2 (GPS Module)
- ✅ GY-61 (ADXL335 Analog Accelerometer)
- ✅ HC-SR04 (Ultrasonic Distance Sensor)
- ✅ PIR (Motion Sensor)
- 🚧 DHT11 (Temperature/Humidity) - Structure ready
- 🚧 LM35 (Temperature) - Structure ready

### Arduino M0
- 📁 Folder structure created
- ➕ Add sensors as needed

## Features

- **No Redundancy**: Each sensor is self-contained in its own folder
- **Easy Configuration**: JSON config files per microcontroller
- **Modular Design**: Add sensors without affecting others
- **Clean Structure**: Easy to navigate and maintain
- **Individual Documentation**: Each sensor has its own README

## Requirements

- PlatformIO
- VS Code (recommended)
- Appropriate microcontroller board
- Sensor hardware

## License

This project is for educational and testing purposes.
