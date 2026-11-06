/*
 * =============================================================================
 * OBSTACLE-AVOIDING ROBOT CAR
 * =============================================================================
 * 
 * Description:
 *   Autonomous four-wheel robot car that detects obstacles using an HC-SR04
 *   ultrasonic sensor and avoids collisions by controlling four DC motors
 *   through an L298N dual H-bridge motor driver.
 * 
 * Hardware:
 *   - Arduino Uno
 *   - HC-SR04 Ultrasonic Distance Sensor
 *   - L298N Dual H-Bridge Motor Driver
 *   - 4x DC Geared Motors (3-6V)
 *   - 4-Wheel Robot Chassis
 *   - Battery Pack (7.4V–12V recommended)
 * 
 * Reconstruction Note:
 *   This code has been reconstructed in 2026 for documentation purposes.
 *   The original source code from the first-year college project is no longer
 *   available. This version faithfully recreates the intended functionality.
 *   It has NOT been physically tested on hardware at the time of writing.
 * 
 * Author:  [Your Name]
 * Date:    2026
 * License: MIT
 * 
 * =============================================================================
 */

// =============================================================================
// PIN CONFIGURATION
// =============================================================================
// Centralized pin definitions — change these if your wiring differs.

// HC-SR04 Ultrasonic Sensor Pins
const int TRIG_PIN = 9;   // Trigger pin (OUTPUT) — sends ultrasonic pulse
const int ECHO_PIN = 10;  // Echo pin (INPUT) — receives reflected pulse

// L298N Motor Driver Pins — Left Motors (Motor A)
const int LEFT_EN  = 5;   // ENA — PWM speed control for left motors
const int LEFT_IN1 = 2;   // IN1 — direction control for left motors
const int LEFT_IN2 = 3;   // IN2 — direction control for left motors

// L298N Motor Driver Pins — Right Motors (Motor B)
const int RIGHT_EN = 6;   // ENB — PWM speed control for right motors
const int RIGHT_IN3 = 4;  // IN3 — direction control for right motors
const int RIGHT_IN4 = 7;  // IN4 — direction control for right motors

// =============================================================================
// CONFIGURABLE PARAMETERS
// =============================================================================
// Adjust these values to tune the robot's behavior.

const int OBSTACLE_THRESHOLD_CM = 25;    // Distance (cm) to trigger obstacle avoidance
const int MOTOR_SPEED           = 180;   // Motor speed (0–255, PWM duty cycle)
const int TURN_SPEED            = 200;   // Speed during turning maneuvers
const int TURN_DURATION_MS      = 400;   // Duration of a turn (milliseconds)
const int BACKUP_DURATION_MS    = 300;   // Duration of reverse before turning (ms)
const int SENSOR_DELAY_MS       = 50;    // Delay between sensor readings (ms)
const long ULTRASONIC_TIMEOUT   = 25000; // Timeout for echo pulse (microseconds)
                                          // ~425 cm max range at speed of sound

// =============================================================================
// GLOBAL VARIABLES
// =============================================================================
long duration;       // Duration of the ultrasonic echo pulse (microseconds)
int  distance;       // Calculated distance to obstacle (centimeters)
bool lastTurnRight = false;  // Alternates turn direction for better coverage

// =============================================================================
// SETUP — Runs once when Arduino powers on or resets
// =============================================================================
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println(F("==========================================="));
  Serial.println(F("  OBSTACLE-AVOIDING ROBOT CAR"));
  Serial.println(F("  Initializing..."));
  Serial.println(F("==========================================="));

  // Configure ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configure motor driver pins
  pinMode(LEFT_EN,   OUTPUT);
  pinMode(LEFT_IN1,  OUTPUT);
  pinMode(LEFT_IN2,  OUTPUT);
  pinMode(RIGHT_EN,  OUTPUT);
  pinMode(RIGHT_IN3, OUTPUT);
  pinMode(RIGHT_IN4, OUTPUT);

  // Ensure motors are stopped at startup
  stopMotors();

  Serial.println(F("  Sensor pins configured."));
  Serial.println(F("  Motor pins configured."));
  Serial.print(F("  Obstacle threshold: "));
  Serial.print(OBSTACLE_THRESHOLD_CM);
  Serial.println(F(" cm"));
  Serial.print(F("  Motor speed: "));
  Serial.println(MOTOR_SPEED);
  Serial.println(F("  Initialization complete!"));
  Serial.println(F("==========================================="));
  Serial.println();

  // Brief delay before starting main loop
  delay(1000);
}

