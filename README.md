# 3003ICT Project - Autonomous Irrigation Unit

## Project Overview

The Autonomous Irrigation Unit, abbreviated as A.I.U, is an embedded agricultural controller that uses environmental sensor data to manage irrigation, detect heat-risk conditions, and maintain safe operation under day/night and water-availability conditions.

The system is designed to monitor soil moisture, temperature, light level, and tank water level. Based on these inputs, it automatically controls irrigation, warning outputs, and failsafe behaviour through a finite state machine structure.

## Features

- Soil moisture monitoring
- Temperature and heat-risk detection
- Day/night sensing
- Water-level monitoring
- Automatic irrigation control
- Warning and failsafe states
- LCD/status output

## Hardware / Wokwi Components

- Arduino Uno
- DHT22 temperature sensor
- Photoresistor
- Potentiometer for soil moisture
- Potentiometer for water level
- Pushbutton
- RGB LED
- Buzzer or fan output
- Relay/pump output
- LCD 2004 I2C display

## File Structure

| File | Purpose |
|---|---|
| `README.md` | Project documentation, overview, setup instructions, and demonstration information |
| `sketch.ino` | Main program file containing `setup()`, `loop()`, and high-level control |
| `Config.h` | Constants, pin mappings, thresholds, timing values, and shared configuration |
| `Sensors.ino` | Sensor-reading functions such as temperature, soil moisture, water level, and light level |
| `FSM.ino` | Finite State Machine logic, including state transitions and state behaviour |
| `Outputs.ino` | Controls output devices such as the pump, RGB LED, buzzer, fan, and relay |
| `Display.ino` | LCD display updates and user-facing system information |
| `Button.ino` | Pushbutton input handling, debouncing, reset, and acknowledgement logic |
| `diagram.json` | Wokwi circuit diagram for the simulated hardware setup |
| `libraries.txt` | Required libraries for the Wokwi/Arduino simulation |
| `/demo/project-demonstration.mp4` | Final project demonstration video |

## System States

- Idle
- Monitoring
- Irrigating
- Warning
- Failsafe

## How to Run

1. Open the project in Wokwi.
2. Ensure the following files are included in the project:
   - `sketch.ino`
   - `Config.h`
   - `Sensors.ino`
   - `FSM.ino`
   - `Outputs.ino`
   - `Display.ino`
   - `Button.ino`
   - `diagram.json`
   - `libraries.txt`
3. Start the Wokwi simulation.
4. Adjust the simulated sensor inputs to test different operating conditions.
5. Observe the LCD, RGB LED, pump/relay output, and warning output as the system changes state.

## Demonstration Video

The final project demonstration video will be stored in the `/demo` folder.

Video file:

`/demo/project-demonstration.mp4`

## Course

3003ICT - Programming for Robotics

## Project Title

Autonomous Irrigation Unit  
A.I.U

## Author

Thomas Dobson
