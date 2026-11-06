# ⚙️ Working Principle — Obstacle-Avoiding Robot Car

This document explains the engineering concepts behind the obstacle-avoiding robot car. It is written for beginner electronics students and those preparing for technical interviews.

## Table of Contents

- [What is an Autonomous Robot?](#what-is-an-autonomous-robot)
- [System Architecture](#system-architecture)
- [Ultrasonic Sensing](#ultrasonic-sensing)
- [How HC-SR04 Calculates Distance](#how-hc-sr04-calculates-distance)
- [What is an L298N Motor Driver?](#what-is-an-l298n-motor-driver)
- [Why is a Motor Driver Necessary?](#why-is-a-motor-driver-necessary)
- [How Arduino Controls Motor Direction](#how-arduino-controls-motor-direction)
- [PWM Speed Control](#pwm-speed-control)
- [How Obstacle Avoidance Works](#how-obstacle-avoidance-works)
- [Complete Operation Flow](#complete-operation-flow)

## What is an Autonomous Robot?

An **autonomous robot** is a machine that can perform tasks and make decisions without continuous human control. It uses **sensors** to perceive its environment and **actuators** (motors) to take action based on programmed logic.

Key characteristics of an autonomous robot:
- **Self-directed:** Operates without remote control or human commands
- **Sensor-driven:** Uses sensors to gather environmental data
- **Decision-making:** Processes sensor data to decide what action to take
- **Reactive:** Responds to changes in its environment in real time

Our obstacle-avoiding robot is a basic autonomous system. It uses one sensor (HC-SR04) to detect obstacles and four motors to navigate around them.

## System Architecture

The robot follows a classic **Sense → Think → Act** loop:

```
┌─────────────────────────────────────────────────────────┐
│                    SENSE → THINK → ACT                  │
│                                                         │
│   ┌──────────┐    ┌──────────────┐    ┌──────────────┐  │
│   │  HC-SR04  │───→│  Arduino Uno │───→│  L298N Motor │  │
│   │  Sensor   │    │  (Decision   │    │  Driver      │  │
│   │ (Sensing) │    │   Logic)     │    │ (Actuation)  │  │
│   └──────────┘    └──────────────┘    └──────┬───────┘  │
│                                              │          │
│                                        ┌─────┴─────┐   │
│                                        │  4× DC     │   │
│                                        │  Motors    │   │
│                                        └───────────┘   │
└─────────────────────────────────────────────────────────┘
```

1. **Sense:** The HC-SR04 ultrasonic sensor measures the distance to the nearest object
2. **Think:** The Arduino Uno processes the distance reading and decides what to do
3. **Act:** The L298N motor driver controls the four DC motors to move, stop, or turn

## Ultrasonic Sensing

**Ultrasonic sensing** uses high-frequency sound waves (above 20kHz — beyond human hearing) to measure distance. It works on the same principle as **sonar** used by submarines and bats.

### How it works:
1. A **transmitter** emits a burst of ultrasonic sound waves
2. The sound waves travel through the air
3. When they hit an object, they **reflect** back (echo)
4. A **receiver** detects the returning echo
5. The **time** between emission and reception is used to calculate distance

### Why ultrasonic?
- Works in any lighting condition (unlike optical sensors)
- No physical contact required (unlike bump sensors)
- Reasonable range (2–400 cm) for indoor navigation
- Inexpensive and easy to interface with Arduino
- Low power consumption

## How HC-SR04 Calculates Distance

The HC-SR04 sensor uses the following process:

### Step-by-Step Process

1. **Trigger:** The Arduino sends a 10µs HIGH pulse to the TRIG pin
2. **Transmit:** The HC-SR04 automatically sends 8 pulses at 40kHz
3. **Listen:** The ECHO pin goes HIGH while waiting for the reflection
4. **Receive:** When the echo returns, the ECHO pin goes LOW
5. **Calculate:** The duration of the ECHO HIGH pulse = round-trip time

### Distance Formula

The speed of sound in air at room temperature (~20°C) is approximately **343 m/s** or **0.0343 cm/µs**.

Since the sound travels to the object AND back (round trip), the distance is:

```
Distance (cm) = (Duration in µs × 0.0343) / 2
```

Simplifying:

```
Distance (cm) = Duration (µs) / 58.2
```

In our code, we use integer division for efficiency:

```c
int distance = duration / 58;
```

### Example Calculation

If the ECHO pulse duration is 1160µs:
```
Distance = 1160 / 58 = 20 cm
```

The object is approximately 20 cm away.

### Sensor Limitations

| Limitation | Details |
|-----------|---------|
| Minimum range | ~2 cm (closer objects may not be detected) |
| Maximum range | ~400 cm (signal weakens beyond this) |
| Beam angle | ~15° cone — cannot detect objects outside this cone |
| Soft surfaces | Sound-absorbing materials may not reflect well |
| Temperature | Speed of sound varies with temperature (±0.6 m/s per °C) |
| Angled surfaces | Surfaces at steep angles may deflect the echo away |

## What is an L298N Motor Driver?

The **L298N** is a **Dual H-Bridge Motor Driver** integrated circuit (IC). It allows you to control:
- The **direction** (forward/reverse) of two DC motors independently
- The **speed** of each motor using PWM (Pulse Width Modulation)

### What is an H-Bridge?

An **H-Bridge** is a circuit arrangement of four switches (transistors) that controls the direction of current flow through a motor:

```
    +V ──────┬──────────┬────── +V
             │          │
           [S1]      [S2]
             │          │
             ├──[MOTOR]─┤
             │          │
           [S3]      [S4]
             │          │
    GND ─────┴──────────┴────── GND
```

- **S1 + S4 ON:** Current flows left-to-right → Motor spins **forward**
- **S2 + S3 ON:** Current flows right-to-left → Motor spins **reverse**
- **All OFF:** Motor **stops** (coasts)
- **S1 + S2 ON or S3 + S4 ON:** Motor **brakes** (short-circuit braking)

The L298N contains **two** H-bridges, so it can control two motors (or two pairs of motors) independently.

### L298N Key Specifications

| Parameter | Value |
|-----------|-------|
| Logic voltage | 5V |
| Motor supply voltage | 5V – 35V |
| Max current per channel | 2A |
| Peak current per channel | 3A |
| Built-in 5V regulator | Yes (for motor supply ≤ 12V) |
| Control inputs | IN1, IN2, IN3, IN4 |
| Enable pins | ENA (Motor A), ENB (Motor B) |

## Why is a Motor Driver Necessary?

> **Critical Concept:** You must NEVER connect DC motors directly to Arduino GPIO pins.

### The Problem
| Parameter | Arduino GPIO Pin | DC Geared Motor |
|-----------|-----------------|-----------------|
| Max current | ~40 mA | 100–300+ mA |
| Voltage | 5V (logic level) | 3–12V (depending on motor) |

If you connect a motor directly to an Arduino pin:
1. The motor will draw too much current
2. The Arduino pin or entire board may be **permanently damaged**
3. The motor may not spin at all (insufficient current)

### The Solution
A motor driver like the L298N acts as an **intermediary**:
- It receives **low-current control signals** (5V, ~mA) from the Arduino
- It switches **high-current power** (from the battery) to the motors
- Think of it as a **power relay** controlled by the Arduino

```
Arduino (Signal) → L298N (Amplifies) → Motor (Moves)
   5V, ~1mA          Battery Power        3-12V, 200mA+
```

## How Arduino Controls Motor Direction

The Arduino controls each motor's direction by setting the IN pins HIGH or LOW:

### Left Motors (Motor A)
| IN1 | IN2 | Action |
|-----|-----|--------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Stop (coast) |

### Right Motors (Motor B)
| IN3 | IN4 | Action |
|-----|-----|--------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Stop (coast) |

### Robot Movement Combinations
| Left Motors | Right Motors | Robot Action |
|------------|-------------|-------------|
| Forward | Forward | Move Forward |
| Reverse | Reverse | Move Backward |
| Reverse | Forward | Turn Left |
| Forward | Reverse | Turn Right |
| Stop | Stop | Stop |

## PWM Speed Control

**Pulse Width Modulation (PWM)** controls motor speed by rapidly switching the power on and off.

### How PWM Works
- The Arduino outputs a square wave signal
- **Duty cycle** = percentage of time the signal is HIGH
- Higher duty cycle = more average power = faster motor speed

| PWM Value | Duty Cycle | Motor Speed |
|-----------|-----------|-------------|
| 0 | 0% | Stopped |
| 64 | 25% | Slow |
| 128 | 50% | Medium |
| 191 | 75% | Fast |
| 255 | 100% | Full speed |

In our code:
```c
analogWrite(LEFT_EN, 180);   // ~70% speed
analogWrite(RIGHT_EN, 180);  // ~70% speed
```

The Arduino Uno's PWM frequency on pins 5 and 6 is approximately **976 Hz** — fast enough that the motor appears to run smoothly rather than pulsing.

## How Obstacle Avoidance Works

Our robot uses a simple but effective avoidance strategy:

### Algorithm

```
LOOP:
  1. Measure distance to nearest object
  2. If distance > threshold (25 cm):
       → Continue moving forward
  3. If distance ≤ threshold (25 cm):
       → Stop immediately
       → Reverse for 300ms
       → Turn (alternating left/right) for 400ms
       → Check new path
       → If still blocked, turn opposite direction
       → Resume forward movement
  4. Repeat from step 1
```

### Why Alternating Turns?

If the robot always turns in the same direction (e.g., always right), it can get stuck in a corner — turning right, hitting a wall, turning right again, hitting another wall, and repeating.

By alternating between left and right turns, the robot explores more directions and is less likely to get trapped.

## Complete Operation Flow

```
Power On
    │
    ▼
Initialize (setup)
    │ - Configure pins
    │ - Stop motors
    │ - Start serial monitor
    │
    ▼
┌─→ Read Distance ◄────────────────────┐
│       │                               │
│       ▼                               │
│   Valid Reading?                       │
│       │                               │
│    NO ├──→ Stop motors ──→ Wait ──────┤
│       │                               │
│   YES ▼                               │
│   Distance > 25 cm?                   │
│       │                               │
│   YES ├──→ Move Forward ─────────────┤
│       │                               │
│    NO ▼                               │
│   OBSTACLE DETECTED                   │
│       │                               │
│       ├──→ Stop                       │
│       ├──→ Reverse (300ms)            │
│       ├──→ Turn Left or Right (400ms) │
│       ├──→ Check new path             │
│       │                               │
│       └──→ Resume ────────────────────┘
│
└─── (loop repeats continuously)
```