// =============================================================================
// MAIN LOOP — Runs continuously after setup()
// =============================================================================
void loop() {
  // Step 1: Read distance from ultrasonic sensor
  distance = readDistance();

  // Step 2: Validate the reading
  if (distance <= 0 || distance > 400) {
    // Invalid reading — sensor error or out of range
    Serial.println(F("[WARNING] Invalid sensor reading — stopping for safety."));
    stopMotors();
    delay(SENSOR_DELAY_MS);
    return;  // Skip this iteration and retry
  }

  // Step 3: Log the distance
  Serial.print(F("[SENSOR] Distance: "));
  Serial.print(distance);
  Serial.println(F(" cm"));

  // Step 4: Decide action based on distance
  if (distance <= OBSTACLE_THRESHOLD_CM) {
    // Obstacle detected — execute avoidance maneuver
    Serial.println(F("[ACTION] Obstacle detected! Executing avoidance..."));
    executeObstacleAvoidance();
  } else {
    // Path is clear — move forward
    moveForward();
  }

  // Step 5: Brief delay before next sensor reading
  delay(SENSOR_DELAY_MS);
}

// =============================================================================
// SENSOR FUNCTIONS
// =============================================================================

/**
 * readDistance()
 * 
 * Sends an ultrasonic pulse and measures the time for the echo to return.
 * Calculates the distance to the nearest object in centimeters.
 * 
 * How it works:
 *   1. Send a 10µs HIGH pulse on the TRIG pin.
 *   2. The HC-SR04 emits eight 40kHz ultrasonic pulses.
 *   3. The ECHO pin goes HIGH for the duration of the round-trip.
 *   4. Distance = (duration × speed of sound) / 2
 *      Speed of sound ≈ 0.0343 cm/µs → distance = duration / 58.2
 * 
 * Returns:
 *   Distance in centimeters (int).
 *   Returns 0 if the sensor times out (no echo received).
 */
int readDistance() {
  // Ensure TRIG pin is LOW before sending pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10µs HIGH pulse to trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the ECHO pulse (with timeout)
  duration = pulseIn(ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT);

  // If pulseIn timed out, it returns 0
  if (duration == 0) {
    Serial.println(F("[SENSOR] Echo timeout — no object in range."));
    return 0;
  }

  // Calculate distance: duration (µs) / 58.2 ≈ distance (cm)
  // Using integer math: duration / 58
  int calculatedDistance = duration / 58;

  return calculatedDistance;
}

// =============================================================================
// MOTOR CONTROL FUNCTIONS
// =============================================================================

/**
 * moveForward()
 * 
 * Drives all four motors forward at the configured speed.
 * Left motors: IN1=HIGH, IN2=LOW
 * Right motors: IN3=HIGH, IN4=LOW
 * 
 * Note: If the robot moves backward instead of forward, swap the
 * IN1/IN2 values for left motors and/or IN3/IN4 values for right motors.
 * See the troubleshooting guide for detailed instructions.
 */
void moveForward() {
  // Set left motors direction — FORWARD
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);

  // Set right motors direction — FORWARD
  digitalWrite(RIGHT_IN3, HIGH);
  digitalWrite(RIGHT_IN4, LOW);

  // Set motor speeds via PWM
  analogWrite(LEFT_EN,  MOTOR_SPEED);
  analogWrite(RIGHT_EN, MOTOR_SPEED);
}

/**
 * moveBackward()
 * 
 * Drives all four motors in reverse at the configured speed.
 * Left motors: IN1=LOW, IN2=HIGH
 * Right motors: IN3=LOW, IN4=HIGH
 */
void moveBackward() {
  Serial.println(F("[MOTOR] Reversing..."));

  // Set left motors direction — REVERSE
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);

  // Set right motors direction — REVERSE
  digitalWrite(RIGHT_IN3, LOW);
  digitalWrite(RIGHT_IN4, HIGH);

  // Set motor speeds via PWM
  analogWrite(LEFT_EN,  MOTOR_SPEED);
  analogWrite(RIGHT_EN, MOTOR_SPEED);
}

/**
 * turnLeft()
 * 
 * Turns the robot to the left by:
 *   - Running RIGHT motors forward
 *   - Running LEFT motors backward (or stopping them)
 * This creates a differential turn.
 */
void turnLeft() {
  Serial.println(F("[MOTOR] Turning LEFT..."));

  // Left motors — REVERSE (or stop for a wider turn)
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);

  // Right motors — FORWARD
  digitalWrite(RIGHT_IN3, HIGH);
  digitalWrite(RIGHT_IN4, LOW);

  // Set turn speed
  analogWrite(LEFT_EN,  TURN_SPEED);
  analogWrite(RIGHT_EN, TURN_SPEED);
}

