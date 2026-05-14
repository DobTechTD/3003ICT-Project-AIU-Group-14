# 3003ICT Project - Autonomous Irrigation Unit

## Project Overview
Briefly describe what the A.I.U does.

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
| `sketch.ino` | Main program entry point |
| `Config.h` | Pin definitions, thresholds, constants |
| `FSM.ino` | Finite state machine logic |
| `Sensors.ino` | Sensor reading and conversion |
| `Outputs.ino` | Pump, LED, buzzer/fan control |
| `Display.ino` | LCD display logic |
| `Button.ino` | Manual button handling |
| `diagram.json` | Wokwi circuit simulation |
| `libraries.txt` | Required Wokwi libraries |

## System States
- Idle
- Monitoring
- Irrigating
- Warning
- Failsafe

## How to Run
1. Open the project in Wokwi.
2. Ensure the required libraries are loaded.
3. Run `sketch.ino`.
4. Adjust the simulated sensors to test different conditions.

## Demonstration Video
Add the video file or link here.

## Author
Thomas Dobson
