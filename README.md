# Enhanced Fire Detection and Air Quality Monitoring System

## Overview

This system monitors air quality and detects potential fire hazards using the **MQ135 Air Quality Sensor** and **IR Flame Sensors**. It provides visual alerts through an **LED** and outputs status messages to the **serial monitor**.

- The system evaluates air quality in real-time, categorizing it into **Good**, **Moderate**, and **Poor** levels based on the **MQ135** sensor readings.
- It detects fire or flame using **IR sensors** and combines fire detection with poor air quality to trigger a rapid blinking LED alert.
- If only the IR sensors are triggered (but air quality is acceptable), the LED will blink with a different pattern for a "potential fire" warning.

## Features

- **MQ135 Sensor**: Monitors air quality and detects harmful gases.
- **IR Sensors**: Detect flames or fire.
- **LED Visual Alerts**: 
  - Rapid blinking LED when both poor air quality and fire are detected.
  - Slow blinking LED when IR sensors are triggered (indicating a potential fire).
  - Steady LED or no LED for good or moderate air quality.
- **Real-time Serial Monitor Output**: 
  - Displays air quality status with emojis (🌿, 🌫️, ☠️).
  - Shows fire detection alerts with a 🔥 emoji and "Evacuate" instructions.
- **Multiple Thresholds**:
  - **Good**: Air quality ≤ 38.
  - **Moderate**: Air quality ≤ 60.
  - **Poor**: Air quality > 60.
- **Safety Alerts**: Fires and poor air quality result in immediate safety alerts.

## Components Used

- **Arduino UNO**: Microcontroller for managing inputs and outputs.
- **MQ135 Gas Sensor**: For air quality measurement.
- **IR Flame Sensors**: For fire/flame detection.
- **LED**: For visual alerts.
- **Resistors, Breadboard, Jumper Wires**: For building the circuit.

## Wiring Diagram

- **MQ135 Pin**: Connect to **A0**.
- **IR Sensors**: Connect to **Digital Pins 7 and 8**.
- **LED Pin**: Connect to **Pin 9**.

## Code Overview

### System Logic

1. **Fire Detection (Highest Priority)**:
   - If **IR Sensors** detect a flame and **poor air quality** is present (MQ135 value > threshold), the system triggers a **fire detection alert**.
   - The LED blinks rapidly, and a warning is printed to the serial monitor.

2. **IR Detection Alone**:
   - If **IR Sensors** detect a flame but air quality is acceptable, the system prints a "Potential Fire" alert and blinks the LED with a different pattern.

3. **Air Quality Evaluation**:
   - The system evaluates the **MQ135 sensor** output to classify air quality into **Good**, **Moderate**, or **Poor**.
   - **Good**: No LED blink.
   - **Moderate**: LED blinks slowly.
   - **Poor**: Solid LED light.

### Air Quality Levels

- **Good (🌿)**: Air quality value ≤ 38.
- **Moderate (🌫️)**: Air quality value ≤ 60.
- **Poor (☠️)**: Air quality value > 60.

### Fire Alert Mechanism

- If a **fire** is detected, the LED blinks rapidly, and the system displays an **evacuate** message on the serial monitor.

## Installation and Setup

### Prerequisites

- **Arduino IDE** installed.
- **Arduino UNO** or compatible board.
- **MQ135 Gas Sensor**, **IR Flame Sensors**, and **LED** for hardware.
- Basic knowledge of **Arduino programming** and circuit setup.

### Steps

1. **Wiring**:
   - Connect **MQ135 sensor** to **A0**.
   - Connect **IR sensors** to **digital pins 7 and 8**.
   - Connect **LED** to **pin 9**.

2. **Upload the Code**:
   - Open the **Arduino IDE**.
   - Copy and paste the code into the IDE.
   - Select the correct **board** and **port**.
   - Upload the code to the Arduino.

3. **Monitor Output**:
   - Open the **serial monitor** to view real-time data.
   - Observe the LED for visual alerts and corresponding serial messages for air quality and fire detection.
