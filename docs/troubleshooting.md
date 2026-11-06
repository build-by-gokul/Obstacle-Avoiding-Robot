# 🔍 Troubleshooting Guide — Obstacle-Avoiding Robot Car

This guide covers common issues and their solutions. Work through the relevant section methodically — most problems have simple fixes.

## Table of Contents

- [Arduino IDE Issues](#arduino-ide-issues)
- [Ultrasonic Sensor Issues](#ultrasonic-sensor-issues)
- [Motor Issues](#motor-issues)
- [Power Issues](#power-issues)
- [Behavioral Issues](#behavioral-issues)
- [Serial Monitor Issues](#serial-monitor-issues)

---

## Arduino IDE Issues

### Problem: Code won't compile
**Symptoms:** Error messages in the Arduino IDE output panel.

**Solutions:**
1. Verify **Tools → Board** is set to "Arduino Uno"
2. Check for typos if you modified the code
3. Ensure all curly braces `{}` are properly matched
4. Make sure you're using Arduino IDE 1.8.x or 2.x
5. Try restarting the Arduino IDE

### Problem: Upload fails ("avrdude" error)
**Symptoms:** Error messages mentioning "avrdude", "sync", or "not in sync".

**Solutions:**
1. Check that the USB cable is firmly connected
2. Verify **Tools → Port** shows the correct COM port
3. Try a different USB cable (some cables are power-only, with no data lines)
4. Try a different USB port on your computer
5. Press the reset button on the Arduino and try uploading again immediately
6. Close any other programs that might be using the COM port (e.g., other serial monitors)
7. On clone boards: install the CH340 or CP2102 driver

### Problem: Arduino not detected by computer
**Symptoms:** No COM port appears in Tools → Port.

**Solutions:**
1. Try a different USB cable
2. Try a different USB port
3. Check Device Manager (Windows) for unknown devices
4. Install the correct USB driver (CH340 for most clone boards)
5. Check if the Arduino's power LED lights up — if not, the board may be damaged

---

## Ultrasonic Sensor Issues

### Problem: Sensor always reads 0 cm
**Symptoms:** Serial monitor shows `Distance: 0 cm` or `Echo timeout`.

**Solutions:**
1. Verify VCC is connected to Arduino 5V (not 3.3V)
2. Verify GND is connected to Arduino GND
3. Check TRIG wire is connected to Pin 9
4. Check ECHO wire is connected to Pin 10
5. Ensure TRIG and ECHO wires are not swapped
6. Try a different HC-SR04 sensor (the module may be defective)
7. Test the sensor separately with a simple sketch

### Problem: Sensor readings are erratic or noisy
**Symptoms:** Distance values jump randomly between readings.

**Solutions:**
1. Ensure all connections are secure (no loose wires)
2. Add a small delay between readings (at least 50ms)
3. Average multiple readings for stability:
   ```c
   int avgDistance = 0;
   for (int i = 0; i < 5; i++) {
     avgDistance += readDistance();
     delay(10);
   }
   avgDistance /= 5;
   ```
4. Check for electrical interference from the motors
5. Keep sensor wires away from motor wires

### Problem: Sensor reads maximum range constantly
**Symptoms:** Distance always shows ~400 cm.

**Solutions:**
1. Check that there are objects within range for the sensor to detect
2. Verify the sensor is not pointing at a sound-absorbing surface (e.g., thick fabric)
3. Check that the sensor's transmitter and receiver are not obstructed
4. Ensure the sensor is mounted level and facing forward

---

## Motor Issues

### Problem: Motors don't spin at all
**Symptoms:** No motor movement when code is running.

**Solutions:**
1. Check battery pack — is it charged and connected?
2. Verify battery (+) is connected to L298N 12V terminal
3. Verify battery (−) is connected to L298N GND terminal
4. Check that the L298N power LED is on
5. Verify ENA/ENB jumpers are removed (we control speed via Arduino PWM)
6. Check that Arduino pins 5 and 6 are connected to ENA and ENB
7. Verify IN1–IN4 wires are connected correctly
8. Try increasing `MOTOR_SPEED` to 255 for testing
9. Test each motor individually by connecting directly to the battery (briefly)

### Problem: Motors spin in the wrong direction
**Symptoms:** Robot moves backward instead of forward, or turns the wrong way.

**Solutions:**

**Hardware Fix (easier):**
- Swap the two wires of the problematic motor at the L298N output terminal

**Software Fix:**
- In the `moveForward()` function, swap HIGH and LOW for the affected motor:
  ```c
  // If LEFT motors go backward, change:
  digitalWrite(LEFT_IN1, HIGH);  // was HIGH → change to LOW
  digitalWrite(LEFT_IN2, LOW);   // was LOW  → change to HIGH
  ```

### Problem: Only one side of motors works
**Symptoms:** Robot spins in circles instead of going straight.

**Solutions:**
1. Check that both motor pairs are wired to the L298N (OUT1/2 and OUT3/4)
2. Verify both ENA and ENB are connected to Arduino PWM pins
3. Check that IN1–IN4 are all properly connected
4. One motor pair may be defective — test individually

### Problem: Motors are very slow
**Symptoms:** Motors barely turn or move sluggishly.

**Solutions:**
1. Check battery voltage — batteries may be depleted
2. Increase `MOTOR_SPEED` value (try 220 or 255)
3. Verify ENA/ENB connections — motors run at full speed only with PWM
4. L298N has ~2V voltage drop — with 6V input, motors only get ~4V. Use 7.4V+ battery
5. Check for mechanical friction in the chassis or wheels

---

## Power Issues

### Problem: Arduino resets when motors start
**Symptoms:** Arduino restarts (serial monitor shows init messages again) when motors activate.

**Solutions:**
1. **Separate power supplies:** Power Arduino via USB, motors via battery through L298N
2. Add a large capacitor (100µF–470µF) across the motor power supply terminals
3. Use a battery with higher capacity
4. Ensure common ground is connected

### Problem: Short battery life
**Symptoms:** Robot stops working after a short time.

**Solutions:**
1. Use a higher-capacity battery (2000+ mAh recommended)
2. Reduce motor speed when full speed isn't needed
3. Use rechargeable Li-ion batteries instead of alkaline
4. Check for short circuits causing excess current draw

### Problem: L298N gets very hot
**Symptoms:** The L298N heatsink becomes uncomfortably hot.

**Solutions:**
1. This is partially normal — the L298N has ~2V drop and dissipates heat
2. Ensure motors are not stalled (stuck against an obstacle continuously)
3. Verify motor current is within the 2A-per-channel rating
4. Add a small heatsink or fan if operating continuously
5. Consider upgrading to a TB6612FNG driver (more efficient, less heat)

---

## Behavioral Issues

### Problem: Robot doesn't avoid obstacles
**Symptoms:** Robot drives into objects without stopping.

**Solutions:**
1. Open Serial Monitor — check if distance readings are being displayed
2. Verify `OBSTACLE_THRESHOLD_CM` is set appropriately (default: 25 cm)
3. Increase the threshold if the robot's speed doesn't allow it to stop in time
4. Check sensor orientation — is it facing forward?
5. Check that the obstacle is within the sensor's 15° beam angle
6. Some surfaces (glass, thin poles) may not reflect ultrasonic waves well

### Problem: Robot gets stuck in corners
**Symptoms:** Robot repeatedly turns back and forth in a corner.

**Solutions:**
1. The alternating turn direction should help, but corners can still be challenging
2. Increase `TURN_DURATION_MS` to make wider turns (try 600–800ms)
3. Increase `BACKUP_DURATION_MS` to reverse further before turning
4. Consider adding a servo-mounted sensor for scanning left/right (future improvement)

### Problem: Robot doesn't go straight
**Symptoms:** Robot veers to one side during forward movement.

**Solutions:**
1. This is common — motors have manufacturing variations
2. Adjust individual motor speeds:
   ```c
   // If robot veers right, slow down the left motor slightly:
   analogWrite(LEFT_EN, 170);   // slightly slower
   analogWrite(RIGHT_EN, 180);  // normal speed
   ```
3. Check that all four wheels are properly aligned and make good ground contact
4. Ensure the chassis is assembled symmetrically

---

## Serial Monitor Issues

### Problem: Garbled text in Serial Monitor
**Symptoms:** Random characters instead of readable text.

**Solutions:**
1. Set the baud rate dropdown to **9600** in the Serial Monitor
2. Ensure `Serial.begin(9600)` is in your code
3. Try closing and reopening the Serial Monitor

### Problem: No output in Serial Monitor
**Symptoms:** Serial Monitor is blank.

**Solutions:**
1. Verify the correct COM port is selected
2. Press the reset button on the Arduino
3. Check that the USB cable supports data (not power-only)
4. Ensure `Serial.begin(9600)` is in the `setup()` function
5. Try closing and reopening the Serial Monitor

---

## Still Having Issues?

If none of the above solutions work:

1. **Simplify:** Test each component individually
   - Sensor only: Upload a simple sketch that just reads and prints distance
   - Motors only: Upload a sketch that just spins motors forward/backward
2. **Inspect:** Look for loose connections, broken wires, or bent pins
3. **Replace:** Try swapping suspected faulty components
4. **Ask:** Post on the [Arduino Forum](https://forum.arduino.cc/) with:
   - Your code
   - Your wiring setup
   - The exact error or unexpected behavior
   - Photographs of your wiring
