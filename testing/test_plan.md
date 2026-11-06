# 🧪 Test Plan — Obstacle-Avoiding Robot Car

> **Reconstruction Notice:** This test plan has been created in 2026 as part of the
> project reconstruction. All tests are currently marked as **NOT TESTED**. Test results
> should be filled in only after physically conducting each test with the assembled hardware.

## Testing Objectives

1. Verify all hardware components function correctly
2. Confirm the ultrasonic sensor provides accurate distance measurements
3. Validate motor direction and speed control
4. Test the obstacle avoidance behavior end-to-end
5. Verify safe handling of edge cases and error conditions

## Test Environment

| Parameter | Requirement |
|-----------|-------------|
| Surface | Flat, smooth surface (e.g., table, tile floor) |
| Space | Minimum 2m × 2m clear area |
| Obstacles | Solid, flat-surfaced objects (e.g., boxes, books, walls) |
| Power | Fully charged battery pack |
| Monitoring | Arduino connected to computer via USB for serial monitor |

## Test Cases

### Category 1: Hardware Verification

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| HW-01 | Arduino Uno powers on via USB | Power LED lights up, board detected on COM port | — | NOT TESTED |
| HW-02 | Arduino Uno powers on via battery through L298N | Power LED lights up | — | NOT TESTED |
| HW-03 | L298N power LED activates with battery connected | Red LED on L298N module lights up | — | NOT TESTED |
| HW-04 | HC-SR04 sensor receives power | No visible indicator, but sensor functions in tests below | — | NOT TESTED |

### Category 2: Ultrasonic Sensor Tests

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| US-01 | Sensor reads distance to a wall at 10 cm | Serial monitor shows ~10 cm (±2 cm) | — | NOT TESTED |
| US-02 | Sensor reads distance to a wall at 25 cm | Serial monitor shows ~25 cm (±3 cm) | — | NOT TESTED |
| US-03 | Sensor reads distance to a wall at 50 cm | Serial monitor shows ~50 cm (±5 cm) | — | NOT TESTED |
| US-04 | Sensor reads distance to a wall at 100 cm | Serial monitor shows ~100 cm (±10 cm) | — | NOT TESTED |
| US-05 | No object in front of sensor (open space) | Serial monitor shows 0 or >400 cm, warning message displayed | — | NOT TESTED |
| US-06 | Object closer than 2 cm | Sensor may return 0 or unreliable value; robot stops safely | — | NOT TESTED |
| US-07 | Sensor reads distance to a soft object (pillow, fabric) | Reading may be inaccurate — verify behavior | — | NOT TESTED |

### Category 3: Motor Direction Tests

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| MT-01 | Call moveForward() — observe left motors | Left motors spin forward (toward front of robot) | — | NOT TESTED |
| MT-02 | Call moveForward() — observe right motors | Right motors spin forward (toward front of robot) | — | NOT TESTED |
| MT-03 | Call moveBackward() — observe all motors | All motors spin in reverse | — | NOT TESTED |
| MT-04 | Call turnLeft() — observe motor directions | Left motors reverse, right motors forward | — | NOT TESTED |
| MT-05 | Call turnRight() — observe motor directions | Left motors forward, right motors reverse | — | NOT TESTED |
| MT-06 | Call stopMotors() | All motors stop immediately | — | NOT TESTED |

### Category 4: Speed Control Tests

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| SP-01 | Set MOTOR_SPEED to 100 | Motors spin noticeably slower than default | — | NOT TESTED |
| SP-02 | Set MOTOR_SPEED to 255 | Motors spin at maximum speed | — | NOT TESTED |
| SP-03 | Set MOTOR_SPEED to 0 | Motors do not spin | — | NOT TESTED |

### Category 5: Obstacle Avoidance Tests

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| OA-01 | Place obstacle 50 cm in front, start robot | Robot moves forward toward obstacle | — | NOT TESTED |
| OA-02 | Robot approaches obstacle within 25 cm | Robot stops, serial shows "Obstacle detected!" | — | NOT TESTED |
| OA-03 | After stopping, robot executes avoidance | Robot reverses, then turns left or right | — | NOT TESTED |
| OA-04 | After avoidance, path is clear | Robot resumes forward movement | — | NOT TESTED |
| OA-05 | Obstacle on both sides (narrow corridor) | Robot attempts both turn directions, may require manual intervention | — | NOT TESTED |
| OA-06 | Multiple obstacles in sequence | Robot avoids each obstacle in turn | — | NOT TESTED |

### Category 6: Emergency and Edge Cases

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| EC-01 | Disconnect sensor during operation | Robot stops (invalid reading triggers safety stop) | — | NOT TESTED |
| EC-02 | Block sensor with hand directly | Robot detects very close obstacle and avoids | — | NOT TESTED |
| EC-03 | Operate on inclined surface (~5°) | Robot should still detect obstacles, may move unevenly | — | NOT TESTED |
| EC-04 | Low battery operation | Robot slows down; should not behave erratically | — | NOT TESTED |

### Category 7: Serial Monitor and Debugging

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| SM-01 | Open serial monitor at 9600 baud | Initialization messages display correctly | — | NOT TESTED |
| SM-02 | Observe continuous operation | Distance readings update every ~50ms | — | NOT TESTED |
| SM-03 | Trigger obstacle avoidance | Action messages ("Obstacle detected!", "Turning LEFT/RIGHT") display | — | NOT TESTED |
| SM-04 | Simulate invalid reading | Warning message displays, motors stop | — | NOT TESTED |

### Category 8: Power and Battery Tests

| Test ID | Test Description | Expected Result | Actual Result | Status |
|---------|-----------------|-----------------|---------------|--------|
| PW-01 | Measure battery voltage before test | Voltage is within expected range (7.4V for 2S Li-ion) | — | NOT TESTED |
| PW-02 | Run robot for 30 minutes continuously | Robot operates consistently without resets | — | NOT TESTED |
| PW-03 | Check L298N temperature after 10 min | Warm but not burning hot | — | NOT TESTED |
| PW-04 | Arduino does not reset when motors start | Serial monitor does not show re-initialization | — | NOT TESTED |

## Test Summary

| Category | Total Tests | Passed | Failed | Not Tested |
|----------|------------|--------|--------|------------|
| Hardware Verification | 4 | 0 | 0 | 4 |
| Ultrasonic Sensor | 7 | 0 | 0 | 7 |
| Motor Direction | 6 | 0 | 0 | 6 |
| Speed Control | 3 | 0 | 0 | 3 |
| Obstacle Avoidance | 6 | 0 | 0 | 6 |
| Emergency/Edge Cases | 4 | 0 | 0 | 4 |
| Serial Monitor | 4 | 0 | 0 | 4 |
| Power/Battery | 4 | 0 | 0 | 4 |
| **TOTAL** | **38** | **0** | **0** | **38** |

> ⚠️ **All 38 tests are currently NOT TESTED.** Results should be filled in only
> after physically conducting each test with the assembled hardware. Do not
> fabricate or assume test results.

## How to Record Test Results

1. Assemble the robot completely (see [Installation Guide](../docs/installation_guide.md))
2. Conduct each test in order
3. Fill in the "Actual Result" column with what you observed
4. Update the "Status" column: `PASS`, `FAIL`, or `SKIP` (with reason)
5. Update the Test Summary table with counts
6. If a test fails, document the issue and any fixes applied
7. Re-test failed tests after applying fixes
