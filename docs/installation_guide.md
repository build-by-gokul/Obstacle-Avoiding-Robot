# 📥 Installation Guide — Obstacle-Avoiding Robot Car

This guide walks you through the complete process of setting up and uploading the code to your Arduino Uno.

## Prerequisites

Before you begin, ensure you have:

- [ ] All hardware components (see [Hardware Requirements](hardware_requirements.md))
- [ ] A computer with a USB port
- [ ] Arduino IDE installed (see [Software Requirements](software_requirements.md))
- [ ] USB Type-A to Type-B cable

## Step 1: Install Arduino IDE

1. Visit [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Download the Arduino IDE for your operating system
3. Run the installer and follow the on-screen instructions
4. Launch the Arduino IDE after installation

## Step 2: Install USB Driver (If Needed)

Most genuine Arduino Uno boards work without additional drivers. If your board uses a CH340 chip (common in clones):

1. Download the CH340 driver from [wch-ic.com](http://www.wch-ic.com/downloads/CH341SER_EXE.html)
2. Install the driver
3. Restart your computer

## Step 3: Connect Arduino to Computer

1. Connect the Arduino Uno to your computer using the USB cable
2. The power LED on the Arduino should light up
3. Your computer should recognize the device

## Step 4: Configure Arduino IDE

1. Open Arduino IDE
2. Go to **Tools → Board** and select **Arduino Uno**
3. Go to **Tools → Port** and select the correct COM port
   - On Windows: Look for **COMx** (e.g., COM3, COM5)
   - On macOS: Look for `/dev/tty.usbmodem*`
   - On Linux: Look for `/dev/ttyACM0`
4. If unsure, disconnect the Arduino, check available ports, reconnect, and see which new port appears

## Step 5: Open the Source Code

1. Navigate to the `code/` folder in this repository
2. Open `obstacle_avoiding_robot.ino` in the Arduino IDE
   - Method 1: Double-click the `.ino` file
   - Method 2: In Arduino IDE, go to **File → Open** and browse to the file

## Step 6: Verify (Compile) the Code

1. Click the **✓ (Verify/Compile)** button in the Arduino IDE toolbar
2. Wait for the compilation to complete
3. The bottom panel should show:
   ```
   Sketch uses XXXX bytes (XX%) of program storage space.
   Global variables use XXX bytes (XX%) of dynamic memory.
   ```
4. If there are errors, check the error messages and verify you selected "Arduino Uno" as the board

## Step 7: Upload the Code

1. Ensure the Arduino is connected via USB
2. Ensure the correct board and port are selected
3. Click the **→ (Upload)** button in the Arduino IDE toolbar
4. Wait for the upload to complete
5. The bottom panel should show:
   ```
   Done uploading.
   ```
6. The Arduino's TX/RX LEDs will blink during upload — this is normal

## Step 8: Open Serial Monitor

1. Click the **🔍 (Serial Monitor)** button in the Arduino IDE toolbar (or press `Ctrl+Shift+M`)
2. Set the baud rate to **9600** (bottom-right dropdown)
3. You should see initialization messages:
   ```
   ===========================================
     OBSTACLE-AVOIDING ROBOT CAR
     Initializing...
   ===========================================
     Sensor pins configured.
     Motor pins configured.
     Obstacle threshold: 25 cm
     Motor speed: 180
     Initialization complete!
   ===========================================
   ```
4. If you see garbled text, verify the baud rate is set to 9600

## Step 9: Wire the Components

> ⚠️ **Disconnect the USB cable and battery before wiring.**

Follow the [Wiring Guide](../circuit/wiring_guide.md) to connect:
1. HC-SR04 ultrasonic sensor
2. L298N motor driver
3. Four DC motors
4. Battery pack

Refer to the [Pin Configuration](../circuit/pin_configuration.md) for detailed pin mappings.

## Step 10: Test the Robot

1. Place the robot on a flat surface with clearance around it
2. Connect the battery pack
3. Connect USB cable (optional — for serial monitor debugging)
4. Power on the Arduino
5. The robot should:
   - Start displaying distance readings on the serial monitor
   - Move forward when the path is clear
   - Stop and turn when an obstacle is detected within 25 cm

See the [Test Plan](../testing/test_plan.md) for detailed testing procedures.

## Troubleshooting Quick Reference

| Problem | Solution |
|---------|----------|
| Code won't compile | Verify board is set to "Arduino Uno" |
| Upload fails | Check USB cable and COM port selection |
| Serial monitor shows garbled text | Set baud rate to 9600 |
| Motors don't spin | Check L298N power and wiring |
| Robot moves backward | Swap motor wires or adjust code |
| Sensor shows 0 cm | Check HC-SR04 wiring and power |

For detailed troubleshooting, see [Troubleshooting Guide](troubleshooting.md).

## Quick Start Summary

```
1. Install Arduino IDE
2. Connect Arduino via USB
3. Open obstacle_avoiding_robot.ino
4. Select Board: Arduino Uno
5. Select Port: COMx
6. Click Verify (✓) — should compile without errors
7. Click Upload (→) — code transfers to Arduino
8. Open Serial Monitor — verify initialization messages
9. Wire all components (with power off)
10. Power on and test
```
