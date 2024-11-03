# MIDI-Controlled System Volume

This project is a C++ application that allows you to control your Windows system volume using a MIDI controller. By rotating a MIDI knob, the application reads the MIDI signal and adjusts the system's master volume accordingly.

## Features
- **MIDI Input**: Listens for changes in the MIDI Control Change (CC) value from a MIDI controller.
- **Volume Control**: Maps the MIDI controller's knob position to the Windows system volume, allowing smooth adjustments from 0% to 100%.
- **Error Handling**: Catches and displays errors related to MIDI input using `RtMidi`.

## Requirements
- **Windows**: This application is designed for Windows.
- **C++ Compiler**: A C++ compiler that supports C++11 or later.
- **Libraries**:
  - [RtMidi](https://www.music.mcgill.ca/~gary/rtmidi/) for MIDI input handling.
  - **Windows API** for system volume control.
  - **mmdevapi.lib**: Ensure you link against this library for multimedia device control.

## Setup
1. **Clone this repository**:
   ```bash
   git clone https://github.com/telnorp/midivolcontrol.git

2. **Find your MIDI port**:
- change ccNumber in volumeController.cpp to the number you get in the debug section at 
