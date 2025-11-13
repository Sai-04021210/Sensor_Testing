# Arduino M0 Servo Controller

Simple servo motor controller that randomly moves a servo and sends position data via serial to a Python server.

## Hardware Setup

- **Arduino M0** (or compatible)
- **Servo Motor** connected to **Pin 9**
- Power the servo appropriately (5V)

## Wiring

```
Servo    →  Arduino M0
-----       ----------
Signal   →  Pin 9
VCC      →  5V
GND      →  GND
```

## Arduino Setup

1. **Upload code to Arduino M0:**
   ```bash
   pio run -e arduinoM0_servo -t upload
   ```

2. **Monitor serial output (optional):**
   ```bash
   pio device monitor -b 115200
   ```

## Python Server Setup

1. **Install dependencies:**
   ```bash
   cd microcontrollers/ArduinoM0/sensors/Servo
   pip install -r requirements.txt
   ```

2. **Run the server:**
   ```bash
   python serial_server.py
   ```

The server will:
- Auto-detect the Arduino port
- Display servo position data in real-time
- Show visual ASCII representation of servo angle

## How It Works

1. Arduino randomly generates angles (0-180°) every 2 seconds
2. Servo moves to the new position
3. Arduino sends JSON data via serial: `{"angle":90,"time":1234}`
4. Python server receives and displays the data with visualization

## Example Output

```
╔════════════════════════════════════════════════╗
║   Arduino M0 Servo Serial Monitor             ║
║   Reads servo data via USB serial             ║
╚════════════════════════════════════════════════╝

Connected to Arduino on /dev/cu.usbmodem14201 at 115200 baud

[12:34:56]
Servo Angle: 145°
Device Time: 4567ms

Position: 0° ────────────────────────────────█───── 180°
          ↑ 145°
```
