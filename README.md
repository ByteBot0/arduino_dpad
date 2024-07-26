# arduino_dpad
Many buttons to one analog

1. Build the dpad and use a different resistor for each button.
2. Run arduino_dpad.ino and press buttons to get analogRead(analogPin) values (R= on screen or serial monitor).
3. Edit arduino_dpad.ino using the values to map and test buttons.



Based on https://forum.arduino.cc/t/multiple-buttons-on-1-analog-pin/8622

The goal is to keep this repo as simple as possible so anyone can copy and paste and modify as needed. Button values also work with AJRussell/Tiny-Tetris, which hopefully simplifies the dpad build process and integrates well with other repos.
