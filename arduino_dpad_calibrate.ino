//Lighter, faster, and lets you calibrate buttons and view the current values.
//Nice to have when using different power sources for the Arduino.

#include <Arduino.h>
#include <stdio.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//dpad input pin
int analogPin = 0;

// To store analogRead(analogPin) value
int raw = 0;

//auto-calibrate button
const int topButtonPin = 3; // The pin where the top button is connected

//Show current high and low values
const int bottomButtonPin = 4; // The pin where the bottom button is connected


// This is to track which button number it's calibrating
int currentButtonNumber = 0;
int buttonNum = 0;

// Pixel location
int vertical = 35;
int horizontal = 60;
int rotate = 0;

/*
Button layout:
    6 (calibrate)
    7 (show current values)

   1         5
0     2        
   3       4

*/
// Set button high and low values based on what R= is returning on the screen,
// or use calibrate button
// Button ranges:
int buttonLow[6] = {50, 660, 350, 230, 100, 520};
int buttonHigh[6] = {90, 680, 400, 270, 150, 580};


void setup() {
  Serial.begin(9600);

  //Start display
  display.setRotation(2);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  pinMode(topButtonPin, INPUT_PULLUP);
  pinMode(bottomButtonPin, INPUT_PULLUP);
}


void loop() {

  //Set default display options
  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  //Get number of buttons based on the number of elements in the array
  int numberOfButtons = sizeof(buttonLow)/sizeof(buttonLow[0]);

  raw = analogRead(analogPin);


  // Make the buttons do stuff: 
  if (raw >= buttonLow[0] && raw <= buttonHigh[0]) {
    horizontal -= 10;
  }
  if (raw >= buttonLow[1] && raw <= buttonHigh[1]) {
    vertical -= 10;
  }
  if (raw >= buttonLow[2] && raw <= buttonHigh[2]) {
    horizontal += 10;
  }
  if (raw >= buttonLow[3] && raw <= buttonHigh[3]) {
    vertical += 10;
  }
  if (raw >= buttonLow[4] && raw <= buttonHigh[4]) {
    rotate += 1;
  }
  if (raw >= buttonLow[5] && raw <= buttonHigh[5]) {
    vertical = 35;
    horizontal = 60;
  }
  // Make object go back to upright, otherwise it'll explode. Comment out if you'd like
  if (rotate == 4) {
    rotate = 0;
  }


  // Auto-calibrate feature:
  if (digitalRead(topButtonPin) == LOW) {
    for (int currentButtonNumber = 0; currentButtonNumber < numberOfButtons; currentButtonNumber++) {
      // its a lot of print statements so I thought this would be cleanest
      calibrationMenu(currentButtonNumber);
    }
  }

  if (digitalRead(bottomButtonPin) == LOW) {
    display.clearDisplay();

    for (int currentButtonNumber = 0; currentButtonNumber < numberOfButtons; currentButtonNumber++) {
      display.setCursor(0, currentButtonNumber*10);
      display.print("Button ");
      display.print(currentButtonNumber); 
      display.print(" = ");           
      display.print(buttonLow[currentButtonNumber]);
      display.print(" - ");
      display.println(buttonHigh[currentButtonNumber]);      
    }
    display.display();
    delay(5000);
    display.clearDisplay();

  }
  
  //draw the circle for interacting with
  display.fillCircle(horizontal, vertical, 2, WHITE);

  // Print R= ...
  display.setCursor(0, 50);
  display.print("R = ");
  display.println(raw);
  display.display();

  // Print to serial to use without screen
  Serial.print("Raw: ");
  Serial.println(raw);


}


//This is used in calibrationMenu() to let the user
//know how much time is left
void timer(int seconds) {
  int i = 0;
  for (i=seconds; i>0; i--) {
    display.setCursor(0, 55);
    display.print("Time: ");
    display.println(i);
    display.display();
    delay(1000);

    //cover old text
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(0, 55);
    display.print("Time: ");
    display.println(i);
    display.display();
    display.setTextColor(SSD1306_WHITE);
  }

}



void calibrationMenu(int buttonNum) {
  //Display old values
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Hold button ");
  display.println(buttonNum);
  display.setCursor(0, 10);
  display.print("Low is: ");
  display.println(buttonLow[buttonNum]);
  display.setCursor(0, 20);
  display.print("High is: ");
  display.println(buttonHigh[buttonNum]);
  display.display();

  //Countdown
  timer(3);
  display.clearDisplay();

  //Where the actual new raw number is set.
  // + and - 20 as a buffer
  raw = analogRead(analogPin);
  buttonLow[buttonNum] = raw - 20;
  buttonHigh[buttonNum] = raw + 20;

  //Display new values so the user knows it worked/didn't work:
  display.setCursor(0, 0);
  display.print("Button ");
  display.println(buttonNum);
  display.setCursor(0, 10);
  display.print("New low is: ");
  display.println(buttonLow[buttonNum]);
  display.setCursor(0, 20);
  display.print("New high is: ");
  display.println(buttonHigh[buttonNum]);
  display.display();
  delay(3000);
  display.clearDisplay();
}
