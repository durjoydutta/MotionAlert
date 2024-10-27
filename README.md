# MotionAlert
# ESP32 Smart Motion-Activated Intrusion Alert System on Arduino IOT Cloud

## Project Overview
This project is a **motion-activated security system** designed to detect movement and respond with a light and buzzer, creating an effective deterrent and notification system for any unexpected motion within a monitored area. Built using an ESP32 microcontroller, this setup can be controlled remotely and logs total light-on time to give insights into activity patterns.

## Features
- **Motion Detection**: When motion is detected, an AC light turns on for a set period (30 seconds), and a buzzer sounds briefly to alert any presence.
- **Manual Control Option**: The system allows manual on/off control of the light through a dashboard, independent of motion events.
- **Timed Control**: The light turns off automatically after 30 seconds of no movement to conserve energy.
- **Alert Window**: The buzzer reactivates only after a 5-second cooldown to reduce noise in case of prolonged motion.

## Components Used
- **ESP32** - Microcontroller for WiFi connectivity and control
- **PIR Motion Sensor** - Detects movement within the monitored area
- **Relay Module** - Controls the AC light
- **Buzzer** - Provides an audible alert upon motion detection

## Getting Started
1. **Hardware Setup**: 
   - Connect the motion sensor to the ESP32 digital input pin.
   - Connect the relay module to control the light.
   - Connect the buzzer to a digital output pin on the ESP32.

2. **Install Arduino Libraries**: 
   - Install necessary libraries for ESP32 and Arduino IoT Cloud integration.

3. **Configure Cloud Dashboard**: 
   - Set up the dashboard to manually control the light and monitor activity remotely.

## Usage
Deploy the system in a desired area and turn on **motionControl**. The light and buzzer will respond to detected movement, with manual overrides available for light control.

## Future Improvements
- **Integrate notification systems** like SMS or email alerts for remote activity monitoring.
- **Battery and solar power options** for off-grid applications, making it a self-sustained security solution.

## License
This project is open-source under the MIT License.
