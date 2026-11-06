# 💻 Software Requirements — Obstacle-Avoiding Robot Car

## Required Software

### 1. Arduino IDE

The Arduino Integrated Development Environment (IDE) is required to write, compile, and upload code to the Arduino Uno.

| Parameter | Details |
|-----------|---------|
| Software | Arduino IDE |
| Version | 2.0 or later (recommended) |
| Legacy | Arduino IDE 1.8.x also works |
| Download | [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software) |
| Supported OS | Windows, macOS, Linux |
| Cost | Free (open-source) |

### 2. USB Driver

Most Arduino Uno boards use the **ATmega16U2** USB-to-serial chip, which is supported natively by most operating systems. If your board uses a **CH340** chip (common in clone boards), you may need to install a driver:

| Chip | Driver Needed? | Download |
|------|---------------|----------|
| ATmega16U2 (genuine Uno) | Usually no | Built into most OS |
| CH340/CH340G (clone) | Yes, on some systems | [CH340 Driver](http://www.wch-ic.com/downloads/CH341SER_EXE.html) |
| CP2102 (some clones) | Yes, on some systems | [CP210x Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) |

## Arduino IDE Configuration

### Board Settings

Configure these settings in the Arduino IDE before uploading:

| Setting | Value |
|---------|-------|
| Board | Arduino Uno |
| Processor | ATmega328P |
| Port | COM port where Arduino is connected |
| Programmer | AVRISP mkII (default) |

### How to Find the Correct COM Port

**Windows:**
1. Open Device Manager
2. Look under "Ports (COM & LPT)"
3. The Arduino will appear as "Arduino Uno (COMx)" or "USB-SERIAL CH340 (COMx)"

**macOS:**
1. Open Terminal
2. Run: `ls /dev/tty.*`
3. Look for `/dev/tty.usbmodem*` or `/dev/tty.usbserial*`

**Linux:**
1. Open Terminal
2. Run: `ls /dev/ttyACM*` or `ls /dev/ttyUSB*`
3. The Arduino will appear as `/dev/ttyACM0` or `/dev/ttyUSB0`

## External Libraries

This project uses **only built-in Arduino functions**. No external libraries need to be installed.

| Function | Source | Purpose |
|----------|--------|---------|
| `pinMode()` | Built-in | Configure pin as INPUT/OUTPUT |
| `digitalWrite()` | Built-in | Set digital pin HIGH/LOW |
| `digitalRead()` | Built-in | Read digital pin state |
| `analogWrite()` | Built-in | Write PWM value (0–255) |
| `pulseIn()` | Built-in | Measure pulse duration |
| `Serial.begin()` | Built-in | Initialize serial communication |
| `Serial.print()` | Built-in | Output text to serial monitor |
| `delay()` | Built-in | Pause execution (milliseconds) |
| `delayMicroseconds()` | Built-in | Pause execution (microseconds) |

> **No external dependencies** — This design choice keeps the project simple,
> reduces potential compatibility issues, and ensures it compiles on any standard
> Arduino IDE installation without additional setup.

## Optional Software

| Software | Purpose | Required? |
|----------|---------|-----------|
| Fritzing | Create circuit diagrams | No — for documentation |
| Tinkercad Circuits | Simulate the circuit online | No — for learning |
| Serial Plotter | Visualize sensor data graphically | No — built into Arduino IDE |
| Git | Version control | No — for GitHub workflow |
| VS Code + Arduino Extension | Alternative code editor | No — for advanced users |

## System Requirements

### Minimum Computer Requirements

| Requirement | Specification |
|-------------|--------------|
| OS | Windows 10+, macOS 10.15+, or Linux (64-bit) |
| RAM | 4 GB |
| Disk Space | 500 MB (for Arduino IDE) |
| USB Port | 1× USB Type-A (for Arduino connection) |
| Internet | Required only for initial Arduino IDE download |
