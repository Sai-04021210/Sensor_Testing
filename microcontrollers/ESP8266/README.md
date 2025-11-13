# ESP8266 Sensor Testing

Documentation for testing sensors with ESP8266 (NodeMCU V2).

## Board Specifications

- **Microcontroller**: ESP8266 (Tensilica 32-bit)
- **Operating Voltage**: 3.3V
- **Digital Pins**: 9 (D0-D8)
- **Analog Pins**: 1 (A0)
- **Flash Memory**: 4MB
- **SRAM**: 80KB
- **Clock Speed**: 80-160 MHz

## Important Notes

⚠️ **ESP8266 operates at 3.3V logic!**
- Do NOT connect 5V signals directly
- Use level shifters for 5V sensors
- A0 pin max voltage: 1.0V (use voltage divider for higher voltages)

⚠️ **Only ONE analog pin (A0)**
- If multiple sensors need analog input, use a multiplexer
- Or test sensors one at a time

## Available Sensors

### ✅ MQ135 - Gas Sensor (CO2)
- **Status**: Fully implemented
- **Location**: `sensors/MQ135/`
- **Pins Used**: A0 (analog), D1 (digital)

### 🚧 DHT11 - Temperature & Humidity
- **Status**: Structure ready
- **Location**: `sensors/DHT11/`
- **Pins Used**: D4

### 🚧 LM35 - Temperature Sensor
- **Status**: Structure ready
- **Location**: `sensors/LM35/`
- **Pins Used**: A0 (shares with MQ135)

### 🚧 Rain Sensor
- **Status**: Structure ready
- **Location**: `sensors/RainSensor/`
- **Pins Used**: D6

## Pin Reference

```
ESP8266 Pin  |  GPIO  |  Functions       |  Notes
-------------|--------|------------------|---------------------------
D0           |  16    |  Digital only    |  No PWM, I2C, interrupts
D1           |  5     |  Digital, PWM    |  Often used for I2C SCL
D2           |  4     |  Digital, PWM    |  Often used for I2C SDA
D3           |  0     |  Digital, PWM    |  Boot mode pin - avoid
D4           |  2     |  Digital, PWM    |  Built-in LED, boot mode
D5           |  14    |  Digital, PWM    |  SPI SCK
D6           |  12    |  Digital, PWM    |  SPI MISO
D7           |  13    |  Digital, PWM    |  SPI MOSI
D8           |  15    |  Digital, PWM    |  Boot mode pin - avoid
A0           |  ADC0  |  Analog 0-1V     |  Only analog input
```

## Configuration

Board settings are in `config.json`:
- Pin mappings
- Voltage levels
- Upload/monitor speeds
- Board-specific notes

## Testing a Sensor

1. **Navigate to sensor folder**
   ```bash
   cd sensors/MQ135/  # or your sensor
   ```

2. **Read the sensor README**
   - Check wiring diagram
   - Understand configuration options
   - Note any calibration requirements

3. **Update platformio.ini** (in project root)
   - Set correct source files
   - Add any required libraries

4. **Upload and test**
   ```bash
   pio run -t upload
   pio device monitor
   ```

## Adding a New Sensor

1. Create sensor folder: `sensors/YourSensor/`
2. Add implementation:
   - `YourSensor.cpp` - Implementation
   - `YourSensor.h` - Header with config struct
   - `README.md` - Wiring and usage docs
3. Update this README with sensor status

## Common Issues

### Upload fails
- Check USB cable connection
- Press RESET before upload
- Try lowering upload speed in platformio.ini

### No serial output
- Verify monitor speed matches code (115200)
- Check USB drivers are installed
- Try different USB port

### Sensor reads garbage
- Check power supply (stable 3.3V/5V)
- Verify pin connections
- Add delay after sensor initialization
- Check for loose connections

## Libraries

Common libraries for ESP8266:
- ESP8266WiFi - WiFi connectivity
- Wire - I2C communication
- SPI - SPI communication
- ESP8266WebServer - Web server

Install via PlatformIO:
```ini
lib_deps =
    ESP8266WiFi
    Wire
```

## Resources

- [ESP8266 Arduino Core Docs](https://arduino-esp8266.readthedocs.io/)
- [NodeMCU Pinout](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
- [PlatformIO ESP8266 Platform](https://docs.platformio.org/en/latest/platforms/espressif8266.html)
