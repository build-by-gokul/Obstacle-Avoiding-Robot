# 🔌 Wiring Guide — Obstacle-Avoiding Robot Car

> **Reconstruction Notice:** This wiring guide has been reconstructed in 2026 based on
> standard component datasheets and common wiring practices. Verify all connections
> against your actual components before powering on.

## Overview

This guide explains how to connect all components of the obstacle-avoiding robot car. Follow the connections carefully — incorrect wiring can damage components.

## ⚠️ Safety Precautions

1. **Never connect motors directly to Arduino pins** — Arduino GPIO pins can only supply ~40mA per pin. DC motors draw 100–300mA or more. Always use a motor driver.
2. **Double-check polarity** before connecting the battery pack.
3. **Disconnect the battery** when making wiring changes.
4. **Ensure common ground** — all components must share a common GND connection.
5. **Do not exceed voltage ratings** — Arduino Uno: 5V logic; L298N: 5–35V motor supply; HC-SR04: 5V supply.

## Component Connection Details

### 1. HC-SR04 Ultrasonic Sensor → Arduino Uno

The HC-SR04 has four pins:

| HC-SR04 Pin | Connect To | Wire Color (Suggested) | Purpose |
|-------------|-----------|----------------------|---------|
| VCC | Arduino 5V | Red | Power supply (5V) |
| TRIG | Arduino Pin 9 | Yellow | Trigger pulse output |
| ECHO | Arduino Pin 10 | Green | Echo pulse input |
| GND | Arduino GND | Black | Ground reference |

**How it works:**
- The Arduino sends a 10µs HIGH pulse on the TRIG pin
- The sensor emits 8 ultrasonic pulses at 40kHz
- The ECHO pin goes HIGH for the duration of the round trip
- The Arduino measures this duration to calculate distance

### 2. L298N Motor Driver → Arduino Uno

The L298N module has control pins and power terminals:

| L298N Pin | Connect To | Purpose |
|-----------|-----------|---------|
| ENA | Arduino Pin 5 (PWM) | Speed control for left motors |
| IN1 | Arduino Pin 2 | Left motors direction control |
| IN2 | Arduino Pin 3 | Left motors direction control |
| IN3 | Arduino Pin 4 | Right motors direction control |
| IN4 | Arduino Pin 7 | Right motors direction control |
| ENB | Arduino Pin 6 (PWM) | Speed control for right motors |

> **Important:** Remove the jumpers on ENA and ENB if present. The jumpers bypass
> PWM speed control and run motors at full speed. We need PWM control via Arduino pins.

**Direction Logic:**

| IN1 | IN2 | Left Motor Action |
|-----|-----|-------------------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Stop (coast) |
| HIGH | HIGH | Stop (brake) |

| IN3 | IN4 | Right Motor Action |
|-----|-----|-------------------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Stop (coast) |
| HIGH | HIGH | Stop (brake) |

### 3. DC Motors → L298N Motor Driver

The four motors are connected in two pairs:

| Motor Pair | L298N Terminal | Description |
|-----------|---------------|-------------|
| Left Front Motor | OUT1 (+) and OUT2 (−) | Left side, front wheel |
| Left Rear Motor | OUT1 (+) and OUT2 (−) | Left side, rear wheel (parallel with front) |
| Right Front Motor | OUT3 (+) and OUT4 (−) | Right side, front wheel |
| Right Rear Motor | OUT3 (+) and OUT4 (−) | Right side, rear wheel (parallel with front) |

> **Parallel Wiring:** Both left motors connect to the same output terminals (OUT1/OUT2).
> Both right motors connect to the same output terminals (OUT3/OUT4). This means both
> motors on each side spin at the same speed and direction.

**If a motor spins the wrong way:**
- **Hardware fix:** Swap the two wires of that motor at the terminal
- **Software fix:** Swap the HIGH/LOW values for that motor's IN pins in the code

### 4. Power Connections

| Connection | From | To | Notes |
|-----------|------|-----|-------|
| Motor Power (+) | Battery Pack (+) | L298N 12V Terminal | 7.4V–12V recommended |
| Motor Power (−) | Battery Pack (−) | L298N GND Terminal | Common ground |
| Arduino Power | L298N 5V Output | Arduino 5V Pin | Only if L298N 5V regulator is enabled |
| Common Ground | L298N GND | Arduino GND | **Essential — must be connected** |

> **Power Options:**
> - **Option A (Recommended for testing):** Power Arduino via USB cable, power motors via
>   battery pack through L298N. Connect GNDs together.
> - **Option B (Standalone operation):** Power both Arduino and motors from the battery
>   pack. Use L298N's built-in 5V regulator to power Arduino (keep the 5V jumper on L298N).

### 5. L298N Onboard 5V Regulator

The L298N module has a built-in 5V voltage regulator:

- **If motor supply voltage is 7V–12V:** The 5V regulator works. Keep the 5V jumper ON. You can use the L298N's 5V output to power the Arduino.
- **If motor supply voltage is > 12V:** Remove the 5V jumper to protect the regulator. Power Arduino separately via USB or a dedicated 5V supply.

## Complete Wiring Summary Table

| # | From | To | Purpose |
|---|------|-----|---------|
| 1 | HC-SR04 VCC | Arduino 5V | Sensor power |
| 2 | HC-SR04 GND | Arduino GND | Sensor ground |
| 3 | HC-SR04 TRIG | Arduino Pin 9 | Trigger pulse |
| 4 | HC-SR04 ECHO | Arduino Pin 10 | Echo measurement |
| 5 | L298N ENA | Arduino Pin 5 | Left motor speed (PWM) |
| 6 | L298N IN1 | Arduino Pin 2 | Left motor direction |
| 7 | L298N IN2 | Arduino Pin 3 | Left motor direction |
| 8 | L298N IN3 | Arduino Pin 4 | Right motor direction |
| 9 | L298N IN4 | Arduino Pin 7 | Right motor direction |
| 10 | L298N ENB | Arduino Pin 6 | Right motor speed (PWM) |
| 11 | Left Motors | L298N OUT1/OUT2 | Left motor pair |
| 12 | Right Motors | L298N OUT3/OUT4 | Right motor pair |
| 13 | Battery (+) | L298N 12V | Motor power supply |
| 14 | Battery (−) | L298N GND | Power ground |
| 15 | L298N GND | Arduino GND | Common ground |
| 16 | L298N 5V | Arduino 5V | Arduino power (optional) |

## Common Ground Explanation

> **Why is common ground important?**
>
> All electronic components must share a common ground (GND) reference point.
> Without it, voltage signals between the Arduino and L298N cannot be properly
> interpreted. The Arduino's HIGH (5V) and LOW (0V) signals are measured relative
> to GND. If the grounds are not connected, the L298N may not respond to Arduino
> commands, or may behave erratically.
>
> **Always connect:** Arduino GND ↔ L298N GND ↔ Battery (−)

## Wiring Diagram

> **Placeholder:** A visual circuit diagram should be created using Fritzing,
> Tinkercad Circuits, or similar tools and placed in the `images/` directory.
> See `circuit_diagram_placeholder.md` for details.
