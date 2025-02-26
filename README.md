# 🌼 Farmland Dangerous Radiation Material Detection Robot

## 📌 Overview
This project involves an **autonomous robot** designed to detect **radiation hazards** in farmland. The robot navigates a **6-grid layout**, scanning for radiation and displaying results on a **7-segment display**. It uses an **ATmega32 microcontroller**, **IR sensors**, and an **L293D motor driver** for movement control.

## 🧪 Features
- 🚀 **Autonomous Navigation** - Follows a predefined path using IR sensors.
- ☢️ **Radiation Detection** - Identifies hazardous areas using reflective material.
- 📊 **Real-time Display** - Shows affected locations on a **7-segment display**.
- 🔄 **Motor Control** - Uses **DC motors** for movement.

## Running the Robot
1. Assemble the **ATmega32, IR sensors, L293D motor driver, and DC motors**.
2. Upload firmware using an **AVR programmer**.
3. Press **Start button (PB4)** to begin scanning.
4. Press **Display button (PB5)** to show detected radiation areas.

## 🖥️ Main Code - `RobotCarFinalVer.c`
- 🏁 **Controls movement, sensors, and display.**
- 🔄 **Handles user inputs for start/stop operations.**
- ⚡ **Uses LEDs for real-time feedback.**

### Key Functions:
| Function                | Description |
|-------------------------|-------------|
| `MotorForward()`        | Moves the robot forward |
| `MotorBackward()`       | Moves the robot backward |
| `MotorLeft()`           | Turns the robot left |
| `MotorReset()`          | Stops the robot |
| `radiationCountDisplay()` | Shows radiation count on the 7-segment display |


