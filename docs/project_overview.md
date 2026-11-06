# 📋 Project Overview — Obstacle-Avoiding Robot Car

## Reconstruction Notice

> **Important:** This project was originally completed during the author's first year
> of college. The original source code, circuit diagrams, and documentation are no
> longer available. This entire repository has been reconstructed in 2026 for academic
> documentation and portfolio purposes.
>
> - All code has been rewritten based on the original project requirements
> - Documentation has been created from scratch
> - No prototype photographs from the original project are available
> - Hardware testing results have NOT been fabricated

## Project Summary

| Field | Details |
|-------|---------|
| **Project Name** | Obstacle-Avoiding Robot Car |
| **Category** | Embedded Systems / Robotics / Arduino / Automation |
| **Platform** | Arduino Uno (ATmega328P) |
| **Language** | Arduino C/C++ |
| **Primary Sensor** | HC-SR04 Ultrasonic Distance Sensor |
| **Motor Driver** | L298N Dual H-Bridge |
| **Motors** | 4× DC Geared Motors |
| **Chassis** | Four-Wheel Robot Car Chassis |
| **License** | MIT |

## Objective

To design and build an **autonomous four-wheel robot car** that:

1. Continuously measures the distance to objects in its path using an ultrasonic sensor
2. Moves forward when the path is clear
3. Detects obstacles within a configurable distance threshold
4. Automatically stops and executes an avoidance maneuver (reverse + turn)
5. Resumes forward movement after clearing the obstacle

The robot operates without any human intervention once powered on.

## Scope

### In Scope
- Autonomous forward navigation
- Ultrasonic obstacle detection (front-facing)
- Motor speed control via PWM
- Obstacle avoidance (stop → reverse → turn → resume)
- Serial monitor debugging
- Configurable parameters (speed, distance threshold, timing)

### Out of Scope (Current Version)
- Multi-directional obstacle scanning (e.g., servo-mounted sensor)
- Remote control capability (Bluetooth/WiFi)
- Line following
- GPS navigation
- Advanced path planning algorithms
- Mobile app integration

## Target Audience

This project is designed for:
- First-year engineering students studying embedded systems
- Beginners learning Arduino programming
- Students building robotics projects for academic submissions
- Anyone preparing for embedded systems or IoT job interviews

## Key Learning Outcomes

By studying this project, you will understand:

1. **Microcontroller Programming** — Writing structured Arduino code
2. **Sensor Integration** — Interfacing ultrasonic sensors with Arduino
3. **Motor Control** — Using H-bridge motor drivers for DC motors
4. **PWM Speed Control** — Controlling motor speed with pulse-width modulation
5. **Autonomous Decision Making** — Implementing sensor-based navigation logic
6. **Embedded Systems Design** — Connecting and powering multiple components
7. **Technical Documentation** — Professional project documentation practices

## Document Map

| Document | Location | Description |
|----------|----------|-------------|
| Source Code | [`code/obstacle_avoiding_robot/obstacle_avoiding_robot.ino`](../code/obstacle_avoiding_robot/obstacle_avoiding_robot.ino) | Main Arduino sketch |
| Working Principle | [`docs/working_principle.md`](working_principle.md) | How the system works |
| Hardware Requirements | [`docs/hardware_requirements.md`](hardware_requirements.md) | Component list and specs |
| Software Requirements | [`docs/software_requirements.md`](software_requirements.md) | IDE and library setup |
| Wiring Guide | [`circuit/wiring_guide.md`](../circuit/wiring_guide.md) | Connection instructions |
| Pin Configuration | [`circuit/pin_configuration.md`](../circuit/pin_configuration.md) | Pin mapping tables |
| Installation Guide | [`docs/installation_guide.md`](installation_guide.md) | Setup instructions |
| Troubleshooting | [`docs/troubleshooting.md`](troubleshooting.md) | Common issues and fixes |
| Testing Plan | [`testing/test_plan.md`](../testing/test_plan.md) | Test cases and results |
| Future Improvements | [`docs/future_improvements.md`](future_improvements.md) | Planned enhancements |
