#!/usr/bin/env python3
"""
3D Visualization for ADXL345 Accelerometer
Displays a 3D cube that rotates based on accelerometer readings
"""

import serial
import re
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import sys

# Configuration
SERIAL_PORT = '/dev/cu.usbserial-110'  # Change this to your port
BAUD_RATE = 115200
UPDATE_INTERVAL = 100  # milliseconds

class ADXL345Visualizer:
    def __init__(self, port, baudrate):
        self.port = port
        self.baudrate = baudrate
        self.ser = None

        # Current acceleration values
        self.x_g = 0.0
        self.y_g = 0.0
        self.z_g = 0.0

        # Rotation angles (in radians)
        self.roll = 0.0
        self.pitch = 0.0

        # Setup plot
        self.fig = plt.figure(figsize=(12, 6))

        # 3D cube plot
        self.ax1 = self.fig.add_subplot(121, projection='3d')
        self.ax1.set_xlabel('X')
        self.ax1.set_ylabel('Y')
        self.ax1.set_zlabel('Z')
        self.ax1.set_title('ADXL345 3D Orientation')
        self.ax1.set_xlim([-2, 2])
        self.ax1.set_ylim([-2, 2])
        self.ax1.set_zlim([-2, 2])

        # Text display for values
        self.ax2 = self.fig.add_subplot(122)
        self.ax2.axis('off')
        self.text = self.ax2.text(0.1, 0.5, '', fontsize=12, family='monospace',
                                   verticalalignment='center')

        # Connect to serial
        self.connect_serial()

    def connect_serial(self):
        """Connect to the serial port"""
        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=1)
            print(f"Connected to {self.port} at {self.baudrate} baud")
        except Exception as e:
            print(f"Error connecting to serial port: {e}")
            sys.exit(1)

    def read_sensor_data(self):
        """Read and parse sensor data from serial"""
        try:
            if self.ser and self.ser.in_waiting:
                line = self.ser.readline().decode('utf-8', errors='ignore').strip()

                # Parse X acceleration
                match_x = re.search(r'X:\s*(-?\d+\.\d+)\s*g', line)
                if match_x:
                    self.x_g = float(match_x.group(1))

                # Parse Y acceleration
                match_y = re.search(r'Y:\s*(-?\d+\.\d+)\s*g', line)
                if match_y:
                    self.y_g = float(match_y.group(1))

                # Parse Z acceleration
                match_z = re.search(r'Z:\s*(-?\d+\.\d+)\s*g', line)
                if match_z:
                    self.z_g = float(match_z.group(1))

                # Calculate roll and pitch from accelerometer
                # Roll (rotation around X-axis)
                self.roll = np.arctan2(self.y_g, self.z_g)

                # Pitch (rotation around Y-axis)
                self.pitch = np.arctan2(-self.x_g, np.sqrt(self.y_g**2 + self.z_g**2))

        except Exception as e:
            print(f"Error reading sensor: {e}")

    def create_cube_vertices(self):
        """Create vertices for a cube"""
        vertices = np.array([
            [-1, -1, -1],
            [1, -1, -1],
            [1, 1, -1],
            [-1, 1, -1],
            [-1, -1, 1],
            [1, -1, 1],
            [1, 1, 1],
            [-1, 1, 1]
        ]) * 0.5  # Scale down

        return vertices

    def rotate_vertices(self, vertices, roll, pitch):
        """Rotate vertices by roll and pitch angles"""
        # Rotation matrix for roll (around X-axis)
        Rx = np.array([
            [1, 0, 0],
            [0, np.cos(roll), -np.sin(roll)],
            [0, np.sin(roll), np.cos(roll)]
        ])

        # Rotation matrix for pitch (around Y-axis)
        Ry = np.array([
            [np.cos(pitch), 0, np.sin(pitch)],
            [0, 1, 0],
            [-np.sin(pitch), 0, np.cos(pitch)]
        ])

        # Combined rotation
        R = Ry @ Rx

        # Apply rotation to all vertices
        rotated = vertices @ R.T

        return rotated

    def draw_cube(self, vertices):
        """Draw a cube with the given vertices"""
        # Define the 6 faces of the cube
        faces = [
            [vertices[0], vertices[1], vertices[2], vertices[3]],  # Bottom
            [vertices[4], vertices[5], vertices[6], vertices[7]],  # Top
            [vertices[0], vertices[1], vertices[5], vertices[4]],  # Front
            [vertices[2], vertices[3], vertices[7], vertices[6]],  # Back
            [vertices[0], vertices[3], vertices[7], vertices[4]],  # Left
            [vertices[1], vertices[2], vertices[6], vertices[5]]   # Right
        ]

        # Create colors for each face
        colors = ['cyan', 'magenta', 'yellow', 'red', 'green', 'blue']

        # Create the 3D polygon collection
        cube = Poly3DCollection(faces, alpha=0.7, linewidths=2, edgecolors='black')
        cube.set_facecolor(colors)

        return cube

    def update_plot(self, frame):
        """Update the plot with new sensor data"""
        # Read new sensor data
        self.read_sensor_data()

        # Clear previous plot
        self.ax1.clear()
        self.ax1.set_xlabel('X')
        self.ax1.set_ylabel('Y')
        self.ax1.set_zlabel('Z')
        self.ax1.set_title('ADXL345 3D Orientation')
        self.ax1.set_xlim([-1.5, 1.5])
        self.ax1.set_ylim([-1.5, 1.5])
        self.ax1.set_zlim([-1.5, 1.5])

        # Create and rotate cube
        vertices = self.create_cube_vertices()
        rotated_vertices = self.rotate_vertices(vertices, self.roll, self.pitch)
        cube = self.draw_cube(rotated_vertices)
        self.ax1.add_collection3d(cube)

        # Add coordinate axes
        self.ax1.quiver(0, 0, 0, 1, 0, 0, color='r', arrow_length_ratio=0.1, linewidth=2)
        self.ax1.quiver(0, 0, 0, 0, 1, 0, color='g', arrow_length_ratio=0.1, linewidth=2)
        self.ax1.quiver(0, 0, 0, 0, 0, 1, color='b', arrow_length_ratio=0.1, linewidth=2)

        # Update text display
        text_content = f"""
ADXL345 Accelerometer Data
{'=' * 35}

Acceleration (g):
  X: {self.x_g:7.3f} g
  Y: {self.y_g:7.3f} g
  Z: {self.z_g:7.3f} g

Magnitude: {np.sqrt(self.x_g**2 + self.y_g**2 + self.z_g**2):7.3f} g

Orientation:
  Roll:  {np.degrees(self.roll):7.1f}°
  Pitch: {np.degrees(self.pitch):7.1f}°

{'=' * 35}
Red axis   = X
Green axis = Y
Blue axis  = Z
        """
        self.text.set_text(text_content)

    def run(self):
        """Run the visualization"""
        print("Starting ADXL345 3D Visualization...")
        print("Close the window to exit.")

        # Create animation
        anim = FuncAnimation(self.fig, self.update_plot,
                           interval=UPDATE_INTERVAL, blit=False)

        plt.tight_layout()
        plt.show()

    def close(self):
        """Close serial connection"""
        if self.ser:
            self.ser.close()
            print("Serial connection closed.")

def main():
    """Main function"""
    print("ADXL345 3D Visualizer")
    print("=" * 50)

    # Create visualizer
    viz = ADXL345Visualizer(SERIAL_PORT, BAUD_RATE)

    try:
        viz.run()
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        viz.close()

if __name__ == "__main__":
    main()
