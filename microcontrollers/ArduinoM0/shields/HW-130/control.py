#!/usr/bin/env python3
"""
HW-130 Motor Shield Controller via Serial
Control Arduino M0 motors and servos from Python
"""

import serial
import serial.tools.list_ports
import time
import sys

class HW130Controller:
    def __init__(self, port=None, baudrate=115200):
        self.port = port
        self.baudrate = baudrate
        self.ser = None

    def find_arduino(self):
        """Auto-detect Arduino port"""
        ports = serial.tools.list_ports.comports()

        print("\nAvailable serial ports:")
        for i, port in enumerate(ports):
            print(f"{i+1}. {port.device} - {port.description}")

        if not ports:
            print("No serial ports found!")
            return None

        # Try to find Arduino
        for port in ports:
            if 'Arduino' in port.description or 'USB' in port.description or 'usbmodem' in port.device:
                return port.device

        # If not found, use first available port
        return ports[0].device

    def connect(self):
        """Connect to Arduino via serial"""
        if not self.port:
            self.port = self.find_arduino()

        if not self.port:
            print("No Arduino found!")
            return False

        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=1)
            time.sleep(2)  # Wait for Arduino to reset
            print(f"\nConnected to Arduino on {self.port} at {self.baudrate} baud\n")

            # Read initial messages from Arduino
            time.sleep(0.5)
            while self.ser.in_waiting > 0:
                line = self.ser.readline().decode('utf-8', errors='ignore').strip()
                if line:
                    print(f"[Arduino]: {line}")

            return True
        except Exception as e:
            print(f"Error connecting to {self.port}: {e}")
            return False

    def send_command(self, command):
        """Send command to Arduino"""
        if not self.ser or not self.ser.is_open:
            print("Not connected to Arduino!")
            return False

        try:
            self.ser.write(f"{command}\n".encode())
            time.sleep(0.1)

            # Read response
            timeout_start = time.time()
            while time.time() - timeout_start < 0.5:
                if self.ser.in_waiting > 0:
                    line = self.ser.readline().decode('utf-8', errors='ignore').strip()
                    if line:
                        print(f"[Arduino]: {line}")
            return True
        except Exception as e:
            print(f"Error sending command: {e}")
            return False

    def forward(self):
        """Move forward"""
        print(">>> Sending: Forward")
        self.send_command("1")

    def backward(self):
        """Move backward"""
        print(">>> Sending: Backward")
        self.send_command("2")

    def left(self):
        """Turn left"""
        print(">>> Sending: Turn Left")
        self.send_command("3")

    def right(self):
        """Turn right"""
        print(">>> Sending: Turn Right")
        self.send_command("4")

    def stop(self):
        """Stop motors"""
        print(">>> Sending: Stop")
        self.send_command("5")

    def servo1(self, angle):
        """Control Servo 1"""
        print(f">>> Sending: Servo 1 to {angle}°")
        self.send_command("6")
        time.sleep(0.2)
        self.send_command(str(angle))

    def servo2(self, angle):
        """Control Servo 2"""
        print(f">>> Sending: Servo 2 to {angle}°")
        self.send_command("7")
        time.sleep(0.2)
        self.send_command(str(angle))

    def set_speed(self, speed):
        """Set motor speed"""
        print(f">>> Sending: Set Speed to {speed}")
        self.send_command("8")
        time.sleep(0.2)
        self.send_command(str(speed))

    def show_menu(self):
        """Request menu from Arduino"""
        self.send_command("9")

    def interactive_mode(self):
        """Run interactive control"""
        print("\n" + "="*50)
        print("      HW-130 Motor Shield Python Control")
        print("="*50)
        print("Commands:")
        print("  w/1 - Forward")
        print("  s/2 - Backward")
        print("  a/3 - Turn Left")
        print("  d/4 - Turn Right")
        print("  x/5 - Stop")
        print("  q   - Quit")
        print("  m   - Show Arduino menu")
        print("="*50)

        while True:
            try:
                cmd = input("\nEnter command: ").strip().lower()

                if cmd in ['q', 'quit', 'exit']:
                    print("Stopping motors and exiting...")
                    self.stop()
                    break
                elif cmd in ['w', '1']:
                    self.forward()
                elif cmd in ['s', '2']:
                    self.backward()
                elif cmd in ['a', '3']:
                    self.left()
                elif cmd in ['d', '4']:
                    self.right()
                elif cmd in ['x', '5', 'stop']:
                    self.stop()
                elif cmd == 'm':
                    self.show_menu()
                elif cmd.startswith('speed'):
                    try:
                        speed = int(cmd.split()[1])
                        self.set_speed(speed)
                    except:
                        print("Usage: speed <0-255>")
                elif cmd.startswith('s1'):
                    try:
                        angle = int(cmd.split()[1])
                        self.servo1(angle)
                    except:
                        print("Usage: s1 <angle>")
                elif cmd.startswith('s2'):
                    try:
                        angle = int(cmd.split()[1])
                        self.servo2(angle)
                    except:
                        print("Usage: s2 <angle>")
                else:
                    print("Unknown command! Use: w/a/s/d/x or 1/2/3/4/5")

            except KeyboardInterrupt:
                print("\n\nStopping motors and exiting...")
                self.stop()
                break
            except Exception as e:
                print(f"Error: {e}")

    def close(self):
        """Close serial connection"""
        if self.ser and self.ser.is_open:
            self.ser.close()
            print("Disconnected from Arduino")

def main():
    print("""
╔════════════════════════════════════════════════╗
║   HW-130 Motor Shield Python Controller       ║
║   Control Arduino M0 via Serial                ║
╚════════════════════════════════════════════════╝
    """)

    controller = HW130Controller()

    try:
        if controller.connect():
            controller.interactive_mode()
    except KeyboardInterrupt:
        print("\n\nExiting...")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        controller.close()

if __name__ == "__main__":
    main()
