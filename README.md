# arduino_dpad
Many buttons to one analog

1. Build the dpad and use a different resistor for each button.
2. Skip 3 and 4 by using the ![arduino_dpad_calibrate.ino](https://github.com/ByteBot0/arduino_dpad/blob/main/arduino_dpad_calibrate.ino) file and press the calibrate button.
3. Or for a minimal dpad use ![arduino_dpad](https://github.com/ByteBot0/arduino_dpad/blob/main/arduino_dpad.ino) and press the buttons to get analogRead(analogPin) values (R= on screen or serial monitor).
4. Then edit ![arduino_dpad](https://github.com/ByteBot0/arduino_dpad/blob/main/arduino_dpad.ino) using the R values to map and test buttons.

​​  
​  
​  
### 1) Building the dpad:
#### Here's how I wired it:
![arduino_dpad_fritzing](https://github.com/user-attachments/assets/09f507ce-5ea1-4cda-801a-1442bc35bc7e)
​  
​  
​  
​  
#### This is the most efficient way I found to pack it into a breadboard. Note that the buttons in the middle of the breadboard are not touching:
![arduino_dpad](https://github.com/user-attachments/assets/0fcc0643-1cb5-42d0-a8e2-125a8e001cff)
​  
​  
​  
​  
#### Next, this shows the screen and battery. It also shows the R= value from the ![arduino_dpad](https://github.com/ByteBot0/arduino_dpad/blob/main/arduino_dpad.ino) file that you can use to map your buttons.
![dpad_display](https://github.com/user-attachments/assets/42dfc65c-e705-4b3c-983e-e438503a96a3)
  
​  
​  
​  
#### Finally, the ![arduino_dpad_calibrate.ino](https://github.com/ByteBot0/arduino_dpad/blob/main/arduino_dpad_calibrate.ino) file is way lighter and faster and includes a calibrate button and a button that displays the current high and low values. This is nice when using different power sources because it lets the user cycle through and adjust the values just by pressing and holding each button.
​  
​  
Based on https://forum.arduino.cc/t/multiple-buttons-on-1-analog-pin/8622
  
Button values also work with AJRussell/Tiny-Tetris, which hopefully simplifies the dpad build process and integrates well with other repos.
