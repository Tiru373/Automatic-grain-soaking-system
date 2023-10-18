

# Automatic Grain Soaking System


 
## Overview

This Arduino project is a simple but versatile alarm and door-opening system. It allows you to set a specific "soaking time" and provides audio and visual alerts when it's time to begin a process or when the process is complete. It's an ideal solution for applications where automated door control and process timing are required.

## Features

- Set and adjust the "soaking time" for your process.
- Real-time clock (RTC) ensures accurate timekeeping.
- Audio alerts with a buzzer.
- Servo motor control for opening a door or performing a related action.
- User-friendly interface using buttons and an LCD display.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno).
- DS1307 or DS3231 RTC module for accurate timekeeping.
- 16x2 LCD display for real-time display.
- Servo motor to control the door.
- Buzzer for audio alerts.
- Push buttons for user interaction.
- Necessary wires and connectors.

## Software Requirements

- Arduino IDE for uploading the code to your Arduino board.

## Usage

1. Connect the required hardware components to your Arduino board.
2. Upload the provided Arduino code to your board using the Arduino IDE.
3. Set the "soaking time" by adjusting the hours and minutes using the buttons.
4. The system will display the current time and the set "soaking time."
5. When the current time matches the set "soaking time," the system will:
   - Trigger the buzzer for an audio alert.
   - Open the door using the servo motor (or perform a related action).
6. The system will display "Process Done" after a minute, indicating the end of the process.


## Contributing

Contributions and improvements to the code are welcome. If you have suggestions or feature requests, please open an issue or submit a pull request.

## Author
Tirumalasetty Ashok

## Acknowledgments

This project is inspired by Arduino enthusiasts and the open-source community.
