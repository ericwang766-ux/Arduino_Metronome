# Arduino Metronome

A digital metronome built with Arduino that provides adjustable tempo, selectable time signatures, audible beat accents, and an LCD-based user interface.

## Overview

This project is a custom-built digital metronome designed for music practice. It combines an Arduino, LCD display, buzzer, potentiometer, and physical buttons to create a standalone metronome with an interactive menu system.

The user can adjust the tempo using physical buttons or the Arduino Serial Monitor, select different time signatures, and start or stop the metronome. The buzzer provides an audible beat, with accents used to distinguish the beginning of each measure.

The project was developed as a hands-on electronics and programming project, combining hardware prototyping with embedded software and user-interface design.

## Features
- Adjustable tempo using physical buttons
- Serial tempo input through the Arduino Serial Monitor
- Selectable time signatures through an LCD menu
- Audible beat generation using a piezo buzzer
- Beat accents based on the selected time signature
- Start/stop functionality
- Four-button control system
- Potentiometer-controlled LCD display
## Hardware
| Component | Purpose |
|---|---|
| Arduino | Main microcontroller |
| LCD display | Displays tempo, time signature, and menu information |
| Piezo buzzer | Produces the audible metronome beats |
| Potentiometer | Adjusts the LCD display |
| 4 push buttons | User input and menu navigation |
| Breadboard | Circuit prototyping |
| Jumper wires | Electrical connections |
## User Controls
Control	Function
| Control | Function |
|---|---|
| Left button | Decreases the selected value |
| Right button | Increases the selected value |
| Menu button | Goes to the menu screen |
| Start/Stop button | Starts or stops the metronome / selects the menu option |
| Potentiometer | Adjusts the LCD display |

The tempo can also be entered directly through the Arduino Serial Monitor.

## How It Works

The Arduino is responsible for generating the timing of the metronome and keeping track of the current beat within each measure.

### Tempo

The tempo can be increased or decreased using the left and right buttons. The user can also enter a tempo through the Serial Monitor.

The Arduino uses the selected tempo to determine the interval between beats and activates the buzzer at the appropriate times.

### Time Signatures

The metronome includes a menu system that allows the user to select a time signature.

The selected time signature determines how many beats are contained within each measure and where the primary accent occurs.

For example, in 4/4 time:

ONE — two — three — four

The first beat receives the primary accent, making it easier for the musician to keep track of the beginning of each measure.

### User Interface

The LCD provides feedback to the user by displaying the current settings and menu options.

The four physical buttons provide navigation and control:

Left/right buttons change values
Set confirms or selects options
Start/Stop controls the metronome

The potentiometer is used to adjust the LCD display setting.

## Software

The project is programmed using the Arduino programming environment and C/C++.

The software handles:

Beat timing
Tempo calculation
Beat counting
Time signature selection
Accent generation
LCD output
Button input
Menu navigation
Serial input
# Project Structure
Arduino-Metronome/
├── Arduino-Metronome.ino
└── README.md
## Current Status

The current prototype includes the core functionality of the metronome:

Adjustable tempo
Serial tempo input
Start/stop control
LCD interface
Menu navigation
Time signature selection
Audible beat generation
Beat accents
Physical button controls
LCD display adjustment

The project is currently being developed as a hardware prototype using a breadboard and jumper wires.

# Future Improvements

Potential future improvements include:

- Add additional time signatures
- Add tap-tempo functionality
- Add additional rhythm patterns
- Add visual beat indicators
- Improve the menu interface
# What I Learned

This project has provided hands-on experience with:

- Arduino programming
- Embedded C/C++
- Digital electronics
- Analog inputs
- Push-button inputs
- LCD interfaces
- Serial communication
- Timing and beat generation
- Menu and user-interface design
- Circuit prototyping
- Debugging hardware and software
# Future Development

As development continues, this repository will document the progression from the initial breadboard prototype toward a more refined and complete metronome.

Built with Arduino as an electronics and embedded-systems project.