/**
 * turnRight()
 * 
 * Turns the robot to the right by:
 *   - Running LEFT motors forward
 *   - Running RIGHT motors backward (or stopping them)
 * This creates a differential turn.
 */
void turnRight() {
  Serial.println(F("[MOTOR] Turning RIGHT..."));

  // Left motors — FORWARD
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);

  // Right motors — REVERSE
  digitalWrite(RIGHT_IN3, LOW);
  digitalWrite(RIGHT_IN4, HIGH);

  // Set turn speed
  analogWrite(LEFT_EN,  TURN_SPEED);
  analogWrite(RIGHT_EN, TURN_SPEED);
}

/**
 * stopMotors()
 * 
 * Immediately stops all four motors by setting all direction pins LOW
 * and PWM speed to 0.
 */
void stopMotors() {
  // Set all direction pins LOW
  digitalWrite(LEFT_IN1,  LOW);
  digitalWrite(LEFT_IN2,  LOW);
  digitalWrite(RIGHT_IN3, LOW);
  digitalWrite(RIGHT_IN4, LOW);

  // Set speed to zero
  analogWrite(LEFT_EN,  0);
  analogWrite(RIGHT_EN, 0);
}

// =============================================================================
// OBSTACLE AVOIDANCE STRATEGY
// =============================================================================

/**
 * executeObstacleAvoidance()
 * 
 * Implements a safe obstacle-response strategy:
 *   1. Stop the robot immediately.
 *   2. Reverse for a short distance.
 *   3. Turn in an alternating direction (left/right).
 *   4. Check if the new path is clear before resuming.
 * 
 * The turn direction alternates each time to help the robot navigate
 * around obstacles more effectively rather than always turning one way.
 */
void executeObstacleAvoidance() {
  // Step 1: Stop immediately
  stopMotors();
  delay(200);

  // Step 2: Reverse to create clearance
  moveBackward();
  delay(BACKUP_DURATION_MS);

  // Step 3: Stop before turning
  stopMotors();
  delay(200);

  // Step 4: Turn in alternating direction
  if (lastTurnRight) {
    turnLeft();
    lastTurnRight = false;
  } else {
    turnRight();
    lastTurnRight = true;
  }
  delay(TURN_DURATION_MS);

  // Step 5: Stop after turning
  stopMotors();
  delay(200);

  // Step 6: Check if the new path is clear
  int newDistance = readDistance();
  Serial.print(F("[CHECK] New path distance: "));
  Serial.print(newDistance);
  Serial.println(F(" cm"));

  if (newDistance > 0 && newDistance <= OBSTACLE_THRESHOLD_CM) {
    // Still blocked — try turning the other direction
    Serial.println(F("[ACTION] Still blocked — turning opposite direction..."));

    if (lastTurnRight) {
      turnLeft();
      lastTurnRight = false;
    } else {
      turnRight();
      lastTurnRight = true;
    }
    delay(TURN_DURATION_MS * 2);  // Longer turn to try a different angle

    stopMotors();
    delay(200);
  }

  Serial.println(F("[ACTION] Avoidance complete — resuming navigation."));
}

// =============================================================================
// END OF CODE
// =============================================================================
/*
 * MOTOR DIRECTION TROUBLESHOOTING
 * ================================
 * If a motor spins in the wrong direction:
 * 
 * Option 1 (Hardware): Swap the two motor wires at the L298N terminal.
 * 
 * Option 2 (Software): Swap the HIGH/LOW values for that motor's IN pins.
 *   Example — If left motors go backward when moveForward() is called:
 *     Change: digitalWrite(LEFT_IN1, HIGH); → digitalWrite(LEFT_IN1, LOW);
 *     Change: digitalWrite(LEFT_IN2, LOW);  → digitalWrite(LEFT_IN2, HIGH);
 * 
 * Each motor pair (left/right) can be corrected independently.
 * 
 * SPEED TUNING
 * =============
 * - Increase MOTOR_SPEED (max 255) if the robot moves too slowly.
 * - Decrease MOTOR_SPEED if the robot is too fast to detect obstacles.
 * - Adjust TURN_DURATION_MS to control how sharply the robot turns.
 * - Adjust OBSTACLE_THRESHOLD_CM to change how close the robot gets
 *   before reacting (smaller = closer approach, riskier).
 */
