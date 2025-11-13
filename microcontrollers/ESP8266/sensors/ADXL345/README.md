# ADXL345 Accelerometer with ESP8266

## Hardware Setup

### Wiring (I2C Mode)
Connect the ADXL345 to ESP8266 NodeMCU as follows:

| ADXL345 Pin | ESP8266 Pin | Description |
|-------------|-------------|-------------|
| VCC         | 3.3V        | Power supply (3.3V) |
| GND         | GND         | Ground |
| SDA         | D2 (GPIO4)  | I2C Data line |
| SCL         | D1 (GPIO5)  | I2C Clock line |
| CS          | 3.3V or NC  | Chip Select (HIGH for I2C mode) |
| SDO         | GND         | I2C Address (GND=0x53, VCC=0x1D) |

### I2C Address
- Default: **0x53** (when SDO/ALT ADDRESS is connected to GND)
- Alternate: **0x1D** (when SDO/ALT ADDRESS is connected to VCC)

## Build and Upload

1. **Build the project:**
   ```bash
   pio run -e esp8266_adxl345
   ```

2. **Upload to ESP8266:**
   ```bash
   pio run -e esp8266_adxl345 -t upload
   ```

3. **Monitor serial output:**
   ```bash
   pio device monitor -e esp8266_adxl345 -b 115200
   ```

   Note: The `-b 115200` flag sets the correct baud rate. Without it, you'll see garbled output.

## 3D Visualization

### Installation

First, create a virtual environment and install the required Python packages:

```bash
# Create virtual environment
python3 -m venv venv

# Activate virtual environment
source venv/bin/activate

# Install packages
pip install pyserial numpy matplotlib
```

Or use the requirements file:
```bash
source venv/bin/activate
pip install -r requirements.txt
```

### Running the Visualization

1. **Make sure your ESP8266 is connected and running**

2. **Update the serial port in the script if needed:**
   Edit `visualize_3d.py` and change the `SERIAL_PORT` variable to match your port:
   ```python
   SERIAL_PORT = '/dev/cu.usbserial-110'  # macOS
   # SERIAL_PORT = '/dev/ttyUSB0'         # Linux
   # SERIAL_PORT = 'COM3'                  # Windows
   ```

3. **Activate the virtual environment and run:**
   ```bash
   source venv/bin/activate
   python3 visualize_3d.py
   ```

### Features

The visualization shows:
- **3D rotating cube** that matches your sensor's orientation
- **Real-time acceleration values** (X, Y, Z in g-force)
- **Roll and Pitch angles** calculated from accelerometer
- **Magnitude** of acceleration
- **Color-coded axes:**
  - Red = X axis
  - Green = Y axis
  - Blue = Z axis

### Tips

- Tilt the sensor to see the cube rotate in real-time
- The cube responds to the orientation of your ADXL345 sensor
- Close the window to exit the visualization
- If you get serial port errors, make sure no other program (like PlatformIO monitor) is using the port

## Configuration

You can adjust sensor settings in `ADXL345.h`:

```cpp
struct ADXL345Config {
  int sdaPin = D2;              // SDA pin
  int sclPin = D1;              // SCL pin
  uint8_t i2cAddress = 0x53;    // I2C address
  uint8_t range = 2;            // Range: 2, 4, 8, or 16g
  uint8_t dataRate = 10;        // Data rate (10 = 100Hz)
  unsigned long readInterval = 3000;  // Read every 3000ms (3 seconds)
};
```

## Troubleshooting

### Serial Port Issues
- **Garbled output**: Make sure to specify the baud rate: `pio device monitor -e esp8266_adxl345 -b 115200`
- **"Resource busy"**: Another program is using the port. Close PlatformIO monitor or other serial tools. Check with `lsof /dev/cu.usbserial-110` and kill processes if needed.
- **"Permission denied"**: On Linux, add your user to the `dialout` group:
  ```bash
  sudo usermod -a -G dialout $USER
  ```

### Sensor Not Found
- Check wiring connections
- Verify I2C address (default is 0x53)
- Make sure VCC is connected to 3.3V (not 5V)

### No Data in Visualization
- Make sure the ESP8266 is uploading data (check with serial monitor first)
- Update the `SERIAL_PORT` in `visualize_3d.py`
- Check that required Python packages are installed

## References

- [ADXL345 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf)
- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
