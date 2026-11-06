# 🔧 Hardware Requirements — Obstacle-Avoiding Robot Car

> **Reconstruction Notice:** This hardware list has been reconstructed in 2026 based on
> the original project requirements. Verify component specifications against your actual
> parts before assembly.

## Bill of Materials (BOM)

| # | Component | Quantity | Specifications | Approx. Cost (USD) |
|---|-----------|----------|----------------|-------------------|
| 1 | Arduino Uno R3 | 1 | ATmega328P, 14 digital I/O, 6 analog inputs | \$3–\$25 |
| 2 | HC-SR04 Ultrasonic Sensor | 1 | 5V, 2–400 cm range, 15° beam angle | \$1–\$3 |
| 3 | L298N Motor Driver Module | 1 | Dual H-bridge, 5–35V, 2A per channel | \$2–\$5 |
| 4 | DC Geared Motor (3–6V) | 4 | 100–200 RPM, with gear reduction | \$1–\$2 each |
| 5 | Four-Wheel Robot Chassis | 1 | Acrylic or plastic, pre-drilled mounting holes | \$5–\$15 |
| 6 | Robot Wheels | 4 | 65mm diameter (typical), fits motor shaft | Included with chassis |
| 7 | Jumper Wires | ~20 | Male-to-male and male-to-female, various lengths | \$2–\$5 |
| 8 | Battery Pack | 1 | 7.4V Li-ion (2S) or 4×AA holder (6V) | \$3–\$10 |
| 9 | USB Cable (Type-A to B) | 1 | For Arduino programming and serial monitor | \$1–\$3 |
| 10 | Battery Holder / Strap | 1 | To secure battery to chassis | \$1–\$2 |

**Estimated Total Cost: \$25–\$80** (depending on source and quality)

## Detailed Component Specifications

### 1. Arduino Uno R3

The Arduino Uno is the brain of the robot — the **microcontroller** that runs our code.

| Parameter | Value |
|-----------|-------|
| Microcontroller | ATmega328P |
| Clock Speed | 16 MHz |
| Digital I/O Pins | 14 (6 PWM capable) |
| Analog Input Pins | 6 |
| Flash Memory | 32 KB |
| SRAM | 2 KB |
| EEPROM | 1 KB |
| Operating Voltage | 5V |
| Input Voltage (recommended) | 7–12V |
| DC Current per I/O Pin | 20 mA (max 40 mA) |

> **Why Arduino Uno?** It is the most widely used Arduino board for beginners.
> It has enough I/O pins for our project, built-in USB programming, and extensive
> community support. It runs at 5V logic, which is compatible with both the HC-SR04
> sensor and L298N motor driver.

### 2. HC-SR04 Ultrasonic Distance Sensor

The ultrasonic sensor is the robot's "eyes" — it detects obstacles ahead.

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 5V DC |
| Operating Current | 15 mA |
| Measuring Range | 2 cm – 400 cm |
| Measuring Angle | ~15° cone |
| Trigger Input Signal | 10µs TTL pulse |
| Echo Output Signal | TTL pulse (proportional to distance) |
| Frequency | 40 kHz |
| Dimensions | 45mm × 20mm × 15mm |

### 3. L298N Dual H-Bridge Motor Driver

The motor driver is the "muscle controller" — it amplifies Arduino signals to drive the motors.

| Parameter | Value |
|-----------|-------|
| Driver Chip | L298N (STMicroelectronics) |
| Motor Supply Voltage (VS) | 5V – 35V |
| Logic Supply Voltage (VSS) | 5V |
| Max Current per Channel | 2A |
| Peak Current per Channel | 3A |
| Built-in 5V Regulator | Yes (for VS ≤ 12V) |
| Control Inputs | IN1, IN2, IN3, IN4 |
| Enable Pins | ENA, ENB (PWM compatible) |
| Outputs | OUT1, OUT2, OUT3, OUT4 |

### 4. DC Geared Motors

The motors provide locomotion. Gear reduction increases torque at the cost of speed.

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 3V – 6V |
| No-load Current | ~70 mA |
| Stall Current | ~250 mA |
| Speed (at 6V, no load) | ~100–200 RPM |
| Shaft | Double-sided or single-sided |
| Mounting | Compatible with standard 4WD chassis |

> **Current Consideration:** With 4 motors, peak total current can reach 1A.
> The L298N can handle 2A per channel (2 motors per channel), but adequate
> battery capacity is important.

### 5. Battery Pack

| Option | Voltage | Capacity | Runtime | Notes |
|--------|---------|----------|---------|-------|
| 2S Li-ion (7.4V) | 7.4V | 1800–3000 mAh | ~1–3 hours | Recommended — rechargeable, good power |
| 4× AA Alkaline | 6V | ~2000 mAh | ~1–2 hours | Easy to replace, slightly low voltage |
| 4× AA Rechargeable NiMH | 4.8V | ~2000 mAh | ~1–2 hours | May be too low for reliable operation |
| 9V Battery | 9V | ~500 mAh | ~20–30 min | Not recommended — low capacity |

> **Recommended:** 2S (7.4V) Li-ion or Li-Po battery pack with 1800+ mAh capacity.
> This provides sufficient voltage for both the motors and the L298N's 5V regulator.

### 6. USB Cable

A standard USB Type-A to Type-B cable (the same type used for printers) is needed to:
- Upload code from your computer to the Arduino
- Monitor serial output for debugging
- Power the Arduino during development (without battery)

## Alternative Components

| Original Component | Alternative | Differences |
|-------------------|-------------|-------------|
| Arduino Uno | Arduino Nano | Smaller form factor, same ATmega328P, fewer I/O headers |
| Arduino Uno | Arduino Mega | More I/O pins, more memory — overkill for this project |
| L298N Module | L293D Shield | Sits on top of Arduino, simpler wiring, lower current (600mA) |
| L298N Module | TB6612FNG | More efficient (no voltage drop), smaller, 1.2A per channel |
| HC-SR04 | HC-SR05 | Similar function, different form factor |
| HC-SR04 | Sharp IR Sensor | Infrared instead of ultrasonic — better for specific surfaces |
| 4× DC Motors | 2× DC Motors | Simpler, but less traction and stability |

## Tools Needed for Assembly

| Tool | Purpose |
|------|---------|
| Screwdriver (Phillips) | Assemble chassis, mount motors |
| Wire strippers | Prepare motor wires |
| Soldering iron (optional) | Solder motor wires for reliability |
| Electrical tape | Insulate connections |
| Hot glue gun (optional) | Mount sensor, secure wires |
| Multimeter (recommended) | Verify voltages and connections |
