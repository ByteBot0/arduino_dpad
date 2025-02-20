# arduino_dpad
Many buttons to one analog

1. Build the dpad and use a different resistor for each button.
3. Run arduino_dpad.ino and press buttons to get analogRead(analogPin) values (R= on screen or serial monitor).
4. Edit arduino_dpad.ino using the values to map and test buttons.

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
#### Finally, this shows the screen and battery. It also includes where you can get the R= value that you can input into the .ino file to map your buttons.
![dpad_display](https://github.com/user-attachments/assets/42dfc65c-e705-4b3c-983e-e438503a96a3)
​  
​  
​  
​  
Based on https://forum.arduino.cc/t/multiple-buttons-on-1-analog-pin/8622
  
Button values also work with AJRussell/Tiny-Tetris, which hopefully simplifies the dpad build process and integrates well with other repos.
