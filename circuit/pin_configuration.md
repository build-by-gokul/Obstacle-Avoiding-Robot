# 📌 Pin Configuration — Obstacle-Avoiding Robot Car

> **Reconstruction Notice:** This pin configuration has been reconstructed in 2026.
> Verify against your actual wiring before powering on.

## Arduino Uno Pin Map

### Digital Pins Used

| Arduino Pin | Connected To | Direction | Type | Purpose |
|------------|-------------|-----------|------|---------|
| Pin 2 | L298N IN1 | OUTPUT | Digital | Left motors — direction control A |
| Pin 3 | L298N IN2 | OUTPUT | Digital | Left motors — direction control B |
| Pin 4 | L298N IN3 | OUTPUT | Digital | Right motors — direction control A |
| Pin 5 | L298N ENA | OUTPUT | PWM | Left motors — speed control |
| Pin 6 | L298N ENB | OUTPUT | PWM | Right motors — speed control |
| Pin 7 | L298N IN4 | OUTPUT | Digital | Right motors — direction control B |
| Pin 9 | HC-SR04 TRIG | OUTPUT | Digital | Ultrasonic sensor — trigger pulse |
| Pin 10 | HC-SR04 ECHO | INPUT | Digital | Ultrasonic sensor — echo receive |

### PWM Pin Requirements

The motor speed control pins (ENA, ENB) **must** be connected to PWM-capable pins on the Arduino Uno. PWM pins on the Uno are: **3, 5, 6, 9, 10, 11**.

In this configuration:
- **Pin 5** (PWM) → ENA (left motor speed)
- **Pin 6** (PWM) → ENB (right motor speed)

> **Note:** Pins 5 and 6 use Timer 0, which also controls `millis()` and `delay()`.
> This is acceptable for basic motor control but may cause slight timing variations
> at very low PWM values. For most applications, this is not noticeable.

### Unused Arduino Uno Pins

| Pin | Status | Available For |
|-----|--------|--------------|
| Pin 0 (RX) | Reserved | Serial communication |
| Pin 1 (TX) | Reserved | Serial communication |
| Pin 8 | Free | Future expansion (e.g., buzzer) |
| Pin 11 | Free | Future expansion (e.g., servo signal) |
| Pin 12 | Free | Future expansion (e.g., IR sensor) |
| Pin 13 | Free | Built-in LED / future expansion |
| A0–A5 | Free | Analog sensors / future expansion |

### Power Pins Used

| Arduino Pin | Connected To | Purpose |
|------------|-------------|---------|
| 5V | HC-SR04 VCC | Power supply for ultrasonic sensor |
| GND | HC-SR04 GND, L298N GND | Common ground reference |
| VIN or 5V | L298N 5V out (optional) | Arduino power from motor driver |

## L298N Motor Driver Pin Map

### Control Pins (from Arduino)

| L298N Pin | Arduino Pin | Function |
|-----------|------------|----------|
| ENA | Pin 5 (PWM) | Motor A (left) speed — 0 to 255 |
| IN1 | Pin 2 | Motor A (left) direction input 1 |
| IN2 | Pin 3 | Motor A (left) direction input 2 |
| IN3 | Pin 4 | Motor B (right) direction input 1 |
| IN4 | Pin 7 | Motor B (right) direction input 2 |
| ENB | Pin 6 (PWM) | Motor B (right) speed — 0 to 255 |

### Output Terminals (to Motors)

| L298N Terminal | Connected To |
|---------------|-------------|
| OUT1 | Left Front Motor (+), Left Rear Motor (+) |
| OUT2 | Left Front Motor (−), Left Rear Motor (−) |
| OUT3 | Right Front Motor (+), Right Rear Motor (+) |
| OUT4 | Right Front Motor (−), Right Rear Motor (−) |

### Power Terminals

| L298N Terminal | Connected To | Voltage Range |
|---------------|-------------|---------------|
| 12V (VS) | Battery Pack (+) | 7.4V – 12V |
| GND | Battery Pack (−), Arduino GND | 0V (reference) |
| 5V (VSS) | Arduino 5V (optional) | 5V regulated output |

## HC-SR04 Ultrasonic Sensor Pin Map

| HC-SR04 Pin | Arduino Pin | Description |
|-------------|------------|-------------|
| VCC | 5V | Power supply (5V DC) |
| TRIG | Pin 9 | Trigger input — 10µs pulse starts measurement |
| ECHO | Pin 10 | Echo output — HIGH duration = round-trip time |
| GND | GND | Ground reference |

### Sensor Specifications

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 5V DC |
| Operating Current | 15mA |
| Measuring Range | 2 cm – 400 cm |
| Measuring Angle | 15° cone |
| Trigger Pulse Width | 10µs (minimum) |
| Resolution | ~0.3 cm |

## Quick Reference Diagram (Text)

```
Arduino Uno
┌──────────────────────┐
│                 Pin 2 │──── L298N IN1  (Left Dir A)
│                 Pin 3 │──── L298N IN2  (Left Dir B)
│                 Pin 4 │──── L298N IN3  (Right Dir A)
│            PWM  Pin 5 │──── L298N ENA  (Left Speed)
│            PWM  Pin 6 │──── L298N ENB  (Right Speed)
│                 Pin 7 │──── L298N IN4  (Right Dir B)
│                 Pin 9 │──── HC-SR04 TRIG
│                Pin 10 │──── HC-SR04 ECHO
│                       │
│                   5V  │──── HC-SR04 VCC
│                  GND  │──── HC-SR04 GND ──── L298N GND
└──────────────────────┘
```
